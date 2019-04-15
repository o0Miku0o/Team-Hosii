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
		Image iHoOverride;
		Image iBoshi;
		Image iBoshiOverride;
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
		Rec rBoshi;
		Rec rStart;
		Rec rMeteo;
		Vector2 vMSpd;
		fix fZoom;
		fix fStartImgSrcY;
		fix fMSpdBase;
		fix fMScale;
		byte bAlpha;
		byte bAddAlpha;
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