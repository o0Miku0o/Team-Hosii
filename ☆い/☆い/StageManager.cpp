#include "StageSelect.h"
#include "StageManager.h"
#include "Result.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "Player.h"
#include "FadeInOut.h"
#include "Back.h"
#include "StageLoad.h"
#include "Stage.h"

namespace StageManager
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iStageImg.ImageCreate("./data/image/main/resource.bmp");

		tese.ImageCreate("./data/image/other/fade.bmp");

		wsTest.SoundCreate("./data/sound/爆発音.wav");

		wsTest2.SoundCreate("./data/sound/はまる音.wav");

		wsTest3.SoundCreate("./data/sound/割れる音2.wav");

		wsTest4.SoundCreate("./data/sound/ビーム発射音2.wav");

		wsTest5.SoundCreate("./data/sound/欠片同士があたる2.wav");

		wsTest6.SoundCreate("./data/sound/ひびが入る.wav");

		wsTest7.SoundCreate("./data/sound/弾む音2.wav");

		wsTest8.SoundCreate("./data/sound/ステージ移動.wav");

		wsTest9.SoundCreate("./data/sound/メニュー表示1.wav");

		wsTest10.SoundCreate("./data/sound/吸い込む音.wav");

		wsTest11.SoundCreate("./data/sound/決定音 1.wav");

		wsTest12.SoundCreate("./data/sound/宇宙人出現.wav");

		wsTest13.SoundCreate("./data/sound/リザルト.wav");

		wsBGM.CallBack(WINNAME);
		wsBGM.SoundCreate("./data/sound/BGM2.wav");

		wsBGM1.CallBack(WINNAME);
		wsBGM1.SoundCreate("./data/sound/BGM4.wav");

		wsBGM2.CallBack(WINNAME);
		wsBGM2.SoundCreate("./data/sound/BGM3.wav");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iStageImg.Release();

		wsTest.Release();

		wsTest2.Release();

		wsTest3.Release();

		wsTest4.Release();

		wsTest5.Release();

		wsTest6.Release();

		wsTest7.Release();

		wsTest8.Release();

		wsTest9.Release();

		wsTest10.Release();

		wsTest11.Release();

		wsTest12.Release();

		wsTest13.Release();

		wsBGM.Release();

		wsBGM1.Release();

		wsBGM2.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName("ステージ統括タスク");
		/*リソース生成*/
		RB::Add<RS>("ステージ統括リソース");
		/*タスクの生成*/

		/*データの初期化*/
		bClearFragmentNum = 0;
		bClearFragmentNumMax = 255;
		usBeamCount = 0;
		bStageNum = 11;
		bIsDebug = false;
		iResultCnt = 0;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		//RB::Remove("ステージ統括リソース");
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (bClearFragmentNum >= bClearFragmentNumMax)
		{
			//時間を止めて！！！
			//フェイドイン＆＆フェイドアウトの時間に入れ替え
			auto fade = Find<FadeInOut::Obj>("フェイドインアウトタスク");
			++iResultCnt;
			if (iResultCnt == 1) {
				if (fade)
				{
					//fade->bActive = false;
					fade->Start();
					fade->bIsIn = true;
				}
				else
				{
					fade = Add<FadeInOut::Obj>();
					fade->bIsIn = true;
				}
			}
			else if (fade)//Find<FadeInOut::Obj>("フェイドインアウトタスク") == nullptr)
			{
				if (fade->IsComplete())
				{
					bClearFragmentNum = 0;

					RemoveAll({ "ステージ統括タスク", "フェイドインアウトタスク" }, NOT_REMOVE_NAME);
					//RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);

					//			Add<Back::Obj>();
					if (auto manager = Find<StageManager::Obj>("ステージ統括タスク")) {
						manager->bStageNum = manager->bNextStage;
						if (manager->bStageNum == 255) {
							RemoveAll();
							Add<StageManager::Obj>();
							Add<Back::Obj>();
							Add<StageSelect::Obj>();
							Pause(2);
						}
						else {
							Add<StageLoad::Obj>();
							//Pause(2);
						}
					}


					//RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
					//auto re = Add<Result::Obj>();
					//re->bNextStage = bNextStage;
					//if (usBeamCount <= bClearFragmentNumMax)
					//{
					//	re->bScore = 3;
					//}
					//else if (usBeamCount <= u_short(bClearFragmentNumMax * 2))
					//{
					//	re->bScore = 2;
					//}
					iResultCnt = 0;
				}
			}
		}

		//BGMの振り分け
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			if (Find<Stage::Obj>("ステージタスク") != nullptr) {
				if (bStageNum >= 30 && bStageNum < 40) {
					if (res->wsBGM2.IsPlaying()) {
						res->wsBGM2.Restart();
					}
					else {
						if (res->wsBGM.IsPlaying())
							res->wsBGM.Stop();
						res->wsBGM2.PlayL();
					}
				}
				else {
					if (res->wsBGM.IsPlaying()) {
						res->wsBGM.Restart();
					}
					else {
						if (res->wsBGM2.IsPlaying()) {
							res->wsBGM2.Stop();
						}
						res->wsBGM.PlayL();
					}
				}
			}
			if (Find<StageSelect::Obj>("ステージ選択タスク") != nullptr) {
				if (res->wsBGM.IsPlaying()) {
					res->wsBGM.Restart();
				}
				else {
					if (res->wsBGM2.IsPlaying()) {
						res->wsBGM2.Stop();
					}
					res->wsBGM.PlayL();
				}
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		//if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		//{
		//	Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b).Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		//}
	}
}