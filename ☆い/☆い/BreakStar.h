#pragma once
#include "MyGame/MyApp.h"

namespace BreakStar
{
	const char caTaskName[] = { "壊す星タスク" };
	const char caResName[] = { "壊す星リソース" };

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
		void BeamCheckHit(TaskBase* beam);
		void FragmentCheckHit(TaskBase* fragment);
	}*Obj_ptr;
}