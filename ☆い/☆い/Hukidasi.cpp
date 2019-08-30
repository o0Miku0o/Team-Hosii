#include "Hukidasi.h"
#include "StageManager.h"
#include "StagePicture.h"
#include "StarGenerator.h"

namespace Hukidasi
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iTextImg.ImageCreate("./data/image/other/stagelogo.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iTextImg.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);
		/*リソース生成*/
		RB::Add<RS>(caResName);
		/*タスクの生成*/

		/*データの初期化*/
		/*テキストの幅に合わせて調整*/
		faWidth[0] = 16.f * 4;
		faWidth[1] = 16.f * 6;
		faWidth[2] = 16.f * 8;
		faWidth[3] = 16.f * 6;
		faWidth[4] = 16.f * 7;

		rTextBox.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * (0.75f * 0.75f) + 70.f));
		fAddScale = 0.f;
		fWidthMax = 1800.f;
		fHeightMax = 400.f;
		//constexpr float fScaleWMax = 1800.f;
		//constexpr float fScaleHMax = 400.f;
		bSetPictureCount = 0;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		/*サイズ変更*/
		Resize();
		auto sp = Find<StagePicture::Obj>(StagePicture::caTaskName);
		if (rHukidasi.GetW() >= fWidthMax && rHukidasi.GetH() >= fHeightMax)
		{
			if (!sp)
			{
				/*画面の半分の位置、四分の一の位置*/
				const float fHalfWidth = Rec::Win.r * 0.5f;
				const float fHalfHeight = Rec::Win.b * 0.5f;
				const float fQuarterWidth = fHalfWidth * 0.5f;
				const float fQuarterHeight = fHalfHeight * 0.5f;
				constexpr float cfDist = -40.f;
				const Point pPosArr[3] =
				{
					Point(fQuarterWidth, fHalfHeight + fQuarterHeight - cfDist),
					Point(fHalfWidth, fHalfHeight + fQuarterHeight - cfDist),
					Point(fHalfWidth + fQuarterWidth, fHalfHeight + fQuarterHeight - cfDist)
				};
				constexpr float cfPicWidth = 1920.f * (0.125f * 1.5f);
				constexpr float cfPicHeight = 1080.f * (0.125f * 1.5f);

				for (byte b = 0; b < 3; ++b)
				{
					SetStagePicture(sGroup * 3 + b + 1, &Frec(pPosArr[b].x, pPosArr[b].y, cfPicWidth, cfPicHeight));
				}
			}
		}
		else
		{
			if (sp)
			{
				RemoveAll(StagePicture::caTaskName);
				//Remove(sp);
			}
			bSetPictureCount = 0;
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		/*サイズが0でないなら*/
		if (!rHukidasi.SizeZero())
		{
			if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
			{
				Frec src(16.f * 59, 16.f * 0, 16.f, 16.f);
				rHukidasi.Draw(&res->iStageImg, &src);
			}
		}
		if (!rHukidasi.GetH()) rHukidasi.Draw();
		if (rHukidasi.GetH() >= fHeightMax)
		{
			if (auto res = RB::Find<Hukidasi::RS>(caResName))
			{
				Frec src(0.f, 16.f * sGroup, faWidth[sGroup], 16.f);
				rTextBox.Scaling(faWidth[sGroup] * 6.f, 16.f * 6.f);
				rTextBox.Draw(&res->iTextImg, &src);
			}
		}
	}
	/*吹き出しのサイズ変更*/
	void Obj::Resize()
	{
		/*現在のサイズ*/
		const float fScaleW = rHukidasi.GetW();
		const float fScaleH = rHukidasi.GetH();
		/*各増加量*/
		const float fAddW = (fAddScale < 0.f && fScaleH > 0.f) ? 0.f : fAddScale;
		const float fAddH = (fAddScale > 0.f && fScaleW < fWidthMax) ? 0.f : fAddScale;
		/*サイズと増加量からサイズ変更*/
		const float fResizeW = Min(Max(fScaleW + fAddW, 0.f), fWidthMax);
		const float fResizeH = Min(Max(fScaleH + fAddH, 0.f), fHeightMax);
		rHukidasi.Scaling(fResizeW, fResizeH);
	}
	/*サイズの変化量を設定*/
	void Obj::SetAddScale(const float afAddScale)
	{
		fAddScale = afAddScale;
	}
	/*サイズの最大値を設定*/
	void Obj::SetScaleMax(const float afWMax, const float afHMax)
	{
		fWidthMax = afWMax;
		fHeightMax = afHMax;
	}
	/*座標を設定*/
	void Obj::SetPos(const Point * const appPos)
	{
		rHukidasi.SetPos(appPos);
	}
	/*表示するステージの設定*/
	void Obj::SetStagePicture(const unsigned int auiStageNumber, const Frec * const apfrPosSize)
	{
		if (bSetPictureCount > 2) return;
		auto sp = Add<StagePicture::Obj>();
		sp->LoadImg(auiStageNumber);
		sp->SetPos(&Point(apfrPosSize->l, apfrPosSize->t));
		sp->SetSize(apfrPosSize->r, apfrPosSize->b);
		++bSetPictureCount;
	}
	/*ステージのグループの設定*/
	void Obj::SetStageGroup(const StageSelectIcon::Type asStageGroup)
	{
		sGroup = asStageGroup;
	}
}
