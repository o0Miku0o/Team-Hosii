#pragma once
#include "MyGame/MyApp.h"

namespace Player
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
		Rec rBase;
		Rec rImgBase;
		Line lGuideLine;
		Line lGuideLineFgm;
		Point pStandardPoint;
		float fSPDist;
		float fSPAngle;
		float fPAngle;
		float fSrcX;

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