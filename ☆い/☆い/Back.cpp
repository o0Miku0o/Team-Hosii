#include "Back.h"
#include "Title.h"
#include "StageManager.h"
#include "MeteoGenerator.h"

namespace Back
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
		SetName("背景タスク");
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/
		for (auto &ap : pBackStar)
		{
			ap.SetPos(&Point(float(rand() % int(Rec::Win.r)), float(rand() % int(Rec::Win.b))));
		}
		rBackBase = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b);
		lShootingStar = Line();
		bSSLife = 0;
		bSSLifeMax = 60;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		BackStarUpdate();

		ShootingStarUpdate();
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		BackBaseDraw();

		BackStarDraw();

		ShootingStarDraw();
	}
	/*流れ星の更新*/
	void Obj::ShootingStarUpdate()
	{
		lShootingStar.Move(20.f);
		if (bSSLife >= bSSLifeMax)
		{
			bSSLife = 0;
			lShootingStar.SetLen(0.f);
			lShootingStar.SetPos(&Point(float(rand() % int(Rec::Win.r)), float(rand() % int(Rec::Win.b))));
			lShootingStar.SetDeg(float(rand() % 360));
		}
		else if (bSSLife < byte(bSSLifeMax * 0.5f))
		{
			lShootingStar.SetLen(lShootingStar.GetLen() + 10.f);
		}
		else
		{
			lShootingStar.SetLen(lShootingStar.GetLen() - 10.f);
		}
		++bSSLife;
	}
	/*背景の星の更新*/
	void Obj::BackStarUpdate()
	{
		for (auto &ap : pBackStar)
		{
			if (rand() % 91 == 1)
			{
				const byte bC = (byte)rand() % 206 + 50;
				ap.SetColor(RGB(bC, bC, bC));
			}
		}
	}
	/*背景画像の描画*/
	void Obj::BackBaseDraw()
	{
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			rBackBase.Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		}
	}
	/*流れ星の描画*/
	void Obj::ShootingStarDraw()
	{
		if (lShootingStar.GetLen() > 0.f)
		{
			lShootingStar.Draw();
		}
	}
	/*背景の星の更新*/
	void Obj::BackStarDraw()
	{
		auto ti = Find<Title::Obj>("タイトルタスク");
		for (auto &ap : pBackStar)
		{
			if (ti)
			{
				if (ti->rBoshi.CheckHit(&ap.GetPos()) || ti->rHo.CheckHit(&ap.GetPos())) continue;
			}
			ap.Draw();
		}
	}
}
