#pragma once
#include "MyGame/MyApp.h"
#include "Eff1.h"

namespace Star
{
	const char caTaskName[] = { "星タスク" };
	const char caResName[] = { "星リソース" };

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
	typedef RS* RS_ptr;
	/*タスクオブジェクトクラス*/
	typedef class Obj : public TaskBase
	{
	public:
		/*必要なメンバはここに追加*/
		Rec rStar;
		Rec rStarCircle;
		Circle cStarhitbase;
		Animation aAnimetor;

//		int iChange;
//		int iStarEffect;
//		int iChangeCircle;
		int iAlpha;
		int iCnt;
		Vector2 vMove;
		byte bAlpha;
		char cAddAlpha;
		Point pPos;

		Eff1::EffectCreater::SP effsp;
		Eff1::EffectCreater::SP effsp1;
		Eff1::EffectCreater::SP effsp2;

		enum StarColor {
			Yellow2 = 22,
			Yellow2_Red = 26,
			Yellow2_Blue = 28,
			Yellow2_Red_Blue = 30,
			Yellow3 = 23,
			Yellow3_Red = 27,
			Yellow3_Blue = 29,
			Yellow3_Red_Blue = 31,
			Yellow4 = 24,
			Yellow4_Red = 33,
			Yellow4_Blue = 32,
			Yellow5 = 25,

			NonColor = -1,
		}starColor;
		enum StarEffect {
			EFTYellow2 = 44,
			EFTYellow3 = 45,
			EFTYellow4 = 46,
			EFTYellow3_Blue = 46,
			EFTYellow5 = 47,
			EFTYellow3_Red_Blue = 47,
			EFTYellow4_Red = 47,
			EFTYellow4_Blue =47,
			EFTYellow2_Red = 48,
			EFTYellow3_Red = 49,
			EFTYellow2_Blue = 50,
			EFTYellow2_Red_Blue = 51,

			NonEFT = -1,
		}starEffect;
		enum Color {
			Yellow = 0,
			Red = 1,
			Blue = 2,
		};
		enum StarCircle {
			NonComplete = 85, Complete = 86
		}starCircle;
		enum StarSound {
			Full = 2, Reflact = 5, NonSound = -1
		}starSound;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void EffectInit();

		void CheckHitYellow();
		void CheckHitRed();
		void CheckHitBlue();

		void SoundPlay(const int bSoundNum_);
	public:
		void Update();
		void Render();
		void CheckHit(TaskBase* fragment);
	}*Obj_ptr;
	void AnimStar(byte* const bFrame, byte* const bSrcX, byte* const bSrcY);
}