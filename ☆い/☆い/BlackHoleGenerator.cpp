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

	void Obj::Bridge(const int iNum, const Point *pPos, const float *pSize, const int* mode, const Point *pMovePos) {
		for (int i = 0; i < iNum; i++) {
			auto blackHole = Add<BlackHole::Obj>();
			blackHole->pPos = *(pPos + i);
			blackHole->rBlackHole = Rec((pPos + i)->x, (pPos + i)->y, *(pSize + i), *(pSize + i));
			if (*(mode + i) == Bigger) {
				blackHole->bBigger = true;
			}
			else if (*(mode + i) == Move) {
				blackHole->bMove = true;
				blackHole->pEndPos = *(pMovePos + i);
			}
		}
	}
	void Obj::Bridge(const int iNum, const vector<Point> pPos, const vector<float> pSize, const vector<int> mode, const vector<Point>* pMovePos) {
		for (int i = 0; i < iNum; i++) {
			auto blackHole = Add<BlackHole::Obj>();
			blackHole->pPos = pPos.at(i);
			blackHole->rBlackHole = Rec(pPos.at(i).x, pPos.at(i).y, pSize.at(i), pSize.at(i));
			if (mode.at(i) == Bigger) {
				blackHole->bBigger = true;
			}
			else if (mode.at(i) == Move) {
				blackHole->bMove = true;
				blackHole->pEndPos = pMovePos->at(i);
			}
		}
	}
}