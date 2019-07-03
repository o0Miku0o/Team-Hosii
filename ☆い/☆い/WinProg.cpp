#include "MyGame/MyApp.h"
#include "Title.h"
#include "GameInit.h"

//グローバル領域ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//

//初期化処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//
void Init()
{
	/*ここで最初のタスクを追加*/
	TB::Add<GameInit::Obj>();
	//TB::SysInit<GameInit::Obj>();
}

//終了処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//
void Finalize()
{
	TB::SysFinalize();
}

//更新処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//
bool Update()
{
	return TB::SysUpdate();
}

//描画処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//
void Render()
{
	TB::SysRender();
}
