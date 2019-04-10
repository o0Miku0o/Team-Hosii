#include "Stage5-3.h"
#include "Stage5-1.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "StageSelect.h"

//#include "BlackHole.h"

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
		RB::Add<StageManager::RS>("ステージ統括リソース");

		/*タスクの生成*/
		Add<Player::Obj>();
		//Add<BlackHole::Obj>();
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

		if (auto sm = Find<StageManager::Obj>("ステージ統括タスク"))
		{
			sm->usBeamCount = 0;
			sm->bClearFragmentNumMax = 5;
			sm->bNextStage = 1;
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
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<Stage53::Obj>();
			Pause(2);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
