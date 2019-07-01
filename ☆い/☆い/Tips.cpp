#include "Tips.h"
//Tipsタスク
//スクショを加工したbmpんｐ画像を貼る
namespace Tips
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		//iTips.ImageCreate("./data/image/other/.bmp");
		iGuideBase.ImageCreate("./data/image/other/GuideBook.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iGuideBase.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);

		/*リソース生成*/
		RB::Add<Tips::RS>(caResName);

		/*タスクの生成*/

		/*データの初期化*/
		rGuideBase = Rec(Rec::Win.r * 0.5f, 700.f, 16.f * 95.f, 16.f * 100.f);

	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<Tips::RS>(caResName))
		{
			rGuideBase.Draw(&res->iGuideBase, &Frec(0.f, 0.f, 64.f, 80.f), true);
		}
	}
}
