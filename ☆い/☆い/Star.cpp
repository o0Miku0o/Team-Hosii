#include "Star.h"
#include "Fragment.h"
#include "StageManager.h"
#include "Title.h"
#include "Result.h"
#include "Eff1.h"
#include "MiniGame.h"

namespace Star
{
	/*リソースの初期化処理*/
	void RS::Init()
	{

	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{

	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/
		rStar = Rec(Rec::Win.r * 0.75f, Rec::Win.b * 0.5f, 100, 100);
		rStarCircle = Rec(rStar.GetPosX(), rStar.GetPosY(), rStar.GetW()*1.4f, rStar.GetH()*1.4f);
		cStarhitbase = Circle(&rStar.GetPos(), rStar.GetW() / 2);
		//iChange = 0;
		//iStarEffect = 0;
		bAlpha = 5;
		cAddAlpha = 5;

		starColor = NonColor;
		starCircle = NonComplete;
		starSound = NonSound;
		starEffect = NonEFT;
		aAnimetor.SetAnim(AnimStar, 0);
		//iChangeCircle = 85;

		iAlpha = 0;
		iCnt = 0;

		effsp = Eff1::EffectCreater::SP(new Eff1::EffectCreater("./data/effect/ef_star_chipY.txt"));
		effsp1 = Eff1::EffectCreater::SP(new Eff1::EffectCreater("./data/effect/ef_star_fullY.txt"));
		effsp2 = Eff1::EffectCreater::SP(new Eff1::EffectCreater("./data/effect/ef_reflect_frgY.txt"));
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (starEffect == NonEFT) {
			EffectInit();
		}
		rStarCircle = Rec(rStar.GetPosX(), rStar.GetPosY(), rStar.GetW()*1.4f, rStar.GetH()*1.4f);
		auto vFgm = FindAll <Fragment::Obj>(Fragment::caTaskName);
		if (vFgm.size())
		{
			for (auto &vf : vFgm)
			{
				CheckHit(vf);
			}
		}
		if (bAlpha <= 0 || bAlpha >= 192)
		{
			cAddAlpha = -cAddAlpha;
		}
		bAlpha += cAddAlpha;
		if (iAlpha == 0)
		{
			iCnt = 2;
		}
		else if (iAlpha == 254)
		{
			iCnt = -2;
		}
		iAlpha += iCnt;
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			//Frec src(16.f * iChange, 0, 16.f, 16.f);
			Frec src(16.f * starColor, 0, 16.f, 16.f);
			//Frec srcE(16.f * iStarEffect, 0, 16.f, 16.f);
			Frec srcE(16.f * starEffect, 0, 16.f, 16.f);

			rStar.Draw(&res->iStageImg, &src);

			rStar.DrawAlpha(&res->iStageImg, &srcE, bAlpha);

			src = Frec(16.f * aAnimetor.GetSrcX(), 16.f * aAnimetor.GetSrcY(), 16.f, 16.f);

			//rStar.DrawAlpha(&res->iStageImg, &src, 100);
			if (Find<Result::Obj>(Result::caTaskName) == nullptr && Find<Title::Obj>(Title::caTaskName) == nullptr)
			{
				Frec src2(16.f*starCircle, 0, 16.f, 16.f);
				rStarCircle.DrawAlpha(&res->iStageImg, &src2, iAlpha);
			}
#ifdef _DEBUG
			cStarhitbase.Draw();
#endif // _DEBUG	
		}
	}

	void Obj::EffectInit() {
		switch (starColor) {
		case Yellow2:						starEffect = EFTYellow2;					 break;
		case Yellow2_Red:				starEffect = EFTYellow2_Red;			 break;
		case Yellow2_Blue:				starEffect = EFTYellow2_Blue;			 break;
		case Yellow2_Red_Blue:		starEffect = EFTYellow2_Red_Blue;	 break;
		case Yellow3:						starEffect = EFTYellow3;					 break;
		case Yellow3_Red:				starEffect = EFTYellow3_Red;			 break;
		case Yellow3_Blue:				starEffect = EFTYellow3_Blue;			 break;
		case Yellow3_Red_Blue: 		starEffect = EFTYellow3_Red_Blue;	 break;
		case Yellow4:						starEffect = EFTYellow4;					 break;
		case Yellow4_Red:				starEffect = EFTYellow4_Red;			 break;
		case Yellow4_Blue:				starEffect = EFTYellow4_Blue;			 break;
		case Yellow5:						starEffect = EFTYellow5;					 break;
		}
	}

