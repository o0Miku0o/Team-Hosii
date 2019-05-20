#include "Eff1.h"

namespace Eff1
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iEff1Img.ImageCreate("./data/image/other/Effect/eff1.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iEff1Img.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName("エフェクト１タスク");
		/*リソース生成*/
		RB::Add<RS>("エフェクトリソース");
		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(0.3f);

		rEffBase = Rec(0.f, 0.f, 16.f, 16.f);
		fSpdX = 0;
		fSpdY = 0;
		fAngle = 0;
		fAddAngle = 0;
		bLife = 0;
		bLifeMax = 30;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		if (!Find<Obj>("エフェクト１タスク"))
		{
			RB::Remove("エフェクトリソース");
		}
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (bLife >= bLifeMax)
		{
			Remove(this);
			return;
		}
		++bLife;
		Vector2 vSpd(fSpdX, fSpdY);
		rEffBase.Move(&vSpd);
		rEffBase.SetDeg(fAngle);
		fAngle = ModAngle(fAngle + fAddAngle);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<RS>("エフェクトリソース"))
		{
			Frec src(0.f, 16.f * tType, 16.f, 16.f);
			rEffBase.Draw(&res->iEff1Img, &src, true);
		}
	}

	void Obj::SetParam(const Rec * const crpcEffBase, const Vector2 * const cvpcSpd, const byte cbLifeMax, const Type ctType, const fix cfAngle, const fix cfAddAngle)
	{
		rEffBase = *crpcEffBase;
		fSpdX = cvpcSpd->GetX();
		fSpdY = cvpcSpd->GetY();
		fAngle = cfAngle;
		fAddAngle = cfAddAngle;
		bLife = 0;
		bLifeMax = cbLifeMax;
		tType = ctType;
	}
}
