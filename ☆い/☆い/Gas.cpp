#include "Gas.h"
#include "Title.h"
#include "StageManager.h"

//素材は4(種類)×2(アニメーションあり)
//位置は多分87から94
//ランダムで出すようにしたい
//タイトル＆ステージで使えるようにしたい
//三枝先生からのお言葉「最後の方でいいかな」
namespace Gas
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
		SetName("ガスタスク");
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/

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
			rGus.Draw(&res->iStageImg, &Frec(16.f * 87.f, 0.f, 16.f, 16.f));
		}

	}
}
