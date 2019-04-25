#pragma once
#include "MyGame/MyApp.h"

namespace Back
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

		Obj() {}
		~Obj() {}
	private:
		Pixel pBackStar[560];
		Rec rBackBase;
		Line lShootingStar;
		byte bSSLife;
		byte bSSLifeMax;

		RS_ptr res;
		void Init();
		void Finalize();

		void ShootingStarUpdate();
		void BackStarUpdate();

		void BackBaseDraw();
		void ShootingStarDraw();
		void BackStarDraw();
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
}