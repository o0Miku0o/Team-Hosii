#include "StageSelect.h"
#include "StageManager.h"
#include "StageSelectObjUS.h"
#include "StageSelectObjEarth.h"
#include "StageSelectObjGalaxy.h"
#include "StageSelectObjBH.h"
#include "StageSelectObjAsteroid.h"
#include "Cursor.h"
#include "Hukidasi.h"
#include "StageLoad.h"


namespace StageSelect
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
		Add<StageSelectObjGalaxy::Obj>();
		Add<StageSelectObjBH::Obj>();
		Add<StageSelectObjAsteroid::Obj>();
		auto es = Add<StageSelectObjEarth::Obj>();
		Add<StageSelectObjUS::Obj>();
		Add<Hukidasi::Obj>();
		auto cs = Add<Cursor::Obj>();
		//cs->pPos = es->rEarth.GetPos();
		cs->rCursorBase.SetPos(&es->rEarth.GetPos());

		/*データの初期化*/
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsBGM.Restart();
		}
		if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			sm->bStageNum = 11;

		}
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		//tamesi
		const auto kb = KB::GetState();
		if (kb->Down('O'))
		{
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			Add<StageLoad::Obj>();
			Pause(2);
			return;
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
