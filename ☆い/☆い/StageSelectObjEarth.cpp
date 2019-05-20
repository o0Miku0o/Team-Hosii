#include "StageSelectObjEarth.h"
#include "StageManager.h"

namespace StageSelectObjEarth
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
		SetName("地球タスク");
		/*リソース生成*/
		/*タスクの生成*/

		/*データの初期化*/
		rEarth = Rec(400, 600 - 200.f, 16 * 10, 16 * 10);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Frec src(16.f * (iAnimCount + 37), 16, 16, 16);

			if (i >= 16)
			{
				i = 0;
				iAnimCount = (iAnimCount + 1) % 4;
			}
			++i;
			rEarth.Draw(&res->iStageImg, &src, true);
		}
	}
}
