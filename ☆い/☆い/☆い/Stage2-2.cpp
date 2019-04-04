#include "Stage2-2.h"
#include "Stage2-3.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "MeteoGenerator.h"
#include "Alien.h"

namespace Stage22
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
		SetName("ステージ１タスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(500.f, Rec::Win.b*0.5f), &iColor);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		//auto sg = Add<BreakStarGenerator::Obj>();
		//int iChange = 25;
		sg->Bridge(1, &iChange, &Point(1500.f, Rec::Win.b*0.5f));

		auto met = Add<MeteoGenerator::Obj>();
		met->Bridge(1, &Point(Rec::Win.r*0.5f, Rec::Win.t - 300), &Vector2(0.f, 15.f));
		//auto ag = Add<AlienGenerator::Obj>();

		//constexpr int ceiNum = 3;
		//Point pPos[ceiNum] =
		//{
		//	Point(1100.f, Rec::win.b * 0.5f),
		//	Point(800.f, 100.f),
		//	Point(500.f, 500.f)
		//};
		//Alien::Move fpMove[ceiNum] =
		//{
		//	Alien::MoveStay,
		//	Alien::MoveStay,
		//	Alien::MoveStay,
		//};
		//Alien::Hit fpBMHit[ceiNum] =
		//{
		//	Alien::BMRemove,
		//	Alien::BMReflectUR,
		//	Alien::BMReflectDR,
		//};
		//Alien::Hit fpFGHit[ceiNum] =
		//{
		//	Alien::FGReflectUR,
		//	Alien::FGReflectDR,
		//	Alien::FGReflectUR,
		//};
		//Alien::Anim fpAnim[ceiNum] =
		//{
		//	Alien::AnimNomal,
		//	Alien::AnimNomal,
		//	Alien::AnimNomal,
		//};

		//ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		/*データの初期化*/

		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			res->wsBGM.PlayL();
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
		if (kb->Now('G') == 1)
		{
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<Stage23::Obj>();
			Pause(2);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
