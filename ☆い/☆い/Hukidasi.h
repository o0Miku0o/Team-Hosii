#pragma once
#include "MyGame/MyApp.h"

namespace Hukidasi
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
		Rec rHukidasi;
		float fAddScale;
		float fWidthMax;
		float fHeightMax;
		bool bIsSetPicture;
			
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
	}*OBJ_ptr;
}