	void Obj::CheckHitYellow() {
		starSound = Full;
		pPos = Point(rStar.GetPosX(), rStar.GetPosY() + 25.f);
		switch (starColor) {
		case Yellow2:
			starColor = Yellow3;
			starEffect = EFTYellow3;
			break;
		case Yellow2_Red:
			starColor = Yellow3_Red;
			starEffect = EFTYellow3_Red;
			break;
		case Yellow2_Blue:
			starColor = Yellow3_Blue;
			starEffect = EFTYellow3_Blue;
			break;
		case Yellow2_Red_Blue:
			starColor = Yellow3_Red_Blue;
			starEffect = EFTYellow3_Red_Blue;
			starCircle = Complete;
			break;
		case Yellow3:
			starColor = Yellow4;
			starEffect = EFTYellow4;
			break;
		case Yellow3_Red:
			starColor = Yellow4_Red;
			starEffect = EFTYellow4_Red;
			starCircle = Complete;
			break;
		case Yellow3_Blue:
			starColor = Yellow4_Blue;
			starEffect = EFTYellow4_Red;
			starCircle = Complete;
			break;
		case Yellow4:
			starColor = Yellow5;
			starEffect = EFTYellow5;
			starCircle = Complete;
			break;
		default:
			starSound = Reflact;
		}

		if (starCircle == Complete)
		{
			effsp1->_set_chip_type("y_sta");
			effsp1->run(pPos, 0);
		}
		else
		{
			effsp->_set_chip_type("y_sta");
			effsp->run(pPos, 0);
		}
	}

	void Obj::CheckHitRed() {
		starSound = Full;
		pPos = Point(rStar.GetPosX(), rStar.GetPosY() + 25.f);
		switch (starColor) {
		case Yellow2:
			starColor = Yellow2_Red;
			starEffect = EFTYellow2_Red;
			break;
		case Yellow2_Blue:
			starColor = Yellow2_Red_Blue;
			starEffect = EFTYellow2_Red_Blue;
			break;
		case Yellow3:
			starColor = Yellow3_Red;
			starEffect = EFTYellow3_Red;
			break;
		case Yellow3_Blue:
			starColor = Yellow3_Red_Blue;
			starEffect = EFTYellow3_Red_Blue;
			starCircle = Complete;
			break;
		case Yellow4:
			starColor = Yellow4_Red;
			starEffect = EFTYellow4_Red;
			starCircle = Complete;
			break;
		default:
			starSound = Reflact;
			break;
		}

		if (starCircle == Complete)
		{
			effsp1->_set_chip_type("r_sta");
			effsp1->run(pPos, 0);
		}
		else
		{
			effsp->_set_chip_type("r_sta");
			effsp->run(pPos, 0);
		}
	}

	void Obj::CheckHitBlue() {
		starSound = Full;
		pPos = Point(rStar.GetPosX(), rStar.GetPosY() + 25.f);
		//effsp1->_set_chip_type("b_sta");
		//effsp1->run(pPos, 0);

		switch (starColor) {
		case Yellow2:
			starColor = Yellow2_Blue;
			starEffect = EFTYellow2_Blue;
			break;
		case Yellow2_Red:
			starColor = Yellow2_Red_Blue;
			starEffect = EFTYellow2_Red_Blue;
			break;
		case Yellow3:
			starColor = Yellow3_Blue;
			starEffect = EFTYellow3_Blue;
			break;
		case Yellow3_Red:
			starColor = Yellow3_Red_Blue;
			starEffect = EFTYellow3_Red_Blue;
			starCircle = Complete;
			break;
		case Yellow4:
			starColor = Yellow4_Blue;
			starEffect = EFTYellow4_Blue;
			starCircle = Complete;
			break;
		default:
			starSound = Reflact;
			break;
		}

		if (starCircle == Complete)
		{
			effsp1->_set_chip_type("b_sta");
			effsp1->run(pPos, 0);
		}
		else
		{
			effsp->_set_chip_type("b_sta");
			effsp->run(pPos, 0);
		}
	}

