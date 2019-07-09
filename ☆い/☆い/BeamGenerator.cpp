#include "BeamGenerator.h"
#include "Beam.h"
#include "Player.h"
#include "Title.h"
#include "StageManager.h"
#include "BreakStar.h"

namespace BeamGenerator
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
		bBeamCount = 0;

		if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			++sm->usBeamCount;
		}
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (auto player = Find<Player::Obj>(Player::caTaskName))
		{
			/*プレイヤーに合わせてビームを生成*/
			BeamCreate(player);
		}
		/*タイトル画面だけ特殊に*/
		else if (Find<Title::Obj>(Title::caTaskName))
		{
			TitleBeamCreate();
		}
		++bBeamCount;
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
	/*ビームを生成*/
	void Obj::BeamCreate(TaskBase *atpPlayer)
	{
		auto player = (Player::Obj_ptr)atpPlayer;
		if (bBeamCount > 5)
		{
			Remove(this);
			return;
		}
		auto beam = Add<Beam::Obj>();
		Point pPos
		(
			cos(DtoR(player->rBase.GetDeg() - 180)) * player->rBase.GetW() * 0.5f + player->rBase.GetPosX(),
			sin(DtoR(player->rBase.GetDeg() - 180)) * player->rBase.GetW() * 0.5f + player->rBase.GetPosY()
		);
		beam->rHitBase.SetPos(&pPos);
		beam->rHitBase.SetDeg(player->rBase.GetDeg() + 180);
	}
	/*タイトルだけ特殊に*/
	void Obj::TitleBeamCreate()
	{
		if (bBeamCount > 13)
		{
			Remove(this);
			return;
		}
		auto beam = Add<Beam::Obj>();
		beam->rHitBase.SetPos(&Point(Rec::Win.l, Rec::Win.b * 0.423f));
		beam->rHitBase.Scaling(21.f, 16.f * 2.f);
		beam->rHitBase.SetDeg(0.f);
	}
}
