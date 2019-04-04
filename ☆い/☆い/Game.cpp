#include "Game.h"
#include "Title.h"

namespace Game
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
		SetName("統括タスク");
		/*リソース生成*/
		RB::Add<RS>("統括リソース");
		/*タスクの生成*/

		/*データの初期化*/

	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove("統括リソース");
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		/*if (kb->Now('T') == 1)
		{
			RemoveAll();
			Add<Title::Obj>();
		}*/
		const auto pad = JoyPad::GetState(0);
		if (pad->NowBut(J_BUT_1))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_2))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_3))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_4))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_5))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (res = RB::Find<RS>("統括リソース"))
		{

		}
	}
}
