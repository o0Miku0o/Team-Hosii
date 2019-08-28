#pragma once
#include "MyGame/MyApp.h"
#include "../☆い/MyGame/My/EventMsg.h"

namespace MiniGame
{
	const char caTaskName[] = { "ミニゲームタスク" };
	const char caResName[] = { "ミニゲームリソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iButton;

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
		Rec rButton;
		float fFragmentCnt;
		int score;
		float width, height;
		Point pos1,pos2;
		std::string str[2];
		EventMsg myMsg;
		EventMsg highMsg;
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