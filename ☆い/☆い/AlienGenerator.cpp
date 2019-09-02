#include "AlienGenerator.h"

namespace AlienGenerator
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

	void Obj::Bridge(const int iNum, const Point* pPos, Alien::Move *fpMove, Alien::Hit *fpBMHit, Alien::Hit *fpFGHit, Alien::Anim *fpAnim)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto alien = Add<Alien::Obj>();
			alien->pCenter = *(pPos + i);
			alien->moveFunc = *(fpMove + i);
			alien->BMHitFunc = *(fpBMHit + i);
			alien->FGHitFunc = *(fpFGHit + i);
			alien->AnimFunc = *(fpAnim + i);
		}
		Remove(this);
	}
	void Obj::Bridge(const int iNum, const vector<Point> pPos, const vector<Alien::Move> fpMove, const vector <Alien::Hit> fpBMHit,
		const vector<Alien::Hit> fpFGHit, const vector<Alien::Anim> fpAnim) {
		for (int i = 0; i < iNum; ++i)
		{
			auto alien = Add<Alien::Obj>();
			alien->pCenter = pPos.at(i);
			alien->moveFunc = fpMove.at(i);
			alien->BMHitFunc = fpBMHit.at(i);
			alien->FGHitFunc = fpFGHit.at(i);
			alien->AnimFunc = fpAnim.at(i);
		}
		Remove(this);
	}
}
