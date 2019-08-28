#include "StagePicture.h"

namespace StagePicture
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
		SetRenderPriority(0.5f);
		/*まだ画像は読み込まれていません。*/
		bIsLoaded = false;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		if (!bIsLoaded) return;
		iStageImg.Release();
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (bIsLoaded)
		{
			rPictureBase.Draw(&iStageImg, false);
		}
#ifdef _DEBUG
		rPictureBase.SetColor(RGB(255, 0, 0));
		rPictureBase.Draw();
#endif
	}
	void Obj::LoadImg(const unsigned int auiStageNumber)
	{
		if (bIsLoaded) return;
		std::string sImgName = "./data/image/other/Stage/st";
		sImgName += std::to_string(auiStageNumber);
		sImgName += ".bmp";
		iStageImg.ImageCreate(sImgName.c_str());
		bIsLoaded = true;

	}
	void Obj::SetSize(const float afWidth, const float afHeight)
	{
		rPictureBase.Scaling(afWidth, afHeight);
	}
	void Obj::SetPos(const Point * const appPos)
	{
		rPictureBase.SetPos(appPos);
	}
}
