#pragma once
#include "MyGame/MyApp.h"
#include "Eff1.h"

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
		Rec rFrg[5] = {};
		Rec rFrg1;
		Rec rFrg2;
		Rec rFrg3;
		Rec rFrg4;

		int iChange;
		int iTime;
		bool bHitAct;
		bool bBlackMode;
		bool bCrach;
		//Vector2 vMove;
		Vector2 vVec;
		int cnt;
		Eff1::EffectCreater::SP effsp;

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
		void FrgCreate();
	}*Obj_ptr;
}