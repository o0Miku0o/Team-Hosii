#pragma once
#include "MyGame/MyApp.h"

namespace Tips
{
	const char caTaskName[] = { "ポテチタスク" };
	const char caResName[] = { "ポテチリソース" };


	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iTips;
		Image iGuideBase;

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
		Rec rTips;
		Rec rGuideBase;

		Obj() {}
		~Obj() {}
	private:
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	};
}