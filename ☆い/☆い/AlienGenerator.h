#pragma once
#include "MyGame/MyApp.h"
#include "Alien.h"

using namespace std;

namespace AlienGenerator
{
	const char caTaskName[] = { "宇宙人生成タスク" };
	const char caResName[] = { "宇宙人生成リソース" };

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

		void Bridge(const int iNum, const Point* pPos, Alien::Move *fpMove, Alien::Hit *fpBMHit, Alien::Hit *fpFGHit, Alien::Anim *fpAnim);
		void Bridge(const int iNum, const vector<Point> pPos, const vector<Alien::Move> fpMove, const vector <Alien::Hit> pBMHit, 
			const vector<Alien::Hit> fpFGHit, const vector<Alien::Anim> fpAnim);
	}*Obj_ptr;
}