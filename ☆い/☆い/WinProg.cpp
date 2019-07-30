#include "MyGame/MyApp.h"
#include "Title.h"
#include "GameInit.h"

#include "Result.h"
#include "StageManager.h"

#include "JecLogo.h"

//グローバル領域ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//

//初期化処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//
void Init()
{
	/*ここで最初のタスクを追加*/
	/**TB::Add<StageManager::Obj>();
	TB::Add<Result::Obj>()->SetParam(1, std::array<byte, 3>({ 3, 3, 3 }));/*/
	TB::Add<JecLogo::Obj>();/*TB::Add<GameInit::Obj>();*//**/
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
