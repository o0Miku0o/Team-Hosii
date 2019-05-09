#pragma once
#include "MyGame/MyApp.h"

namespace Hukidasi
{
	enum PictureGroup
	{
		GROUP_UP,
		GROUP_DOWN,
	};
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
		PictureGroup pGroup;
		Rec rHukidasi;
		Point pFontPos[2];
		float fAddScale;
		float fWidthMax;
		float fHeightMax;
		byte bIsSetPictureCount;
			
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
		void SetStageGroup(const PictureGroup asStageGroup);
	}*OBJ_ptr;
}