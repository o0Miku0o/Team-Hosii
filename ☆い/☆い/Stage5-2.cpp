#include "Stage5-2.h"
#include "Stage5-3.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "Jupitor.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "BlackHoleGenerator.h"
#include "StageSelect.h"
#include "Back.h"

namespace Stage52
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
		SetName("ステージ５－２タスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Back::Obj>();
		Add<Player::Obj>();

		auto np = Add<Jupitor::Obj>();
		np->rJupitor.Scaling(16.f * 18.f, 16.f * 18.f);
		np->rJupitor.SetPos(&Point(1550.f, 540.f));


		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(500.f, 600.f), &iColor);

		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		sg->Bridge(1, &iChange, &Point(1550.f, 260.f));

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 1;
		Point pPos[ceiNum] =
		{
			Point(1000.f, 850.f),
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveHorizontal,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectUR,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUR,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimReflectUR,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		auto bf = Add<BlackHoleGenerator::Obj>();
		float fSize = 400.f;
		const int ciMode = 0;
		bf->Bridge(1, &Point(Rec::Win.r*0.3f, Rec::Win.b*0.3f), &fSize, &ciMode);
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
			Add<Stage53::Obj>();
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
