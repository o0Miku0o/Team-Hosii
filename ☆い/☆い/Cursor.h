#pragma once
#include "MyGame/MyApp.h"
#include "MyGame/My/Move.h"

namespace Cursor
{
	const char caTaskName[] = { "カーソルタスク" };
	const char caResName[] = { "カーソルリソース" };

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
		std::shared_ptr<Move> spMove;
		Rec rCursorBase;
		Point pPos;
		float fSpd;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void MoveKeyBoard(std::shared_ptr<KB> &apKB);
		void MovePad(std::shared_ptr<JoyPad> &apPad);
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}