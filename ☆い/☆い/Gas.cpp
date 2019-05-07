#include "Gas.h"
#include "Title.h"
#include "StageManager.h"

//素材は4(種類)×2(アニメーションあり)
//位置は多分87から94
//ランダムで出すようにしたい
//タイトル＆ステージで使えるようにしたい
//三枝先生からのお言葉「最後の方でいいかな」
namespace Gas
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
		SetName("ガスタスク");
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/

		iGasColor = 0;

		aAnim.SetAnim(AnimGasW, 0);
		aAnim.SetAnim(AnimGasB, 0);
		aAnim.SetAnim(AnimGasY, 0);
		aAnim.SetAnim(AnimGasP, 0);
		aAnim.Play();
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			if (iGasColor == 'W')
			{
				Frec src(16.f * (aAnim.GetSrcX() + 87), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iGasColor == 'B')
			{

				Frec src(16.f * (aAnim.GetSrcX() + 89), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iGasColor == 'Y')
			{

				Frec src(16.f * (aAnim.GetSrcX() + 91), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iGasColor == 'P')
			{

				Frec src(16.f * (aAnim.GetSrcX() + 93), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
		}

	}
	void AnimGasW(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasP(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 2) % 8;
		}
		++*bFrame;
	}
}
