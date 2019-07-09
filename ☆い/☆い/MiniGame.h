#pragma once
#include "MyGame/MyApp.h"

namespace MiniGame
{
	const char caTaskName[] = { "ミニゲームタスク" };
	const char caResName[] = { "ミニゲームリソース" };

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
		int iFragmentCnt;

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