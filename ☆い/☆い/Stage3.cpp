#include "Stage1.h"
#include "Stage3.h"
#include "StageManager.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "Player.h"
#include "Neptune.h"
#include "Jupitor.h"

namespace Stage3
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
		SetName("ステージ３タスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Player::Obj>();
		auto np = Add<Neptune::Obj>();
		auto jp = Add<Jupitor::Obj>();

		Point pJp(jp->cGravityCircle.GetPos().x + jp->cGravityCircle.GetRadius()-1, jp->cGravityCircle.GetPos().y);
		Point pNp(np->cGravityCircle.GetPos().x + np->cGravityCircle.GetRadius()-1, np->cGravityCircle.GetPos().y);
		auto fg = Add<FragmentGenerator::Obj>();
		Point pArr[2] = { pJp , pNp };
		fg->Bridge(2, pArr, 1);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 23;
		sg->Bridge(1, &iChange, &Point(1650.f, 500.f));
		/*データの初期化*/
		//背景
		rBack = Rec(Rec::Win.r / 2, Rec::Win.b / 2, Rec::Win.r, Rec::Win.b);

		//↓仮のサイズ(調整するために好きに変更してください)
		rPlayer = Rec(250, 100, 16 * 8, 16 * 8);
		rStar = Rec(1600, 300, 16 * 7, 16 * 7);
		//rStarM = Rec(500, 500, 16 * 5, 16 * 5);
		rStarB = Rec(800, 500, 16 * 5, 16 * 5);
		rStarB.SetDeg(160);
		rStarR = Rec(1350, 500, 16 * 5, 16 * 5);
		rStarR.SetDeg(150);

		//アニメーションあり(後ほど追加するので今回は反時計回りに画像を回転させてください)
		rPlanetJ = Rec(800, 270, 16 * 20, 16 * 20);
		rPlanetJ.SetDeg(90);
		rPlanetN = Rec(1350, 680, 16 * 14, 16 * 14);
		rPlanetN.SetDeg(90);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		if (kb->Now('A') == 1)
		{
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<Stage1::Obj>();
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
