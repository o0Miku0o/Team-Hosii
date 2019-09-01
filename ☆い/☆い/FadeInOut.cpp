#include "FadeInOut.h"
#include "StageManager.h"

namespace FadeInOut
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
		SetName(caTaskName);
		/*リソース生成*/
		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(1.f);

		fSize = 960.f;

		//左右上下
		rSquere[0] = Rec(0, 0, 1000, 1080);
		rSquere[1] = Rec(0, 0, 1000, 1080);
		rSquere[2] = Rec(0, 0, 1920, 1000);
		rSquere[3] = Rec(0, 0, 1920, 1000);

		fStarSize = 0;
		fStarSizeValue = 0.f;
		rStar = Rec(Rec::Win.r *0.5f, Rec::Win.b *0.5f, fStarSize, fStarSize);

		bIsIn = true;
		bActive = false;

		/*仮*/
		fStarSizeMax = 5600.f;
		fStarSizeMin = 0.f;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		//fsizeが2120になった瞬間背景が全部埋める
		if (!bActive) {
			if (bIsIn) {
				fStarSizeValue = -32.f;
				fStarSize = fStarSizeMax * 0.5f;
			}
			else {
				fStarSizeValue = 32.f;
				fStarSize = fStarSizeMin;
			}
			bActive = true;
		}
		//else {
		//}

		fStarSize += fStarSizeValue;
		if (bActive)
		{
			if (bIsIn) {
				if (fStarSize <= fStarSizeMin) {
					fStarSize = fStarSizeMin;
					//Remove(this);
				}
			}
			else {
				if (fStarSize >= fStarSizeMax) {
					fStarSize = fStarSizeMax;
					//Remove(this);
				}
			}
		}

		rStar.Scaling(fStarSize, fStarSize);
		rSquere[0].SetPos(&Point(rStar.GetPosX() - rSquere[0].GetW() * 0.45f - fStarSize * 0.45f, rStar.GetPosY()));
		rSquere[1].SetPos(&Point(rStar.GetPosX() + rSquere[1].GetW() * 0.45f + fStarSize * 0.45f, rStar.GetPosY()));
		rSquere[2].SetPos(&Point(rStar.GetPosX(), rStar.GetPosY() - rSquere[2].GetH() * 0.45f - fStarSize * 0.45f));
		rSquere[3].SetPos(&Point(rStar.GetPosX(), rStar.GetPosY() + rSquere[3].GetH() * 0.45f + fStarSize * 0.45f));
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName)) {
			for (int i = 0; i < 4; ++i) {
				Frec src(16, 0, 16, 16);
				rSquere[i].Draw(&res->iStageImg, &src);
			}
			rStar.Draw(&res->tese, &Frec(0, 0, 16, 16));
		}
	}
	/*仮*/
	void Obj::Start()
	{
		bActive = false;
	}
	void Obj::Stop()
	{
		bActive = true;
	}
	const bool Obj::IsComplete() const
	{
		if (bIsIn) return fStarSize <= fStarSizeMin;
		else       return fStarSize >= fStarSizeMax;
		//return fStarSize >= fStarSizeMax || fStarSize <= fStarSizeMin;
	}
}
