#include "StageManager.h"
#include "Beam.h"

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
		rHitBase = Rec(0.f, Rec::Win.b * 0.5f, 21.f, 16.f);
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
