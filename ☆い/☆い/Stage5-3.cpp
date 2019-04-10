#include "Stage5-3.h"
#include "Stage5-1.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "StageSelect.h"
#include "Back.h"

namespace Stage53
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
		SetName("ステージ５－３タスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Back::Obj>();
		Add<Player::Obj>();
		//黒い星５個↓
		auto bs = Add<BreakStarGenerator::Obj>();
		int iChange[6] = { 36,36,36,36,36,25 };
		Point pBPos[6] = { Point(600.f, 0.f),Point(700.f,1080.f),Point(1600.f, 540.f),Point(1920.f, 0.f), Point(1900.f, 1000.f) ,Point(600.f, 540.f) };
		bool bBSMode[6] = { true,true, true, true, true, false };
		bs->Bridge(6, iChange, pBPos,bBSMode);

		//壊れる星

		//目的の星
		auto sg = Add<StarGenerator::Obj>();
		int iChange3[2] = { 22,23 };
		Point pSPos[2] = { Point(1200.f, 850.f),Point(1100.f, 200.f) };
		sg->Bridge(2, iChange3, pSPos);

		/*データの初期化*/

		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			res->wsBGM.Restart();
		}
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);
		if (kb->Now('G') == 1 || pad->NowBut(J_BUT_8) == 1)
		{
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				res->wsBGM.Pause();
			}
			Add<Back::Obj>();
			Add<StageSelect::Obj>();
			Pause(2);
		}

		if (pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				res->wsBGM.Pause();
			}
			Add<Back::Obj>();
			Add<StageSelect::Obj>();
			Pause(2);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b).Draw(&res->iStageImg, &Frec(16.f * 0.f, 0.f, 16.f, 16.f));
		}
	}
}
