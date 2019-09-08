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
		replayStage = "./data/demo/replay_stage.txt";
		replayFile = "./data/demo/replay.txt";
		__int64 temp = getFileSize(replayFile);
		if (temp < 1024) {
			std::string files[2] = { "./data/demo/replay_bac0.txt" ,"./data/demo/replay_bac1.txt" };
			std::string stages[2] = { "./data/demo/replay_stage_bac0.txt",  "./data/demo/replay_stage_bac1.txt" };
			//replayFile = "./data/demo/replay_bac.txt";
			//replayStage = "./data/demo/replay_stage_bac.txt";
			int random = rand() % 2;
			replayFile = files[random];
			replayStage += stages[random];
		}
		std::ifstream ifs(replayStage);
		//std::ifstream ifs("./data/demo/replay_stage.txt");
		if (!ifs)
		{
			Remove(this);
			return;
		}

		if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			int nb;
			ifs >> nb;
			sm->bStageNum = nb;

			/*入れ替え*/
			Swap(sm, this);
			///*強制的に入れ替え*/
			//auto smn = sm->next;
			//auto smp = sm->prev;
			//auto n = this->next;
			//auto p = this->prev;

			//if(p) p->next = sm;
			//else TB::top = sm;
			//if(n) n->prev = sm;
			//sm->next = n;
			//sm->prev = p;

			//if(smp) smp->next = this;
			//else TB::top = this;
			//if(smn) smn->prev = this;
			//this->next = smn;
			//this->prev = smp;
		}
		ifs.close();

		Add<StageLoad::Obj>();
		/*データの初期化*/
		bIsLoad = false;
		bFadeCompCnt = 0;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);
		if (kb->Down(VK_RETURN) || kb->Down(VK_RIGHT) || pad->Down(JOY_BUTTON6) || pad->Down(JOY_BUTTON2))
		{
			if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
			{
				res->wsBGM.Pause();
			}
			RemoveAll();
			Add<JecLogo::Obj>();
			return;
		}
		if (Find<StageLoad::Obj>(StageLoad::caTaskName)) return;
		if (!bIsLoad)
		{
			if (auto pl = Find<Player::Obj>(Player::caTaskName))
			{
				pl->ReplayLoad(replayFile);
				//pl->ReplayLoad("./data/demo/replay.txt");
				bIsLoad = true;
			}
		}
		else if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			if (sm->bClearFragmentNum >= sm->bClearFragmentNumMax)
			{
				if (auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
				{
					if (fade->IsComplete())
					{
						if (bFadeCompCnt > 0)
						{
							bFadeCompCnt = 0;
							if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
							{
								res->wsBGM.Pause();
							}
							RemoveAll();
							Add<JecLogo::Obj>();
						}
						++bFadeCompCnt;
					}
				}
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
	//ファイルの大きさをバイトで返す
	//__int64 は Long タイプ
	__int64 Obj::getFileSize(const std::string &asRepFileName) {
		struct _stati64 statbuf;
		if (_stati64(asRepFileName.c_str(), &statbuf)) return -1;
		return statbuf.st_size;
	}
}
