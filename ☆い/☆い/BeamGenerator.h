#pragma once
#include "MyGame/MyApp.h"

namespace BeamGenerator
{
	const char caTaskName[] = { "ビーム生成タスク" };
	const char caResName[] = { "ビーム生成リソース" };

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
		byte bBeamCount;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void BeamCreate(TaskBase *atpPlayer);
		void TitleBeamCreate();
	public:
		void Update();
		void Render();

	}*Obj_ptr;
}