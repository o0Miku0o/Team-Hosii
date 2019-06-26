#include "StageSelect.h"
#include "StageManager.h"
#include "Stage.h"
#include "StageLoad.h"
#include "Back.h"

namespace Stage
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
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsBGM.Restart();
		}
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);
		if (kb->Down('G') || pad->Down(JOY_BUTTON8))
		{
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
			{
				res->wsBGM.Pause();
			}
			Add<StageLoad::Obj>();
			Pause(2);
		}

		if (kb->Down('F') || pad->Down(JOY_BUTTON7)) {
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
			{
				res->wsBGM.Pause();
			}
			Add<Back::Obj>();
			Add<StageSelect::Obj>();	
			Pause(2);
		}
		if (kb->Down('R') || pad->Down(JOY_BUTTON4)) {
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			Add<StageLoad::Obj>();
			Pause(2);
		}

		if (kb->Down('T') || pad->Down(JOY_BUTTON3)) {
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			if (auto manager = Find<StageManager::Obj>(StageManager::caTaskName)) {
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
					Pause(2);
				}
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
#ifdef _DEBUG
		Font f;
		std::string s = "現在ステージ";
		if (auto manager = Find<StageManager::Obj>(StageManager::caTaskName)) {
			s += to_string(manager->bStageNum);
		}
		f.Draw(&Point(960, 10), s.c_str());
#endif // _DEBUG
	}
}
