#include "Tips.h"
#include "StagePicture.h"	
#include "StageManager.h"

//Tipsタスク
//スクショを加工したbmp画像を貼る
namespace Tips
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		//iTips.ImageCreate("./data/image/other/Tips/.bmp");
		iGuideBase.ImageCreate("./data/image/other/GuideBook.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iGuideBase.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);

		/*リソース生成*/
		RB::Add<Tips::RS>(caResName);

		/*タスクの生成*/

		/*データの初期化*/

		rBack = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b);
		rGuideBase = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, 16.f * 75.f, 16.f * 55.f);
		rTips = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.57f, 16.f * 62.5f, 16.f * 37.5f);
		LoadImg(1);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			rBack.Draw(&res->iStageImg, &Frec(16.f, 0.f, 16.f, 16.f));
		}
		if (auto res = RB::Find<Tips::RS>(caResName))
		{
			rGuideBase.Draw(&res->iGuideBase, &Frec(0.f, 0.f, 64.f, 80.f));
		}
		if (bIsLoaded)
		{
			rTips.Draw(&iTips, false);
		}
	}
	void Obj::LoadImg(const unsigned int auiStageNumber)
	{
		if (bIsLoaded) return;
		std::string sImgName = "./data/image/other/Tips/Tips(";
		sImgName += std::to_string(auiStageNumber);
		sImgName += ").bmp";
		iTips.ImageCreate(sImgName.c_str());
		bIsLoaded = true;

	}
}
