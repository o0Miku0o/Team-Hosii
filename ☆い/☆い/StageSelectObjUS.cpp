#include "StageSelectObjUS.h"
#include "StageSelect.h"
#include "StageManager.h"

namespace StageSelectObjUS
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
		rUranus = Rec(1250, 400 - 200.f, 16 * 10, 16 * 10);
		iAnimCount = 0;
		i = 12;

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
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{

			Frec src(16.f * (iAnimCount + 33), 16, 16, 16);

			if (i >= 15)
			{
				i = 0;
				iAnimCount = (iAnimCount + 1) % 4;
			}
			++i;
			rUranus.Draw(&res->iStageImg, &src);

		}
	}
}
