#include "Title.h"
#include "StageManager.h"
#include "Cursor.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "FragmentGenerator.h"
#include "Fragment.h"
#include "MeteoGenerator.h"
#include "StarGenerator.h"
#include "Star.h"
#include "Gas.h"

namespace Title
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iHo.ImageCreate("./data/image/other/Title/ho.bmp");
		iHoOverride.ImageCreate("./data/image/other/Title/ho2.bmp");
		iBoshi.ImageCreate("./data/image/other/Title/boshi.bmp");
		iBoshiOverride.ImageCreate("./data/image/other/Title/boshi2.bmp");
		iStart.ImageCreate("./data/image/other/Title/word.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iHo.Release();
		iHoOverride.Release();
		iBoshi.Release();
		iBoshiOverride.Release();
		iStart.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName("タイトルタスク");
		/*リソース生成*/
		RB::Add<RS>("タイトルリソース");
		RB::Add<StageManager::RS>("ステージ統括リソース");
		/*タスクの生成*/

		Add<BeamGenerator::Obj>();
		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = rand() % 3;
		fg->Bridge(1, &Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.423f), &iColor);
		/*データの初期化*/
		rHo = Rec(730, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rBoshi = Rec(1190, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);

		fMScale = rand() % (16 * 4 + 1) + 16.f * 14.f;
		rMeteo = Rec(Rec::Win.r * 0.5f, -300.f, fMScale, fMScale);
		fMSpdBase = 20.f;
		vMSpd.SetVec(rMeteo.GetDeg(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.f)), fMSpdBase);
		rStart = Rec(0.f, 0.f, 0.f, 0.f);
		fZoom = 1.8f;
		fStartImgSrcY = 0.f;
		bAlpha = 5;
		cAddAlpha = 5;

		Rec::Zoom(fZoom);
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			res->wsBGM.PlayL();
			//res->wsBGM1.PlayL();
			//res->wsBGM1.Pause();
			//res->wsBGM2.PlayL();
			//res->wsBGM2.Pause();
		}
		//Add<MeteoGenerator::Obj>();
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		sg->Bridge(1, &iChange, &Point(1190.f, Rec::Win.b * 0.43f));
		if (auto st = Find<Star::Obj>("星タスク"))
		{
			st->rStar.Scaling(100 * 1.2f, 100 * 1.2f);
		}
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove("タイトルリソース");
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto pad = JoyPad::GetState(0);
		auto kb = KB::GetState();

		auto bm = Find<Beam::Obj>("ビームタスク");
		if (!bm) return;

		bShineFlag = false;
		if (bm->vSpd != Vector2::right * 20.f && bm->rHitBase.GetPosX() <= Rec::Win.l + 600.f)
		{
			bShineFlag = true;
			Pause("ビームタスク");
		}

		if (bShineFlag)
		{
			Rec::Zoom(fZoom);
			fZoom = Max(fZoom - 0.03f, 1.f);

			if (fZoom > 1.f) return;

			if (bAlpha <= 0 || bAlpha >= 255)
			{
				cAddAlpha = -cAddAlpha;
			}
			bAlpha += cAddAlpha;

			rMeteo.SetDeg(rMeteo.GetDeg() + 2.f);
			
			if (!fMSpdBase)
			{
				const fix fRandAngle = rand() % 360;
				rMeteo.SetPos(&Point(cos(DtoR(fRandAngle)) * 1000.f + Rec::Win.r * 0.5f, sin(DtoR(fRandAngle)) * 1000.f + Rec::Win.b * 0.5f));
				fMSpdBase = 20.f;
				vMSpd.SetVec(rMeteo.GetDeg(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f)), fMSpdBase);
				fMScale = rand() % (16 * 4 + 1) + 16.f * 18.f;
				rMeteo.Scaling(fMScale, fMScale);
			}
			vMSpd.SetVec(vMSpd.GetDeg(), fMSpdBase);
			rMeteo.Move(&vMSpd);
			rMeteo.Scaling(fMScale, fMScale);
			fMScale = Max(fMScale - 4.f, 0.f);
			fMSpdBase = Max(fMSpdBase - 0.15f, 0.f);

			if (Find<Cursor::Obj>("カーソルタスク")) return;

			auto cs = Add<Cursor::Obj>();
			cs->rCursorBase.SetPos(&Point(Rec::Win.r * 0.25f, Rec::Win.b * 0.75f));
			rStart = Rec(Rec::Win.r*0.5f, Rec::Win.b * 0.9f, 16 * 30, 16 * 5);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		//if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		//{
		//	Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b).Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		//}
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Frec src(16.f * 4, 16.f * 1, 16.f, 16.f);
			rMeteo.Draw(&res->iStageImg, &src, true);
		}
		if (auto s = RB::Find<Title::RS>("タイトルリソース"))
		{
			Frec src(0.f, 0.f, 64.f, 64.f);
			rHo.Draw(&s->iHo, &src);
			rHo.DrawAlpha(&s->iHoOverride, &src, bAlpha);

			rBoshi.Draw(&s->iBoshi, &src);
			rBoshi.DrawAlpha(&s->iBoshiOverride, &src, bAlpha);

			src = Frec(16.f * 0, 16.f * fStartImgSrcY, 16.f * 5, 16.f);
			rStart.Draw(&s->iStart, &src);
		}
	}
	/*アニメーション*/
	void AnimHo(byte * const bFrame, byte * const bAnim, byte * const bAnim2)
	{
		*bAnim2 = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			/**/
			*bAnim = (*bAnim + 1) % 4;
			/*/
			*bAnim = ((*bAnim - 1) + 4) % 4;
			/**/
		}
		++*bFrame;
	}
	/*アニメーション*/
	void AnimShiBoshi(byte * const bFrame, byte * const bAnim, byte * const bAnim2)
	{
		*bAnim2 = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			/**/
			*bAnim = (*bAnim + 1) % 4;
			/*/
			*bAnim = ((*bAnim - 1) + 4) % 4;
			/**/
		}
		++*bFrame;
	}
}
