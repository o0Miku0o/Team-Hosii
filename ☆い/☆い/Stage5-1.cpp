#include "Stage5-1.h"
#include "Stage5-2.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "BlackHoleGenerator.h"
#include "StageSelect.h"
#include "Back.h"

//#include "BlackHole.h"

namespace Stage51
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
		SetName("ステージ５－１タスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Back::Obj>();
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor[2] = {};
		Point pFPos[2] = { Point(500.f, 200.f) ,Point(500.f, 800.f) };
		fg->Bridge(2, pFPos, iColor);

		auto sg = Add<StarGenerator::Obj>();
		int iChange = 23;
		sg->Bridge(1, &iChange, &Point(1700.f, 540.f));

		auto bf = Add<BlackHoleGenerator::Obj>();
		float fSize = 250.f;
		const int ciMode = 0;
		bf->Bridge(1, &Point(Rec::Win.r*0.5f, Rec::Win.b*0.5f), &fSize, &ciMode);

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
			Add<Stage52::Obj>();
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
