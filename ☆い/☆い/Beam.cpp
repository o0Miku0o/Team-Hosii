#include "StageManager.h"
#include "Beam.h"
#include "Effect.h"

namespace Beam
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
		SetName("ビームタスク");
		/*リソース生成*/
		//RB::Add<RS>("ビームリソース");
		/*タスクの生成*/

		/*データの初期化*/
		rHitBase = Rec(0.f, Rec::Win.b * 0.5f, 30.f, 16.f);
		bLifeCount = 0;
		vSpd = Vector2::zero;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		//RB::Remove("ビームリソース");
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (bLifeCount >= 120) Remove(this);
		++bLifeCount;
		/*移動ベクトル設定*/
		if (auto prev = FindPrev<Beam::Obj>("ビームタスク"))
		{
			const float ang = rHitBase.GetDeg(&prev->rHitBase);
			rHitBase.SetDeg(ang);
		}
		vSpd.SetVec(rHitBase.GetDeg(), 20.f);
		/*矩形を移動*/
		rHitBase.Move(&vSpd);
		/*エフェクト放出*/
		for (byte b = 0; b < 2; ++b)
		{
			auto ef1 = Add<Eff1::Obj>();
			const fix fAng = ModAngle(rHitBase.GetDeg() + 180.f + (rand() % 21 - 10));
			const fix fRad = DtoR(fAng);
			const fix fSpdX = cos_fast((float)fRad) * 2.f;
			const fix fSpdY = sin_fast((float)fRad) * 2.f;
			Rec rEf(rHitBase.GetPosX() + cos_fast(DtoR(ModAngle(fAng + (b * 180.f - 90.f)))) * (rand() % 9 - 4.f), rHitBase.GetPosY() + sin_fast(DtoR(ModAngle(fAng + (b * 180.f - 90.f)))) * (rand() % 9 - 4.f), 24.f, 3.f, fAng);
			ef1->SetParam(&rEf, &Vector2(fSpdX, fSpdY), 20, Eff1::Type::TYPE_BEAM, fAng);
		}

		/*画面外に出たら消滅*/
		if (rHitBase.GetPosX() > Rec::Win.r + 10.f) Remove(this);
		if (rHitBase.GetPosX() < Rec::Win.l - 10.f) Remove(this);
		if (rHitBase.GetPosY() > Rec::Win.b + 10.f) Remove(this);
		if (rHitBase.GetPosY() < Rec::Win.t - 10.f) Remove(this);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			//rHitBase.Draw(&stageRes->iStageImg, 16 * 10, 0, 16, 16, true, true);

			Frec src(16.f * 10, 0.f, 16.f, 16.f);
			rHitBase.Draw(&stageRes->iStageImg, &src, true);
		}
	}
}
