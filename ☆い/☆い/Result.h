#pragma once
#include "MyGame/MyApp.h"

namespace Result
{
	const char caTaskName[] = { "リザルトタスク" };
	const char caResName[] = { "リザルトリソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iWord;

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
		Rec rBack;
		Rec rPlayer;
		Rec rWord;
		byte bNextStage;
		byte bMoveStarIdx;
		byte bScore;

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