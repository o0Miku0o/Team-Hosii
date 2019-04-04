#pragma once
#include "MyGame/MyApp.h"

namespace Stage3
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
		Rec rPlayer;   //宇宙飛行士
		Rec rStar;     //既存の星
		Rec rStarM;    //補う星("M"ake a star)
		Rec rStarR;    //Red
		Rec rStarB;    //Blue
		Rec rBack;     //背景
		Rec rPlanetJ;  //惑星１("J"upiter)
		Rec rPlanetN;  //惑星２("N"eptune)

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
}