#include "Title.h"
#include "StageManager.h"
#include "Cursor.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "FragmentGenerator.h"
#include "Fragment.h"

namespace Title
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iHo.ImageCreate("./data/image/other/Title/ho.bmp");
		iShi.ImageCreate("./data/image/other/Title/shi.bmp");
		iBoshi.ImageCreate("./data/image/other/Title/boshi.bmp");
		iStart.ImageCreate("./data/image/other/Title/word.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
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
		int iColor = 0;
		fg->Bridge(1, &Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.428f), &iColor);
		/*データの初期化*/
		rHo = Rec(630, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rShi = Rec(Rec::Win.r*0.5f, Rec::Win.b * 0.6f, 16 * 18, 16 * 18);
		rBoshi = Rec(1290, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rStart = Rec(0.f, 0.f, 0.f, 0.f);
		fZoom = 1.8f;

		aAnimator1.SetAnim(AnimHo, 0);
		aAnimator2.SetAnim(AnimShiBoshi, 0);

		Rec::Zoom(fZoom);
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			res->wsBGM.PlayL();
			res->wsBGM1.PlayL();
			res->wsBGM1.Pause();
			res->wsBGM2.PlayL();
			res->wsBGM2.Pause();
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
		auto fgm = Find<Fragment::Obj>("欠片タスク");
		if (!bm || !fgm) return;

		fgm->rFragment.Scaling(100.f * 1.7f, 100.f * 1.7f);

		byte bFlag = 0;
		if (fgm->bMoveActive)
		{
			if (fgm->rFragment.GetPosX() >= Rec::Win.r - 640.f)
			{
				++bFlag;
				fgm->rFragment.SetPos(&Point(Rec::Win.r - 640.f, fgm->rFragment.GetPosY()));
				Pause("欠片タスク");
			}
			if (bm->rHitBase.GetPosX() <= Rec::Win.l + 500.f)
			{
				++bFlag;
				Pause("ビームタスク");
			}
		}

		if (bFlag == 2)
		{
			Rec::Zoom(fZoom);
			fZoom = Max(fZoom - 0.02f, 1.f);

			aAnimator1.Update();
			aAnimator2.Update();

			//if (fZoom > 1.f) return;
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
		if (auto s = RB::Find<Title::RS>("タイトルリソース"))
		{
			Frec src(160.f * aAnimator1.GetSrcX(), 0, 16 * 10, 16 * 10);
			rHo.Draw(&s->iHo, &src, true);

			src = Frec(160.f * aAnimator2.GetSrcX(), 0, 16 * 10, 16 * 10);
			rShi.Draw(&s->iShi, &src, true);

			rBoshi.Draw(&s->iBoshi, &src, true);

			src = Frec(16 * 0, 16 * 0, 16 * 5, 16);
			rStart.Draw(&s->iStart, &src, true);
		}
	}
	/*アニメーション*/
	void AnimHo(byte * const bFrame, byte * const bAnim, byte * const bAnim2)
	{
		*bAnim2 = 0;
		if (*bFrame == 15)
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
		if (*bFrame == 20)
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
