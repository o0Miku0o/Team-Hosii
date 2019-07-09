#pragma once
#include "MyGame/MyApp.h"

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