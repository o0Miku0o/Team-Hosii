#pragma once
#include "MyGame/MyApp.h"
#include "../☆い/MyGame/My/EventMsg.h"

namespace TimeAttack
{
	const char caTaskName[] = { "タイムアタックタスク" };
	const char caResName[] = { "タイムアタックリソース" };

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
		int iTimeCnt;
		int iFrameCnt;
		std::string str;
		Point pos;
		float width, height;
		EventMsg timeMsg;

		Obj() {}
		~Obj() {}
	private:

		RS_ptr res;
		void Init();
		void Finalize();

	public:
		void Update();
		void Render();

	}*OBJ_ptr;
}