#include "GameInit.h"
#include "StageManager.h"
#include "Back.h"
#include "Title.h"
#include "MeteoGenerator.h"

namespace GameInit
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
		Add<StageManager::Obj>();
		Add<Back::Obj>();
		Add<Title::Obj>();
		Remove(this);
		/*データの初期化*/

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

	}
}
