#include "MiniGame.h"
#include "Fragment.h"
#include "Star.h"
#include "Back.h"

//ミニゲームで使うタスクです
//カウントやらなんやらをします
namespace MiniGame
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
		Add<Back::Obj>();

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
