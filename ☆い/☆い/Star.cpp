#include "Star.h"
#include "Fragment.h"
#include "StageManager.h"
#include "Title.h"
#include "Result.h"

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
		SetName("星タスク");
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/
		rStar = Rec(Rec::Win.r * 0.75f, Rec::Win.b * 0.5f, 100, 100);
		rStarCircle = Rec(rStar.GetPosX(), rStar.GetPosY(), rStar.GetW()*1.4f, rStar.GetH()*1.4f);
		cStarhitbase = Circle(&rStar.GetPos(), rStar.GetW() / 2);
		iChange = 0;
		iStarEffect = 0;
		bAlpha = 5;
		cAddAlpha = 5;

		aAnimetor.SetAnim(AnimStar, 0);
		iChangeCircle = 85;
		iAlpha = 0;
		iCnt = 0;
		tempCnt = 0;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		rStarCircle = Rec(rStar.GetPosX(), rStar.GetPosY(), rStar.GetW()*1.4f, rStar.GetH()*1.4f);
		auto vFgm = FindAll <Fragment::Obj>("欠片タスク");
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
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Frec src(16.f * iChange, 0, 16.f, 16.f);

			Frec srcE(16.f * iStarEffect, 0, 16.f, 16.f);

			rStar.Draw(&res->iStageImg, &src, true);

			rStar.DrawAlpha(&res->iStageImg, &srcE, bAlpha);

			src = Frec(16.f * aAnimetor.GetSrcX(), 16.f * aAnimetor.GetSrcY(), 16.f, 16.f);

			//rStar.DrawAlpha(&res->iStageImg, &src, 100);
			if (Find<Result::Obj>("リザルトタスク") == nullptr && Find<Title::Obj>("タイトルタスク") == nullptr)
			{
				Frec src2(16.f*iChangeCircle, 0, 16.f, 16.f);
				rStarCircle.DrawAlpha(&res->iStageImg, &src2, iAlpha);
			}
#ifdef _DEBUG
			cStarhitbase.Draw();
#endif // _DEBUG	
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
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				switch (iChange)
				{
				case 22:
					if (oFragment->iColor == 0)
					{
						iChangeCircle = 85;
						iChange = 23;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChangeCircle = 85;
						iChange = 26;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iChangeCircle = 85;
						iChange = 28;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 23:
					iChangeCircle = 85;
					if (oFragment->iColor == 0)
					{
						iChangeCircle = 85;
						iChange = 24;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChangeCircle = 85;
						iChange = 27;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iChangeCircle = 85;
						iChange = 29;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 24:
					iChangeCircle = 85;
					if (oFragment->iColor == 0)
					{
						iChangeCircle = 86;
						iChange = 25;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChangeCircle = 86;
						iChange = 33;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iChangeCircle = 86;
						iChange = 32;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 25:
					oFragment->rFragment.SetPos(&oFragment->pInitPos);
					res->wsTest5.Play();
					oFragment->bMoveActive = false;
					break;
				case 26:
					iChangeCircle = 85;
					if (oFragment->iColor == 0)
					{
						iChangeCircle = 85;
						iChange = 27;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					if (oFragment->iColor == 2)
					{
						iChangeCircle = 85;
						iChange = 30;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 27:
					iChangeCircle = 85;
					if (oFragment->iColor == 2)
					{
						iChangeCircle = 86;
						iChange = 31;
						res->wsTest2.Play();
						Remove(fr);
					}
					else
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 28:
					iChangeCircle = 85;
					if (oFragment->iColor == 0)
					{
						iChangeCircle = 85;
						iChange = 29;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChangeCircle = 85;
						iChange = 30;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 29:
					iChangeCircle = 85;
					if (oFragment->iColor == 1)
					{
						iChangeCircle = 86;
						iChange = 31;
						res->wsTest2.Play();
						Remove(fr);
					}
					else
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 30:
					iChangeCircle = 85;
					if (oFragment->iColor == 0)
					{
						iChangeCircle = 86;
						iChange = 31;
						res->wsTest2.Play();
						Remove(fr);
					}
					else
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 31:
					oFragment->rFragment.SetPos(&oFragment->pInitPos);
					res->wsTest5.Play();
					oFragment->bMoveActive = false;
					break;
				case 32:
					oFragment->rFragment.SetPos(&oFragment->pInitPos);
					res->wsTest5.Play();
					oFragment->bMoveActive = false;
					break;
				case 33:
					oFragment->rFragment.SetPos(&oFragment->pInitPos);
					res->wsTest5.Play();
					oFragment->bMoveActive = false;
					break;
				}

				switch (iStarEffect)
				{
				case 44:
					if (oFragment->iColor == 0)
					{
						iStarEffect = 45;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iStarEffect = 46;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iStarEffect = 47;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 45:
					if (oFragment->iColor == 0)
					{
						iStarEffect = 46;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iStarEffect = 47;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iStarEffect = 48;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 46:
					if (oFragment->iColor == 0)
					{
						iStarEffect = 47;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iStarEffect = 48;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iStarEffect = 49;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 47:
					if (oFragment->iColor == 0)
					{
						iStarEffect = 48;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iStarEffect = 49;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iStarEffect = 50;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 48:
					if (oFragment->iColor == 0)
					{
						iStarEffect = 49;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iStarEffect = 50;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iStarEffect = 51;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
					/*case 49
						if (oFragment->iColor == 0)
						{
							iStarEffect = 49;
							res->wsTest2.Play();
							Remove(fr);
						}
						if (oFragment->iColor == 1)
						{
							iStarEffect = 50;
							res->wsTest2.Play();
							Remove(fr);
						}
						if (oFragment->iColor == 2)
						{
							iStarEffect = 51;
							res->wsTest2.Play();
							Remove(fr);
						}
						break;*/
				case 50:
					oFragment->rFragment.SetPos(&oFragment->pInitPos);
					res->wsTest5.Play();
					oFragment->bMoveActive = false;
					break;
				case 51:
					if (oFragment->iColor == 0)
					{
						iStarEffect = 52;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					if (oFragment->iColor == 2)
					{
						iStarEffect = 44;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 53:
					if (oFragment->iColor == 2)
					{
						iStarEffect = 54;
						res->wsTest2.Play();
						Remove(fr);
					}
					else
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 54:
					if (oFragment->iColor == 0)
					{
						iStarEffect = 55;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iStarEffect = 56;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
					/*case 47:
						if (oFragment->iColor == 1)
						{
							iStarEffect = 47;
							res->wsTest2.Play();
							Remove(fr);
						}
						else
						{
							oFragment->rFragment.SetPos(&oFragment->pInitPos);
							res->wsTest5.Play();
							oFragment->bMoveActive = false;
						}
						break;
					case 48:
						if (oFragment->iColor == 0)
						{
							iStarEffect = 48;
							res->wsTest2.Play();
							Remove(fr);
						}
						else
						{
							oFragment->rFragment.SetPos(&oFragment->pInitPos);
							res->wsTest5.Play();
							oFragment->bMoveActive = false;
						}
						break;
					case 31:
						*/
				case 0:
					iStarEffect = 54;
					break;
				}
			}



			//iChange = min(iChange + 1, 22 + 13);
			//if (iChange > 4)
			//{
			//	iChange = 0;
			//}
			if (auto sm = Find<StageManager::Obj>("ステージ統括タスク"))
			{
				++sm->bClearFragmentNum;
			}
			/*oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->bMoveActive = false;*/
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