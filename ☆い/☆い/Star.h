#pragma once
#include "MyGame/MyApp.h"

namespace Star
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
		Circle cStarhitbase;
		
		int iChange;
		int iStarEffect;
		Vector2 vMove;
		byte bAlpha;
		char cAddAlpha;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void CheckHit(TaskBase* fragment);
	}*OBJ_ptr;
}