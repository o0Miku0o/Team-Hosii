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
//		iChange = 0;
//		iStarEffect = 0;
		bAlpha = 5;
		cAddAlpha = 5;

		starColor = NonColor;
		starCircle = NonComplete;
		starSound = NonSound;
		starEffect = NonEFT;

		aAnimetor.SetAnim(AnimStar, 0);
//		iChangeCircle = 85;

		iAlpha = 0;
		iCnt = 0;
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

			rStar.Draw(&res->iStageImg, &src, true);

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
			Eff1::Create("./data/effect/ef_star_chipY.txt", &pPos, 0);
			break;
		case Yellow2_Red:
			starColor = Yellow3_Red;
			starEffect = EFTYellow3_Red;
			Eff1::Create("./data/effect/ef_star_chipY.txt", &pPos, 0);
			break;
		case Yellow2_Blue:
			starColor = Yellow3_Blue;
			starEffect = EFTYellow3_Blue;
			Eff1::Create("./data/effect/ef_star_chipY.txt", &pPos, 0);
			break;
		case Yellow2_Red_Blue:
			starColor = Yellow3_Red_Blue;
			starEffect = EFTYellow3_Red_Blue;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullY.txt", &pPos, 0);
			break;
		case Yellow3:
			starColor = Yellow4;
			starEffect = EFTYellow4;
			Eff1::Create("./data/effect/ef_star_chipY.txt", &pPos, 0);
			break;
		case Yellow3_Red:
			starColor = Yellow4_Red;
			starEffect = EFTYellow4_Red;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullY.txt", &pPos, 0);
			break;
		case Yellow3_Blue:
			starColor = Yellow4_Blue;
			starEffect = EFTYellow4_Red;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullY.txt", &pPos, 0);
			break;
		case Yellow4:
			starColor = Yellow5;
			starEffect = EFTYellow5;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullY.txt", &pPos, 0);
			break;
		default:
			starSound = Reflact;
		}
	}
	void Obj::CheckHitRed() {
		starSound = Full;
		pPos = Point(rStar.GetPosX(), rStar.GetPosY() + 25.f);
		switch (starColor) {
		case Yellow2:
			starColor = Yellow2_Red;
			starEffect = EFTYellow2_Red;
			Eff1::Create("./data/effect/ef_star_chipR.txt", &pPos, 0);
			break;
		case Yellow2_Blue:
			starColor = Yellow2_Red_Blue;
			starEffect = EFTYellow2_Red_Blue;
			Eff1::Create("./data/effect/ef_star_chipR.txt", &pPos, 0);
			break;
		case Yellow3:
			starColor = Yellow3_Red;
			starEffect = EFTYellow3_Red;
			Eff1::Create("./data/effect/ef_star_chipR.txt", &pPos, 0);
			break;
		case Yellow3_Blue:
			starColor = Yellow3_Red_Blue;
			starEffect = EFTYellow3_Red_Blue;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullR.txt", &pPos, 0);
			break;
		case Yellow4:
			starColor = Yellow4_Red;
			starEffect = EFTYellow4_Red;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullR.txt", &pPos, 0);
			break;
		default:
			starSound = Reflact;
			break;
		}
	}
	void Obj::CheckHitBlue() {
		starSound = Full;
		pPos = Point(rStar.GetPosX(), rStar.GetPosY() + 25.f);
		switch (starColor) {
		case Yellow2:
			starColor = Yellow2_Blue;
			starEffect = EFTYellow2_Blue;
			Eff1::Create("./data/effect/ef_star_chipB.txt", &pPos, 0);
			break;
		case Yellow2_Red:
			starColor = Yellow2_Red_Blue;
			starEffect = EFTYellow2_Red_Blue;
			Eff1::Create("./data/effect/ef_star_chipB.txt", &pPos, 0);
			break;
		case Yellow3:
			starColor = Yellow3_Blue;
			starEffect = EFTYellow3_Blue;
			Eff1::Create("./data/effect/ef_star_chipB.txt", &pPos, 0);
			break;
		case Yellow3_Red:
			starColor = Yellow3_Red_Blue;
			starEffect = EFTYellow3_Red_Blue;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullB.txt", &pPos, 0);
			break;
		case Yellow4:
			starColor = Yellow4_Blue;
			starEffect = EFTYellow4_Blue;
			starCircle = Complete;
			Eff1::Create("./data/effect/ef_star_fullB.txt", &pPos, 0);
			break;
		default:
			starSound = Reflact;
			break;
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
				static std::string fileName[3] = { "./data/effect/ef_reflect_frgY.txt","./data/effect/ef_reflect_frgR.txt","./data/effect/ef_reflect_frgB.txt" };
				Eff1::Create(fileName[oFragment->iColor], &oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
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
				oFragment->rFragment.SetDeg(rStar.GetDeg(&oFragment->rFragment));
				//oFragment->rFragment.SetPos(&oFragment->pInitPos);
				//oFragment->bMoveActive = false;
			}

			//旧ichange

			//switch (iChange)
			//{
			//case 22:
			//	if (oFragment->iColor == 0)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 23;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 26;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 28;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 23:
			//	iChangeCircle = 85;
			//	if (oFragment->iColor == 0)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 24;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 27;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 29;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 24:
			//	iChangeCircle = 85;
			//	if (oFragment->iColor == 0)
			//	{
			//		iChangeCircle = 86;
			//		iChange = 25;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iChangeCircle = 86;
			//		iChange = 33;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iChangeCircle = 86;
			//		iChange = 32;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 25:
			//	oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//	res->wsTest5.Play();
			//	oFragment->bMoveActive = false;
			//	break;
			//case 26:
			//	iChangeCircle = 85;
			//	if (oFragment->iColor == 0)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 27;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 30;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 27:
			//	iChangeCircle = 85;
			//	if (oFragment->iColor == 2)
			//	{
			//		iChangeCircle = 86;
			//		iChange = 31;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	else
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	break;
			//case 28:
			//	iChangeCircle = 85;
			//	if (oFragment->iColor == 0)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 29;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iChangeCircle = 85;
			//		iChange = 30;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	break;
			//case 29:
			//	iChangeCircle = 85;
			//	if (oFragment->iColor == 1)
			//	{
			//		iChangeCircle = 86;
			//		iChange = 31;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	else
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	break;
			//case 30:
			//	iChangeCircle = 85;
			//	if (oFragment->iColor == 0)
			//	{
			//		iChangeCircle = 86;
			//		iChange = 31;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	else
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	break;
			//case 31:
			//	oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//	res->wsTest5.Play();
			//	oFragment->bMoveActive = false;
			//	break;
			//case 32:
			//	oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//	res->wsTest5.Play();
			//	oFragment->bMoveActive = false;
			//	break;
			//case 33:
			//	oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//	res->wsTest5.Play();
			//	oFragment->bMoveActive = false;
			//	break;
			//}

			//旧ieffct

			//switch (iStarEffect)
			//{
			//case 44:
			//	if (oFragment->iColor == 0)
			//	{
			//		iStarEffect = 45;
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iStarEffect = 46;
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iStarEffect = 47;
			//		Remove(fr);
			//	}
			//	break;
			//case 45:
			//	if (oFragment->iColor == 0)
			//	{
			//		iStarEffect = 46;
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iStarEffect = 47;
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iStarEffect = 48;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 46:
			//	oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//	res->wsTest5.Play();
			//	oFragment->bMoveActive = false;
			//	break;
			//case 47:
			//	oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//	res->wsTest5.Play();
			//	oFragment->bMoveActive = false;
			//	break;
			//case 48:
			//	if (oFragment->iColor == 0)
			//	{
			//		iStarEffect = 49;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iStarEffect = 50;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iStarEffect = 51;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 49:
			//	if (oFragment->iColor == 0)
			//	{
			//		iStarEffect = 49;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iStarEffect = 50;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iStarEffect = 51;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 50:
			//	oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//	res->wsTest5.Play();
			//	oFragment->bMoveActive = false;
			//	break;
			//case 51:
			//	if (oFragment->iColor == 0)
			//	{
			//		iStarEffect = 52;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		iStarEffect = 44;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	break;
			//case 53:
			//	if (oFragment->iColor == 2)
			//	{
			//		iStarEffect = 54;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	else
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	break;
			//case 54:
			//	if (oFragment->iColor == 0)
			//	{
			//		iStarEffect = 55;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 1)
			//	{
			//		iStarEffect = 56;
			//		res->wsTest2.Play();
			//		Remove(fr);
			//	}
			//	if (oFragment->iColor == 2)
			//	{
			//		oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//		res->wsTest5.Play();
			//		oFragment->bMoveActive = false;
			//	}
			//	break;
			//}
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