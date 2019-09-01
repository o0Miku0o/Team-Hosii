#pragma once
#include "MyGame/MyApp.h"
#include "StageSelectIcon.h"

namespace Hukidasi
{
	const char caTaskName[] = { "吹き出しタスク" };
	const char caResName[] = { "吹き出しリソース" };

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
		Rec rHukidasi;
	private:
		StageSelectIcon::Type sGroup;
		float faWidth[StageSelectIcon::Type::TYPEMAX];
		float fAddScale;
		float fWidthMax;
		float fHeightMax;
		byte bSetPictureCount;

		RS_ptr res;
		void Init();
		void Finalize();

	public:
		Rec rTextBox;
		void Update();
		void Render();

		void Resize();
		void SetAddScale(const float afAddScale);
		void SetScaleMax(const float afWMax, const float afHMax);
		void SetPos(const Point * const appPos);
		void SetStagePicture(const unsigned int auiStageNumber, const Frec * const apfrPosSize);
		void SetStageGroup(const StageSelectIcon::Type asStageGroup);
	}*Obj_ptr;
}