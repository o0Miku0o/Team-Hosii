#include "Stage4-3.h"
#include "Stage5-1.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "Neptune.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "MeteoGenerator.h"
#include "StageSelect.h"


namespace Stage43
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
		SetName("ステージ４－３タスク");
		/*リソース生成*/
		RB::Add<StageManager::RS>("ステージ統括リソース");

		/*タスクの生成*/
		Add<Player::Obj>();
		auto np = Add<Neptune::Obj>();
		np->rNeptune.Scaling(16.f * 13.f, 16.f * 13.f);
		np->rNeptune.SetPos(&Point(700.f, 850.f));

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor[2] = {};
		Point pFPos[2] = { Point(600.f, 300.f) ,Point(700.f, 650.f) };
		fg->Bridge(2, pFPos, iColor);

		auto sg = Add<StarGenerator::Obj>();
		int iChange[3] = { 23,22,23 };
		Point pSPos[3] = { Point(1700.f, 200.f) ,Point(1600.f, 600.f),Point(1200.f, 900.f) };
		sg->Bridge(3, iChange, pSPos);

		auto bs = Add<BreakStarGenerator::Obj>();
		int iChange4 = 25;
		bool bBSMode = false;
		bs->Bridge(1, &iChange4, &Point(1250.f, 400.f),&bBSMode);

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 1;
		Point pPos[ceiNum] =
		{
			Point(600.f, 250.f),
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveRotation,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectUL,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUL,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimRotation,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		auto met = Add<MeteoGenerator::Obj>();
		met->Bridge(1, &Point(Rec::Win.r, -300), &Vector2(0.f, 15.f));
		/*データの初期化*/

		if (auto sm = Find<StageManager::Obj>("ステージ統括タスク"))
		{
			sm->usBeamCount = 0;
			sm->bClearFragmentNumMax = 7;
			++sm->bNextStage;
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
			Add<Stage51::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<Stage43::Obj>();
			Pause(2);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
