#include "Cursor.h"
#include "Back.h"
#include "StageManager.h"
#include "StageSelectObjUS.h"
#include "StageSelectObjEarth.h"
#include "StageSelectObjGalaxy.h"
#include "StageSelectObjBH.h"
#include "StageSelectObjAsteroid.h"
#include "Stage1-1.h"
#include "Stage2-1.h"
#include "Stage3-1.h"
#include "Stage4-1.h"
#include "Stage5-1.h"
#include "Title.h"
#include "StageSelect.h"

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
		SetName("カーソルタスク");
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/
		rCursorBase = Rec(0.f, 0.f, 16.f * 4, 16.f * 4);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto pad = JoyPad::GetState(0);
		auto kb = KB::GetState();
		if (kb->On('W'))
		{
			if (rCursorBase.GetPosY() <= Rec::Win.t + rCursorBase.GetH() / 2) {
				rCursorBase.SetPos(&Point(rCursorBase.GetPosX(), Rec::Win.t + rCursorBase.GetH() / 2));
			}
			else
				rCursorBase.Move(&(Vector2::up * 8.f));
		}
		if (kb->On('S'))
		{
			if (rCursorBase.GetPosY() >= Rec::Win.b - rCursorBase.GetH() / 2) {
				rCursorBase.SetPos(&Point(rCursorBase.GetPosX(), Rec::Win.b - rCursorBase.GetH() / 2));
			}
			else
				rCursorBase.Move(&(Vector2::down * 8.f));

		}
		if (kb->On('A'))
		{
			if (rCursorBase.GetPosX() <= Rec::Win.l + rCursorBase.GetW() / 2) {
				rCursorBase.SetPos(&Point(Rec::Win.l + rCursorBase.GetW() / 2, rCursorBase.GetPosY()));
			}
			else
				rCursorBase.Move(&(Vector2::left * 8.f));
		}
		if (kb->On('D'))
		{
			if (rCursorBase.GetPosX() >= Rec::Win.r - rCursorBase.GetW() / 2) {
				rCursorBase.SetPos(&Point(Rec::Win.r - rCursorBase.GetW() / 2, rCursorBase.GetPosY()));
			}
			else
				rCursorBase.Move(&(Vector2::right * 8.f));
		}
		if (pad->GetAxisL() != Vector2::zero)
		{
					rCursorBase.Move(&(pad->GetAxisL() * 8.f));
		}
		if (auto ti = Find<Title::Obj>("タイトルタスク"))
		{
			ti->fStartImgSrcY = 0.f;
			ti->rStart.Scaling(16 * 30.f, 16 * 5.f);
			if (ti->rStart.CheckHit(&rCursorBase.GetPos()))
			{
				ti->fStartImgSrcY = 1.f;
				ti->rStart.Scaling(16 * 30.f * 1.5f, 16 * 5.f * 1.5f);
				if (kb->Down(VK_RETURN))
				{
					RemoveAll();
					Add<StageManager::Obj>();
					Add<Back::Obj>();
					Add<StageSelect::Obj>();
					Pause(2);
					return;
				}
				if (pad->Down(J_BUT_6))
				{
					RemoveAll();
					Add<StageManager::Obj>();
					Add<Back::Obj>();
					Add<StageSelect::Obj>();
					Pause(2);
					return;
				}
			}
		}
		if (auto us = Find<StageSelectObjEarth::Obj>("地球タスク"))
		{
			us->rEarth.Scaling(16 * 10, 16 * 10);
			Circle cHit(&us->rEarth.GetPos(), us->rEarth.GetW() * 0.5f);
			if (cHit.CheckHit(&rCursorBase.GetPos()))
			{
				us->rEarth.Scaling(16 * 15, 16 * 15);
				if (kb->Down(VK_RETURN)|| pad->Down(J_BUT_6))
				{
					RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
					Add<Back::Obj>();
					Add<Stage11::Obj>();
					Pause(2);
					return;
				}
			}
		}
		if (auto us = Find<StageSelectObjAsteroid::Obj>("小惑星タスク"))
		{
			us->rAsteroid.Scaling(16 * 10, 16 * 10);
			Circle cHit(&us->rAsteroid.GetPos(), us->rAsteroid.GetW() * 0.5f);
			if (cHit.CheckHit(&rCursorBase.GetPos()))
			{
				us->rAsteroid.Scaling(16 * 15, 16 * 15);
				if (kb->Down(VK_RETURN)|| pad->Down(J_BUT_6))
				{
					RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
					Add<Back::Obj>();
					Add<Stage21::Obj>();
					Pause(2);
					return;
				}
			}
		}
		if (auto us = Find<StageSelectObjGalaxy::Obj>("銀河タスク"))
		{
			us->rGalaxy.Scaling(16 * 10, 16 * 10);
			Circle cHit(&us->rGalaxy.GetPos(), us->rGalaxy.GetW() * 0.5f);
			if (cHit.CheckHit(&rCursorBase.GetPos()))
			{
				us->rGalaxy.Scaling(16 * 15, 16 * 15);
				if (kb->Down(VK_RETURN)|| pad->Down(J_BUT_6))
				{
					RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
					Add<Back::Obj>();
					Add<Stage31::Obj>();
					Pause(2);
					return;
				}
			}
		}
		if (auto us = Find<StageSelectObjUS::Obj>("天王星タスク"))
		{
			us->rUranus.Scaling(16 * 10, 16 * 10);
			Circle cHit(&us->rUranus.GetPos(), us->rUranus.GetW() * 0.5f);
			if (cHit.CheckHit(&rCursorBase.GetPos()))
			{
				us->rUranus.Scaling(16 * 15, 16 * 15);
				if (kb->Down(VK_RETURN)|| pad->Down(J_BUT_6))
				{
					RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
					Add<Back::Obj>();
					Add<Stage41::Obj>();
					Pause(2);
					return;
				}
			}
		}
		if (auto us = Find<StageSelectObjBH::Obj>("ブラックホール地帯タスク"))
		{
			us->rBH.Scaling(16 * 10, 16 * 10);
			Circle cHit(&us->rBH.GetPos(), us->rBH.GetW() * 0.5f);
			if (cHit.CheckHit(&rCursorBase.GetPos()))
			{
				us->rBH.Scaling(16 * 15, 16 * 15);
				if (kb->Down(VK_RETURN)||pad->Down(J_BUT_6))
				{
					RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
					Add<Back::Obj>();
					Add<Stage51::Obj>();
					Pause(2);
					return;
				}
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		//33
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Frec src(16.f * 32, 16.f, 16.f, 16.f);
			rCursorBase.Draw(&res->iStageImg, &src);
#ifdef _DEBUG
			rCursorBase.Draw();
#endif // _DEBUG
		}
	}
}
