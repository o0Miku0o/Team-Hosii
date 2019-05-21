#pragma once
#include "MyGame/MyApp.h"

namespace Hukidasi
{
	enum StageGroup
	{
		GROUP_EARTH,
		GROUP_ASTEROID,
		GROUP_GALAXY,
		GROUP_URANUS,
		GROUP_BLACKHOLE
	};
	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iTextImg;

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
		StageGroup sGroup;
		float faWidth[5];
		Rec rHukidasi;
		Rec rTextBox;
		float fAddScale;
		float fWidthMax;
		float fHeightMax;
		byte bSetPictureCount;
			
		RS_ptr res;
		void Init();
		void Finalize();

		void Resize();
	public:
		void Update();
		void Render();

		void SetAddScale(const float afAddScale);
		void SetScaleMax(const float afWMax, const float afHMax);
		void SetPos(const Point * const appPos);
		void SetStagePicture(const unsigned int auiStageNumber, const Frec * const apfrPosSize);
		void SetStageGroup(const StageGroup asStageGroup);
	}*OBJ_ptr;
}