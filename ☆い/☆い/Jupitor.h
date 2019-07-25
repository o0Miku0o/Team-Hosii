#pragma once
#include "MyGame/MyApp.h"
#include "Eff1.h"

namespace Jupitor
{
	const char caTaskName[] = { "木星タスク" };
	const char caResName[] = { "木星リソース" };

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
		Rec rJupitor;
		Rec rGravityCircle;
		Circle cJupitorHitBase;
		Circle cGravityCircle;
		int iAnimCount;
		int i;
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
		void BeamCheckhit(TaskBase* bm);
		void FragmentCheckhit(TaskBase* fr);
	}*Obj_ptr;
}