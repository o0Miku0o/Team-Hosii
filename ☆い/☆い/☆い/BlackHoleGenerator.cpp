#include "BlackHole.h"
#include "BlackHoleGenerator.h"

namespace BlackHoleGenerator
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
		SetName("ブラックホール生成タスク");

		/*リソース生成*/

	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		/*リソースの消去*/
	}
	/*タスクごとの更新処理*/
	void Obj::Update()
	{
		Remove(this);
	}
	/*タスクごとの描画処理*/
	void Obj::Render()
	{
	
	}

	void Obj::Bridge(Point *pPos, const float *pSize, const int mode, Point *pMovePos) {
		auto blackHole = Add<BlackHole::Obj>();
		blackHole->pPos = *pPos;
		blackHole->rBlackHole = Rec(pPos->x, pPos->y, *pSize, *pSize);
		if (mode == Bigger) {
			blackHole->bBigger = true;
		}
		else if (mode == Move) {
			blackHole->bMove = true;
			blackHole->pEndPos = *pMovePos;
		}
	}
}