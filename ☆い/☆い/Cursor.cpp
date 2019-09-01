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
#include "Result.h"
#include "GameInit.h"
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
		/*キーボード移動*/
		MoveKeyBoard(kb);
		/*パッド移動*/
		MovePad(pad);

		if (auto ti = Find<Title::Obj>(Title::caTaskName))
		{
			//rCursorBase.SetPos(&ti->rStart.GetPos());
			ti->fStartImgSrcY = 0.f;
			ti->rStart.Scaling(16 * 30.f, 16 * 5.f);
			if (ti->rStart.CheckHit(&rCursorBase.GetPos()))
			{
				ti->fStartImgSrcY = 1.f;
				ti->rStart.Scaling(16 * 30.f * 1.5f, 16 * 5.f * 1.5f);
				if (kb->Down(VK_RETURN) || kb->Down(VK_RIGHT) || pad->Down(JOY_BUTTON6) || pad->Down(JOY_BUTTON2))
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
				}
			}
		}

		if (auto re = Find<Result::Obj>(Result::caTaskName))
		{
			//rCursorBase.SetPos(&re->rRestart.GetPos());
			re->rRestart.Scaling(16.f * 15.f, 16.f * 12.f);
			if (re->rRestart.CheckHit(&rCursorBase.GetPos()))
			{
				re->rRestart.Scaling(16.f * 19.f, 16.f * 16.f);
				if (kb->Down(VK_RETURN) || kb->Down(VK_RIGHT) || pad->Down(JOY_BUTTON6) || pad->Down(JOY_BUTTON2))
				{
					if (re->rHanko.GetPosX() != re->rRestart.GetPosX()) re->rHanko.Scaling(16.f * 19.f * 10.f, 16.f * 16.f * 10.f);
					re->bPushHanko = true;
					//RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
					//Add<Back::Obj>();
					//Add<Title::Obj>();
					////Add<StageSelect::Obj>();
					//Pause(2);
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
	void Obj::MoveKeyBoard(std::shared_ptr<KB> & apKB)
	{

		if (apKB->On('W'))
		{
			rCursorBase.Move(&(Vector2::up * fSpd));
		}
		if (apKB->On('S'))
		{
			rCursorBase.Move(&(Vector2::down * fSpd));
		}
		if (apKB->On('A'))
		{
			rCursorBase.Move(&(Vector2::left * fSpd));
		}
		if (apKB->On('D'))
		{
			rCursorBase.Move(&(Vector2::right * fSpd));
		}
		//画面外の判定処理
		float fX = rCursorBase.GetPosX();
		float fY = rCursorBase.GetPosY();
		const float fW = rCursorBase.GetW();
		const float fH = rCursorBase.GetH();
		if (fX <= Rec::Win.l + fW * 0.5f)
		{
			fX = Rec::Win.l + fW * 0.5f;
		}
		else if (fX >= Rec::Win.r - fW * 0.5f)
		{
			fX = Rec::Win.r - fW * 0.5f;
		}
		if (fY <= Rec::Win.t + fH * 0.5f)
		{
			fY = Rec::Win.t + fH * 0.5f;
		}
		else if (fY >= Rec::Win.b - fH * 0.5f)
		{
			fY = Rec::Win.b - fH * 0.5f;
		}
		rCursorBase.SetPos(&Point(fX, fY));
	}
	/*パッドでの移動*/
	void Obj::MovePad(std::shared_ptr<JoyPad> & apPad)
	{
		if (apPad->Axis(JoyPad::Stick::STK_LEFT) != Vector2::zero)
		{
			rCursorBase.Move(&(apPad->Axis(JoyPad::Stick::STK_LEFT) * fSpd));
			float fX = rCursorBase.GetPosX();
			float fY = rCursorBase.GetPosY();
			const float fW = rCursorBase.GetW();
			const float fH = rCursorBase.GetH();
			if (fX - fW * 0.5f < Rec::Win.l)
			{
				fX = Rec::Win.l + fW * 0.5f;
			}
			else if (fX + fW * 0.5f > Rec::Win.r)
			{
				fX = Rec::Win.r - fW * 0.5f;
			}
			if (fY - fH * 0.5f < Rec::Win.t)
			{
				fY = Rec::Win.t + fH * 0.5f;
			}
			else if (fY + fH * 0.5f > Rec::Win.b)
			{
				fY = Rec::Win.b - fH * 0.5f;
			}
			rCursorBase.SetPos(&Point(fX, fY));
		}
	}
}
