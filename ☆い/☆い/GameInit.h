#pragma once
#include "MyGame/MyApp.h"

namespace GameInit
{
	const char caTaskName[] = { "ゲーム開始タスク" };
	const char caResName[] = { "ゲーム開始リソース" };

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
	}*Obj_ptr;
}