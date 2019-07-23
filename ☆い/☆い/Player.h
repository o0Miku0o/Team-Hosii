#pragma once
#include "MyGame/MyApp.h"

namespace Player
{
	const char caTaskName[] = { "プレイヤータスク" };
	const char caResName[] = { "プレイヤーリソース" };

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
		Point pPos;
		float fSPDist;
		float fSPAngle;
		float fPAngle;
		float fSrcX;
		bool bIsReplay;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void BeamCreateFromPad(std::shared_ptr<JoyPad> &apPad);
		void BeamCreateFromKeyBoard(std::shared_ptr<KB> &apKB);
		void BeamCreateFromReplay();
		const float GetAfterPosY(const float afSpdY);
		const float GetSpdFromKeyBoard(std::shared_ptr<KB> &apKB);
		const float GetSpdFromPad(std::shared_ptr<JoyPad> &apPad);
		const float GetSpdFromReplay();
		void ShotAngleFromKeyBoard(std::shared_ptr<KB> &apKB, float afAddAngle);
		void ShotAngleFromPad(std::shared_ptr<JoyPad> &apPad, float afAddAngle);
		void ShotAngleFromReplay();
		void ReplaySeekZero();
		void GuidLine();
	public:
		void Update();
		void Render();
		const Rep *ReplayLoad(const std::string &asRepFileName);
		void ReplayRelease();
	}*Obj_ptr;
}