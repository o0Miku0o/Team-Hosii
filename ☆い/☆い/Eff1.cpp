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
		SetName(caTaskName);
		/*リソース生成*/
		RB::Add<RS>(caResName);
		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(0.3f);

		rEffBase = Rec(0.f, 0.f, 16.f, 16.f);
		fSpdX = 0;
		fSpdY = 0;
		fAddSpdX = 0;
		fAddSpdY = 0;
		fAngle = 0;
		fAddAngle = 0;
		bLife = 0;
		bLifeMax = 30;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		if (!Find<Obj>(caTaskName))
		{
			RB::Remove(caResName);
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
		fSpdX += fAddSpdX;
		fSpdY += fAddSpdY;
		fAngle = ModAngle(fAngle + fAddAngle);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<RS>(caResName))
		{
			Frec src(0.f, 16.f * tType, 16.f, 16.f);
			rEffBase.Draw(&res->iEff1Img, &src, true);
		}
	}

	void Obj::SetParam(const Rec * const crpcEffBase, const Vector2 * const cvpcSpd, const byte cbLifeMax, const ChipType ctType, const float cfAngle, const float cfAddAngle, const Vector2 * const vAddSpd)
	{
		rEffBase = *crpcEffBase;
		fAddSpdX = vAddSpd->GetX();
		fAddSpdY = vAddSpd->GetY();
		fSpdX = cvpcSpd->GetX() - (fAddSpdX * 10);
		fSpdY = cvpcSpd->GetY() - (fAddSpdY * 10);
		fAngle = cfAngle;
		fAddAngle = cfAddAngle;
		bLife = 0;
		bLifeMax = cbLifeMax;
		tType = ctType;
	}

	void CreateOugi(const int iNum, const ChipType cType, const Point * const pPos, const float fInitAngle, const float fMax, const float fMin, const byte bLife, const float fSpd, const Vector2 * const vAddSpd)
	{
		const float fIAngle = ModAngle(fInitAngle + 180.f);
		const float fRange = Abs((float)fMax - fMin);
		for (int i = 0; i < iNum; ++i)
		{
			auto ef1 = TB::Add<Eff1::Obj>();
			const float fAng = ModAngle(fIAngle - fMin + (fRange / iNum) * i + (rand() % 21 - 10.f));
			Vector2 vSpd;
			vSpd.SetVec(fAng, rand() % 3 + fSpd);
			const Rec rEf(pPos->x, pPos->y, 8.f, 8.f, fAng);
			ef1->SetParam(&rEf, &vSpd, bLife, cType, fAng, 0.f, vAddSpd);
		}
	}
	void CreateHanabi(const int iNum, const ChipType cType, const Point * const pPos, const float fInitAngle, const byte bLife, const float fSpd, const Vector2 * const vAddSpd)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto ef1 = TB::Add<Eff1::Obj>();
			const float fAngle = ModAngle(fInitAngle + (360.f / iNum) * i);
			Vector2 vSpd;
			vSpd.SetVec(fAngle, (rand() % 3 + fSpd));
			const Rec rEf(pPos->x, pPos->y, 8.f, 8.f, fAngle);
			ef1->SetParam(&rEf, &vSpd, bLife, cType, fAngle, 0.f, vAddSpd);
		}
	}
}
