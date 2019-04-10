#include "StarGenerator.h"
#include "Star.h"

namespace StarGenerator
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
		SetName("星生成タスク");
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
	void Obj::Bridge(const int iNum, const int* iChange, const Point* pPos)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto star = Add<Star::Obj>();
			star->rStar.SetPos(pPos + i);
			star->cStarhitbase.SetPos(pPos + i);
			star->iChange = *(iChange+i);
		}
		Remove(this);
	}
	void Obj::Bridge(const int iNum, const vector<int> iChange, const vector<Point> pPos) {
		for (int i = 0; i < iNum; ++i)
		{	
			auto star = Add<Star::Obj>();
			star->rStar.SetPos(&pPos.at(i));
			star->cStarhitbase.SetPos(&pPos.at(i));
			star->iChange = iChange.at(i);
		}
		Remove(this);
	}

}
