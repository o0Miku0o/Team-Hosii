#pragma once
#include "MyGame/MyApp.h"

namespace Beam
{
	const char caTaskName[] = { "ビームタスク" };
	const char caResName[] = { "ビームリソース" };

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
		Rec rHitBase;
		Vector2 vSpd;
		byte bLifeCount;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void EffectCreate();
		void OutOfScreen();
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}