#include "FragmentGenerator.h"
#include "Fragment.h"

namespace FragmentGenerator
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
		SetName("欠片生成タスク");
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
	}
	void Obj::Bridge(const int iNum, const Point *  pPos, const int * const iColor)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto fragment = Add<Fragment::Obj>();
			fragment->rFragment.SetPos(pPos + i);
			fragment->cFragmentHitBase.SetPos(pPos + i);
			fragment->pInitPos = *(pPos + i);
			fragment->iColor = *(iColor + i);
		}
		Remove(this);
	}
	void Obj::Bridge2(const int iNum, const vector<Point> pPos, const vector<int> iColor)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto fragment = Add<Fragment::Obj>();
			fragment->rFragment.SetPos(&pPos.at(i));
			fragment->cFragmentHitBase.SetPos(&pPos.at(i));
			fragment->pInitPos = pPos.at(i);
			fragment->iColor = iColor.at(i);
		}
		Remove(this);
	}
}
