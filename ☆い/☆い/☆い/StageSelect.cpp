#include "StageSelect.h"
#include "StageManager.h"
#include "StageSelectObjUS.h"
#include "StageSelectObjEarth.h"
#include "StageSelectObjGalaxy.h"
#include "StageSelectObjBH.h"
#include "StageSelectObjAsteroid.h"
#include "Cursor.h"


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
		SetName("ステージ選択タスク");
		/*リソース生成*/
	
		/*タスクの生成*/
		Add<StageSelectObjGalaxy::Obj>();
		Add<StageSelectObjBH::Obj>();
		Add<StageSelectObjAsteroid::Obj>();
		Add<StageSelectObjEarth::Obj>();
		Add<StageSelectObjUS::Obj>();
		auto cs = Add<Cursor::Obj>();
		cs->rCursorBase.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f));

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
