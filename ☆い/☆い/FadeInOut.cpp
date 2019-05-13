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
		SetName("フェイドインアウトタスク");
		/*リソース生成*/
		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(1.f);

		fSize = 0.f;

		rec[0] = Rec(Rec::Win.r, Rec::Win.t, fSize, fSize, 45.f);
		rec[1] = Rec(Rec::Win.l, Rec::Win.t, fSize, fSize, 135.f);
		rec[2] = Rec(Rec::Win.r, Rec::Win.b, fSize, fSize, 225.f);
		rec[3] = Rec(Rec::Win.l, Rec::Win.b, fSize, fSize, 315.f);

		bIsIn = true;
		bActive = false;
		fSizeValue = 0.f;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		//EndPositon<FadeInOut::Obj>("フェイドインアウトタスク");
		//fsizeが2120になった瞬間背景が全部埋める
		if (!bActive) {
			if (bIsIn) {
				fSizeValue = 16.f;
				fSize = 0.f;
			}
			else {
				fSizeValue = -16.f;
				fSize = 2120.f;
			}
			bActive = true;
		}
		else {
			if (!bIsIn) {
				if (fSize < 0) {
					Remove(this);
				}
			}
		}

		fSize += fSizeValue;
		for (int i = 0; i < 4; ++i)
			rec[i].Scaling(fSize, fSize);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース")) {
			for (int i = 0; i < 4; ++i)
				rec[i].Draw(&res->iStageImg, &Frec(16, 0, 16, 16), false);
		}
	}
}
