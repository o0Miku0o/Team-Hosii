#include "JecLogo.h"
#include "GameInit.h"

namespace JecLogo
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iLogoImg.ImageCreate("./data/image/other/日本電子ロゴ.bmp");
		iBlackImg.ImageCreate("./data/image/other/Black.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iLogoImg.Release();
		iBlackImg.Release();
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
		rLogoBase.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f));
		rLogoBase.Scaling(Rec::Win.r, Rec::Win.b);
		fAlpha = 255;
		iWaitCnt = 80;
		bRev = false;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (!bRev)
		{
			if (fAlpha > 0)
			{
				fAlpha -= 12.75f;//25.5;
			}
			else if (iWaitCnt > 0)
			{
				--iWaitCnt;
			}
			else bRev = true;
		}
		else
		{
			if (fAlpha < 255)
			{
				fAlpha += 12.75f;//25.5;
			}
			else
			{
				Remove(this);
				Add<GameInit::Obj>();
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<RS>(caResName))
		{
			rLogoBase.Draw(&res->iLogoImg);
			rLogoBase.DrawAlpha(&res->iBlackImg, (byte)fAlpha);
		}
	}
}
