#include "Stage2.h"
#include "Stage3.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "Meteo.h"

namespace Stage2
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
		SetName("ステージ２タスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Player::Obj>();

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 1;
		Point pPos[ceiNum] =
		{
			Point(1400.f, Rec::Win.b * 0.5f),
			//Point(800.f, 100.f),
			//Point(500.f, 500.f)
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveVertical,
			//Alien::MoveHorizontal,
			//Alien::MoveRotation,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMRemove,
			//Alien::BMReflectUR,
			//Alien::BMReflectDR,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGRemove,
			//Alien::FGReflectDR,
			//Alien::FGReflectUR,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimNomal,
			//Alien::AnimNomal,
			//Alien::AnimRotation,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		//Add<Alien::Obj>();
		Add<Meteo::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		fg->Bridge(1, &Point(Rec::Win.r * 0.4f, Rec::Win.b * 0.5f), 1);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		sg->Bridge(1, &iChange, &Point(1650.f, 700.f));
		/*データの初期化*/

	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		if (kb->Now('T') == 1)
		{
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<Stage3::Obj>();
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
