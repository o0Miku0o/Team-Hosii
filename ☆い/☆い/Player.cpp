#include "Player.h"
#include "StageManager.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "Fragment.h"
#include "FadeInOut.h"

//#include "Rail.h"

namespace Player
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
		//Add<Rail::Obj>();
		/*データの初期化*/
		SetRenderPriority(0.2f);

		rBase = Rec(Rec::Win.l + 100.f, Rec::Win.b * 0.5f, 16 * 8.f, 16 * 8.f, 180);
		rImgBase = rBase;
		pStandardPoint = Point(Rec::Win.r - 500.f, Rec::Win.b * 0.5f);
		fSPDist = rBase.GetDist(&pStandardPoint);
		fSPAngle = (float)rBase.GetDeg(&pStandardPoint) + 180;
		fPAngle = fSPAngle;
		lGuideLine.SetLen(2000.f);
		lGuideLine.SetColor(130, 130, 255);
		lGuideLineFgm.SetColor(255, 130, 130);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
		{
			if (fade->IsComplete())
			{
				const auto pad = JoyPad::GetState(0);
				const auto kb = KB::GetState();
				if (pad->NowBut(J_BUT_6) == 1)
				{
					if (!Find<Beam::Obj>(Beam::caTaskName))
					{
						auto bm = Add<BeamGenerator::Obj>();
						if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
						{
							res->wsTest4.Play();
						}
					}
				}
				if (kb->Now(VK_RIGHT) == 1)
				{
					if (!Find<Beam::Obj>(Beam::caTaskName))
					{
						auto bm = Add<BeamGenerator::Obj>();
					}
				}
				if (!Find<Beam::Obj>(Beam::caTaskName))
				{
					float fSpdY = pad->GetAxisL().GetY() * 0.2f;
					float fAng = 0.5f;
					if (kb->On('W'))
					{
						fSpdY = -5.f;
					}
					if (kb->On('S'))
					{
						fSpdY = 5.f;
					}
					if (kb->On(VK_LEFT))
					{
						fSpdY *= 0.5f;
						fAng *= 0.5f;
					}
					if (pad->On(J_BUT_5))
					{
						fSpdY *= 0.5f;
						fAng *= 0.5f;
					}
					const float fPosX = rBase.GetPosX();
					const float fPosY = rBase.GetPosY();
					float fAfterPosY = fPosY + fSpdY;
					constexpr float cfWinRecDist = 100.f;
					constexpr float cfPlayerPosMin = 0.f + cfWinRecDist;
					constexpr float cfPlayerPosMax = 1080.f - cfWinRecDist;
					if (fAfterPosY >= cfPlayerPosMax) fAfterPosY = cfPlayerPosMax;
					if (fAfterPosY <= cfPlayerPosMin) fAfterPosY = cfPlayerPosMin;
					pPos = Point(fPosX, fAfterPosY);
					rBase.SetPos(&pPos);
					if (kb->On(VK_UP))
					{
						fPAngle = Max(fPAngle - fAng, rBase.GetDeg(&pStandardPoint) + 145);
					}
					if (kb->On(VK_DOWN))
					{
						fPAngle = Min(fPAngle + fAng, rBase.GetDeg(&pStandardPoint) + 215);
					}
					fPAngle =
						Max
						(
							Min
							(
								fPAngle + pad->GetAxisR().GetY() * fAng,
								rBase.GetDeg(&pStandardPoint) + 215
							),
							rBase.GetDeg(&pStandardPoint) + 145
						);
					rBase.SetDeg(fPAngle);



					//float fSpd = 0.2f, fAng = 0.3f;
					//if (pad->On(J_BUT_5))
					//{
					//	fSpd = 0.1f;
					//	fAng = 0.1f;
					//}
					//fSPAngle = max(min(fSPAngle - pad->GetAxisL().GetY() * fSpd, 198.f), 162.f);
					//fPAngle =
					//	max
					//	(
					//		min
					//		(
					//			fPAngle + pad->GetAxisR().GetY() * fAng,
					//			rBase.GetDeg(&pStandardPoint) + 215
					//		),
					//		rBase.GetDeg(&pStandardPoint) + 145
					//	);
					//if (pad->NowBut(J_BUT_2) == 1 || kb->Now('6') == 1)
					//{
					//	fSPAngle = 180.f;
					//	fPAngle = 180.f/*rBase.GetDeg(&pStandardPoint) + 180.f*/;
					//}
					//if (kb->Now('W'))
					//{
					//	fSPAngle = min(fSPAngle + 0.2f, 198.f);
					//}
					//if (kb->Now('S'))
					//{
					//	fSPAngle = max(fSPAngle - 0.2f, 162.f);
					//}
					//if (kb->Now(VK_UP))
					//{
					//	fPAngle = max(fPAngle - 1.f, rBase.GetDeg(&pStandardPoint) + 145);
					//}
					//if (kb->Now(VK_DOWN))
					//{
					//	fPAngle = min(fPAngle + 1.f, rBase.GetDeg(&pStandardPoint) + 215);
					//}
					//if (kb->Now('Z') == 1)
					//{
					//	fSPAngle = 180.f;
					//	fPAngle = 180.f/*rBase.GetDeg(&pStandardPoint) + 180.f*/;
					//}
				}
			}
		}
		///**/rBase.SetPos(&Point(cos(DtoR(fSPAngle)) * fSPDist + pStandardPoint.x, sin(DtoR(fSPAngle)) * fSPDist + pStandardPoint.y));/**/
		//rBase.SetDeg(fPAngle);

		if (fSPAngle >= 189.f)
		{
			fSrcX = 6.f;
			rImgBase.SetPos(&rBase.GetPos());
			rImgBase.SetDeg(rBase.GetDeg() - 45.f);
		}
		else if (fSPAngle <= 171.f)
		{
			fSrcX = 8.f;
			rImgBase.SetPos(&rBase.GetPos());
			rImgBase.SetDeg(rBase.GetDeg() + 45.f);
		}
		else
		{
			fSrcX = 10.f;
			rImgBase.SetPos(&Point(cos(DtoR(rBase.GetDeg() + 90)) * 50.f + rBase.GetPosX(), sin(DtoR(rBase.GetDeg() + 90)) * 50.f + rBase.GetPosY()));
			rImgBase.SetDeg(rBase.GetDeg());
		}

		lGuideLine.SetLen(2000.f);
		lGuideLineFgm.SetLen(0.f);
		lGuideLine.SetPos(&rBase.GetPos());
		lGuideLine.SetDeg(rBase.GetDeg() + 180);

		auto vFgm = FindAll<Fragment::Obj>(Fragment::caTaskName);
		if (vFgm.size())
		{
			for (auto &vf : vFgm)
			{
				if (lGuideLine.CheckHit(&vf->cFragmentHitBase))
				{
					Point pIn = lGuideLine.GetPOI(&vf->cFragmentHitBase);
					lGuideLine.SetPos(&lGuideLine.GetSPos(), &pIn);

					if (!vf->bMoveActive)
					{
						lGuideLineFgm.SetPos(&vf->cFragmentHitBase.GetPos());
						lGuideLineFgm.SetDeg(vf->rFragment.GetDeg(&pIn) + 180);
						lGuideLineFgm.SetLen(2000.f);
					}
				}
			}
		}
	}

	/*タスクの描画処理*/
	void Obj::Render()
	{
		lGuideLine.Draw();
		if (lGuideLineFgm.GetLen())
		{
			lGuideLineFgm.Draw(PS_DASH);
		}
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * fSrcX, 16.f, 16.f, 16.f);
			rImgBase.Draw(&res->iStageImg, &src, true);
		}
	}
}
