#pragma once
#include "MyGame/MyApp.h"

namespace Title
{
	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iHo;
		Image iShi;
		Image iBoshi;
		Image iStart;

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
		Rec rHo;
		Rec rShi;
		Rec rBoshi;
		Rec rStart;
		Animation aAnimator1;
		Animation aAnimator2;
		float fZoom;
		bool bShineFlag;

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
	void AnimHo(byte * const bFrame, byte * const bAnim, byte * const bAnim2);
	void AnimShiBoshi(byte * const bFrame, byte * const bAnim, byte * const bAnim2);
}