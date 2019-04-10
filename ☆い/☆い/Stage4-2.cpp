#include "Stage4-2.h"
#include "Stage4-3.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "MeteoGenerator.h"
#include "StageSelect.h"
#include "Back.h"

namespace Stage42
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
		SetName("ステージ４－２タスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Back::Obj>();
		Add<Player::Obj>();

		auto met = Add<MeteoGenerator::Obj>();
		met->Bridge(1, &Point(1300.f, -300.f), &Vector2(0.f, 12.f));
	
		auto sg = Add<StarGenerator::Obj>();
		int iChange[3] = { 23,23,24 };
		Point pSPos[3] = { Point(1600.f, 200.f) ,Point(1600.f, 880.f) ,Point(1600.f,540.f) };
		sg->Bridge(3, iChange, pSPos);

		auto bs = Add<BreakStarGenerator::Obj>();
		int iChange4 = 25;
		bool bBSMode = false;
		bs->Bridge(1, &iChange4, &Point(600.f, 540.f),&bBSMode);
	
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
			Add<Stage43::Obj>();
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
