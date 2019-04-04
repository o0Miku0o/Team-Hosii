#pragma once
#include "MyGame/MyApp.h"
#include "Alien.h"

namespace AlienGenerator
{
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
	}*OBJ_ptr;
}