#pragma once
#include "MyGame/MyApp.h"

namespace JecLogo
{
	const char caTaskName[] = { "Jecロゴタスク" };
	const char caResName[] = { "Jecロゴリソース" };
	
	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iLogoImg;
		Image iBlackImg;

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
		Rec rLogoBase;
		int iWaitCnt;
		float fAlpha;
		bool bRev;

		Obj() {}
		~Obj() {}
	private:
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}