#include "Demo.h"
#include "JecLogo.h"
#include "StageManager.h"
#include "StageLoad.h"
#include "Player.h"
#include "FadeInOut.h"

#include <fstream>

namespace Demo
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
		RB::Add<RS>(caResName);
		/*タスクの生成*/

		RemoveAll({ Demo::caTaskName }, NOT_REMOVE_NAME);

		std::ifstream ifs("./data/demo/replay_stage.txt");
		if (!ifs) return;
		auto sm = Add<StageManager::Obj>();
		ifs >> sm->bStageNum;
		ifs.close();

		Add<StageLoad::Obj>();
		/*データの初期化*/
		bIsLoad = false;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (Find<StageLoad::Obj>(StageLoad::caTaskName)) return;
		if (!bIsLoad)
		{
			if (auto pl = Find<Player::Obj>(Player::caTaskName))
			{
				pl->ReplayLoad("./data/demo/replay.txt");
				bIsLoad = true;
			}
		}
		else if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			if (sm->bClearFragmentNum >= sm->bClearFragmentNumMax)
			{
				if (auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
				{
					if (!fade->bIsIn)
					{
						RemoveAll();
						Add<JecLogo::Obj>();
					}
				}
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
