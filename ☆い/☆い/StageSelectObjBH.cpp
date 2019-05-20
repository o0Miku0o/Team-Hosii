#include "StageSelectObjBH.h"
#include "StageManager.h"

namespace StageSelectObjBH
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
		SetName("ブラックホール地帯タスク");
		/*リソース生成*/
		/*タスクの生成*/

		/*データの初期化*/
		rBH = Rec(1500, 600 - 200.f, 16 * 10, 16 * 10);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		//rBH.SetDeg(rBH.GetDeg() + 4);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Frec src(16.f * (iAnimCount + 53), 16, 16, 16);

			if (i >= 15)
			{
				i = 0;
				iAnimCount = (iAnimCount + 2) % 8;
			}
			++i;
			rBH.Draw(&res->iStageImg, &src);
		}
	}
}
