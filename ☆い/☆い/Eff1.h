#pragma once
#include "MyGame/MyApp.h"

namespace Eff1
{
	enum Type
	{
		TYPE_BEAM,
		TYPE_R_FRG,
		TYPE_Y_FRG,
		TYPE_B_FRG,
		TYPE_MAX
	};
	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iEff1Img;

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

		Obj() {}
		~Obj() {}
	private:
		Rec rEffBase;
		fix fSpdX;
		fix fSpdY;
		fix fAngle;
		fix fAddAngle;
		byte bLifeMax;
		byte bLife;
		Type tType;

		void Init();
		void Finalize();
	public:
		void Update();
		void Render();

		void SetParam(const Rec * const crpcEffBase, const Vector2 * const cvpcSpd, const byte cbLifeMax, const Type ctType, const fix cfAngle = 0.f, const fix cfAddAngle = 0.f);
	}*OBJ_ptr;
}