	void Obj::SoundPlay(const int SoundNum_) {
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName)) {
			switch (SoundNum_)
			{
			case Full:
				res->wsTest2.Play();
				break;
			case Reflact:
				res->wsTest5.Play();
				break;
			default:
				break;
			}
		}
	}

	void Obj::CheckHit(TaskBase* fr)
	{
		Fragment::Obj* oFragment = (Fragment::Obj*)fr;
		Circle cHit;
		cHit.SetRadius(oFragment->cFragmentHitBase.GetRadius());
		cHit.SetPos(&oFragment->cFragmentHitBase.GetPos());
		if (cStarhitbase.CheckHit(&cHit))
		{
			if (auto mg = Find<MiniGame::Obj>(MiniGame::caTaskName))
			{
				mg->fFragmentCnt++;
			}
			//if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			//{
			switch (oFragment->iColor) {
			case Yellow:
				CheckHitYellow();
				break;
			case Red:
				CheckHitRed();
				break;
			case Blue:
				CheckHitBlue();
				break;
			}

			if (starSound == Full) {
				SoundPlay(Full);
				Remove(fr);
				/*エフェクト放出*/
				/*static std::string fileName[3] = { "./data/effect/ef_star_fullY.txt","./data/effect/ef_star_fullR.txt","./data/effect/ef_star_fullB.txt" };
				Eff1::Create(fileName[oFragment->iColor], &rStar.GetPos(), oFragment->rFragment.GetDeg());*/
				/*byte loopmax = 15;
				for (byte b = 0; b < loopmax; ++b)
				{
					auto ef1 = Add<Eff1::Obj>();
					const fix fAng = ModAngle(-90.f+90.f / loopmax * b);
					Rec rEf(rStar.GetPosX(), rStar.GetPosY(), 5, 5);//constつけなくてもOK
					Vector2 vSpd(cos(DtoR(fAng)) * 5, sin(DtoR(fAng)) * 5);
					Eff1::Type tEffectType = Eff1::Type::TYPE_R_FRG;
					if (oFragment->iColor == 0)
					{
						tEffectType = Eff1::Type::TYPE_Y_FRG;
					}
					else if (oFragment->iColor == 1)
					{
						tEffectType = Eff1::Type::TYPE_R_FRG;
					}
					else if (oFragment->iColor == 2)
					{
						tEffectType = Eff1::Type::TYPE_B_FRG;
					}
					ef1->SetParam(&rEf, &vSpd, 25, tEffectType, fAng);
				}*/
				if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
				{
					++sm->bClearFragmentNum;
				}
			}
			else if (starSound == Reflact) {
				SoundPlay(Reflact);
				/*エフェクト放出*/
				static std::string fileName[3] = { "y_frg","r_frg","b_frg" };
				//Eff1::Create(fileName[oFragment->iColor], &oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
				effsp2->_set_chip_type(fileName[oFragment->iColor]);
				effsp2->run(oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
				/*byte loopmax = 31;
				for (byte b = 0; b < loopmax; ++b)
				{
					auto ef1 = Add<Eff1::Obj>();
					const fix fAng = ModAngle(360.f / loopmax * b);
					Rec rEf(oFragment->rFragment.GetPosX(), oFragment->rFragment.GetPosY(), 5, 5);//constつけなくてもOK
					Vector2 vSpd(cos(DtoR(fAng)) * 10, sin(DtoR(fAng)) * 10);
					Eff1::Type tEffectType = Eff1::Type::TYPE_R_FRG;
					if (oFragment->iColor == 0)
					{
						tEffectType = Eff1::Type::TYPE_Y_FRG;
					}
					else if (oFragment->iColor == 1)
					{
						tEffectType = Eff1::Type::TYPE_R_FRG;
					}
					else if (oFragment->iColor == 2)
					{
						tEffectType = Eff1::Type::TYPE_B_FRG;
					}
					ef1->SetParam(&rEf, &vSpd, 15, tEffectType, fAng);
				}*/
				float f = ModAngle(rStar.GetDeg(&oFragment->rFragment));
				oFragment->rFragment.SetDeg(f);
				//oFragment->rFragment.SetPos(&oFragment->pInitPos);
				//oFragment->bMoveActive = false;
			}
			//iChange = min(iChange + 1, 22 + 13);
			//if (iChange > 4)
			//{
			//	iChange = 0;
			//}

			/*oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->bMoveActive = false;*/
			//		}
		}
	}
	void AnimStar(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 60)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 4;
		}
		++*bFrame;
	}
}