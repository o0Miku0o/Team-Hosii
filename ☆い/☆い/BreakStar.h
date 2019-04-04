#pragma once
#include "MyGame/MyApp.h"

namespace BreakStar
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
		Rec rStar;
		Circle cHitbase;
		
		int iChange;
		int iTime;
		bool bHitAct;
		bool bBlackMode;
		Vector2 vMove;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void CheckHit(TaskBase* beam);
	}*OBJ_ptr;
}