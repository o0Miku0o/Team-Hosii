#pragma once
#include "MyGame/MyApp.h"

using namespace std;

namespace FragmentGenerator
{
	const char caTaskName[] = { "欠片生成タスク" };
	const char caResName[] = { "欠片生成リソース" };

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
		void Bridge(const int iNum, const Point * const pPos, const int * const iColor);
		void Bridge2(const int iNum, const vector<Point> pPos, const vector<int> iColor);

	}*OBJ_ptr;
}