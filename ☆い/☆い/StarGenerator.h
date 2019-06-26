#pragma once
#include "MyGame/MyApp.h"

using namespace std;

namespace StarGenerator
{
	const char caTaskName[] = { "星生成タスク" };
	const char caResName[] = { "星生成リソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*タスクオブジェクトクラス*/
	typedef class Obj : public TaskBase
	{
	public:
		/*必要なメンバはここに追加*/

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void Bridge(const int iNum, const int* iChange, const Point* pPos);
		void Bridge(const int iNum, const vector<int> iChange, const vector<Point> pPos, const vector<float> fSize);
		void Bridge(const int iNum, const vector<int> iChange, const vector<int> iEffect, const vector<Point> pPos);
		void Bridge(const int iNum, const vector<int> iChange, const vector<int> iEffect, const vector<Frec> fRec);
	}*Obj_ptr;
}