#include "Cursor.h"
#include "Back.h"
#include "StageManager.h"
#include "StageSelectObjUS.h"
#include "StageSelectObjEarth.h"
#include "StageSelectObjGalaxy.h"
#include "StageSelectObjBH.h"
#include "StageSelectObjAsteroid.h"
#include "Title.h"
#include "StageSelect.h"
#include "Hukidasi.h"
#include "StageLoad.h"
#include "KeyMove.h"
#include "MiniGame.h"
#include "TimeAttack.h"
#include "Ranking.h"
#include "StageSelectIcon.h"

namespace Cursor
{
	/*リソースの初期化処理*/
	void RS::Init()
	{

	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{

	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(0.7f);
		rCursorBase = Rec(0.f, 0.f, 16.f * 4, 16.f * 4);
		fSpd = 12.f;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		spMove.reset();
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto kb = KB::GetState();
		auto pad = JoyPad::GetState(0);
		const float fCursorX = rCursorBase.GetPosX();
		const float fCursorY = rCursorBase.GetPosY();
		const float fCursorW = rCursorBase.GetW();
		const float fCursorH = rCursorBase.GetH();
		/*キーボード移動*/
		MoveKeyBoard(kb, fCursorX, fCursorY, fCursorW, fCursorH);
		/*パッド移動*/
		MovePad(pad, fCursorX, fCursorY, fCursorW, fCursorH);

		if (auto ti = Find<Title::Obj>(Title::caTaskName))
		{
			ti->fStartImgSrcY = 0.f;
			ti->rStart.Scaling(16 * 30.f, 16 * 5.f);
			if (ti->rStart.CheckHit(&rCursorBase.GetPos()))
			{
				ti->fStartImgSrcY = 1.f;
				ti->rStart.Scaling(16 * 30.f * 1.5f, 16 * 5.f * 1.5f);
				if (kb->Down(VK_RETURN) || pad->Down(JOY_BUTTON6))
				{
					RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
					Add<Back::Obj>();
					Add<StageSelect::Obj>();
					Pause(2);
					return;
				}
			}
		}

		if (auto ra = Find<Ranking::Obj>(Ranking::caTaskName))
		{
			ra->rButton.Scaling(16.f * 15.f, 16.f * 13.f);
			if (ra->rButton.CheckHit(&rCursorBase.GetPos()))
			{
				ra->rButton.Scaling(16.f * 20.f, 16.f * 18.f);
				if (kb->Down(VK_RETURN) || pad->Down(JOY_BUTTON6))
				{
					RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
					Add<Back::Obj>();
					Add<StageSelect::Obj>();
					Pause(2);
					return;
				}
			}
		}

		bool bHitFlag = false;
		constexpr float fAddScale = 70.f;
		float fScaleWMax = 1800.f;//2000;
		float fScaleHMax = 400.f;//600;
		auto hu = Find<Hukidasi::Obj>(Hukidasi::caTaskName);
		for (auto si : FindAll<StageSelectIcon::Obj>(StageSelectIcon::caTaskName))
		{
			si->rIcon.Scaling(16.f * 10.f, 16.f * 10.f);
			Circle cHit;
			cHit.SetPos(&si->rIcon.GetPos());
			cHit.SetRadius(si->rIcon.GetW() / 2);
			if (cHit.CheckHit(&rCursorBase.GetPos()))
			{
				si->rIcon.Scaling(16.f * 15.f, 16.f * 15.f);
				if (kb->Down(VK_RETURN) || pad->Down(JOY_BUTTON6))
				{
					RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
					if (auto manager = Find<StageManager::Obj>(StageManager::caTaskName))
					{
						manager->bStageNum = ((si->type + 1) * 10) + 1;

						Add<StageLoad::Obj>();

						Pause(2);
					}
				}

				if (hu)
				{
					Point pPos(Rec::Win.r * 0.5f, Rec::Win.b * 0.75f);
					if (si->type == StageSelectIcon::Type::FR || si->type == StageSelectIcon::Type::TA)
					{
						pPos.y = 910.f;
						fScaleWMax = 1200.f;
						fScaleHMax = 200.f;
						hu->rTextBox.SetPos(&pPos);
					}
					else
					{
						hu->rTextBox.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * (0.75f * 0.75f) + 70.f));
					}
					hu->SetPos(&pPos);
					hu->SetScaleMax(fScaleWMax, fScaleHMax);
					hu->SetAddScale(fAddScale);
					hu->SetStageGroup(si->type);
				}
				break;
			}
			else
			{
				if (hu)hu->SetAddScale(-fAddScale);
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		//33
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * 32, 16.f, 15.f, 15.f);
			rCursorBase.Draw(&res->iStageImg, &src);
#ifdef _DEBUG
			rCursorBase.Draw();
#endif // _DEBUG
		}
	}
	/*キーボードでの移動*/
	void Obj::MoveKeyBoard(std::shared_ptr<KB> &apKB, const float afX, const float afY, const float afW, const float afH)
	{
		if (apKB->On('W'))
		{
			if (afY <= Rec::Win.t + afH / 2) {
				rCursorBase.SetPos(&Point(afX, Rec::Win.t + afH / 2));
			}
			else
				rCursorBase.Move(&(Vector2::up * fSpd));
		}
		if (apKB->On('S'))
		{
			if (afY >= Rec::Win.b - afH / 2) {
				rCursorBase.SetPos(&Point(afX, Rec::Win.b - afH / 2));
			}
			else
				rCursorBase.Move(&(Vector2::down * fSpd));

		}
		if (apKB->On('A'))
		{
			if (afX <= Rec::Win.l + afW / 2) {
				rCursorBase.SetPos(&Point(Rec::Win.l + afW / 2, afY));
			}
			else
				rCursorBase.Move(&(Vector2::left * fSpd));
		}
		if (apKB->On('D'))
		{
			if (afX >= Rec::Win.r - afW / 2) {
				rCursorBase.SetPos(&Point(Rec::Win.r - afW / 2, afY));
			}
			else
				rCursorBase.Move(&(Vector2::right * fSpd));
		}
	}
	/*パッドでの移動*/
	void Obj::MovePad(std::shared_ptr<JoyPad> &apPad, const float afX, const float afY, const float afW, const float afH)
	{
		if (apPad->Axis(JoyPad::Stick::STK_LEFT) != Vector2::zero)
		{

			if (afX - afW * 0.5f - 1 < Rec::Win.l) {
				rCursorBase.SetPos(&Point(Rec::Win.l + afW * 0.5f, afY));
			}
			else if (afX + afW * 0.5f > Rec::Win.r) {
				rCursorBase.SetPos(&Point(Rec::Win.r - afW * 0.5f, afY));
			}
			if (afY - afW * 0.5f - 1 < Rec::Win.t) {
				rCursorBase.SetPos(&Point(afX, Rec::Win.t + afW * 0.5f));
			}
			else if (afY + afH * 0.5f > Rec::Win.r) {
				rCursorBase.SetPos(&Point(afX, Rec::Win.b - afW));
			}
			rCursorBase.Move(&(apPad->Axis(JoyPad::Stick::STK_LEFT) * fSpd));
		}
	}
}
