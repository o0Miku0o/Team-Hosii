#pragma once
#include "MyGame/MyApp.h"

namespace Gas
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
		Rec rGas[3];
		Animation aAnim;
		byte bAlpha;
		float fMove;
		enum GasColor
		{
			White,
			Blue,
			Yellow,
			Purple
		};
		GasColor gGasColor[4];
		int iGNum;
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
	void AnimGasW(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimGasB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimGasY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimGasP(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
}