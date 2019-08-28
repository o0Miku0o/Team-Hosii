#include "StageSelect.h"
#include "StageManager.h"
#include "StageSelectIcon.h"
#include "Cursor.h"
#include "Hukidasi.h"
#include "StageLoad.h"
#include "BeamGenerator.h"
#include "AlienGenerator.h"


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
		srand((unsigned int)time(NULL));
		/*タスクの生成*/
		auto earth = Add<StageSelectIcon::Obj>();
		earth->type = StageSelectIcon::Type::ET;
		earth->rIcon.SetPos(&Point(450.f, 450.f));

		auto icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::MT;
		icon->rIcon.SetPos(&Point(750.f, 250.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::GL;
		icon->rIcon.SetPos(&Point(950.f, 450.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::US;
		icon->rIcon.SetPos(&Point(1150.f, 250.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::BH;
		icon->rIcon.SetPos(&Point(1450.f, 450.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::FR;
		icon->rIcon.SetPos(&Point(750.f, 650.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::TA;
		icon->rIcon.SetPos(&Point(1150.f, 650.f));

		Add<Hukidasi::Obj>();
		auto cs = Add<Cursor::Obj>();
		cs->rCursorBase.SetPos(&earth->rIcon.GetPos());


		/*データの初期化*/
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsBGM.Restart();
		}
		if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			sm->bStageNum = 11;
		}
		rHoudai = Rec(Rec::Win.r*0.5f, Rec::Win.b, 100.f, 100.f);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{

		this->iCnt++;
		int ranX = rand() % int(Rec::Win.r - 100) + 50;
		int ranY = rand() % int(Rec::Win.b*0.3f) + int(Rec::Win.b*0.7f);
		Point pos = Point(float(ranX), float(ranY));
		//エイリアン生成
		auto al = FindAll<Alien::Obj>(Alien::caTaskName);
		if (al.size() < 20 && iCnt > 120)
		{
			auto ag = Add<AlienGenerator::Obj>();
			constexpr int ceiNum = 1;
			Point pPos[ceiNum] =
			{
				pos,
			};
			Alien::Move fpMove[ceiNum] =
			{
				Alien::MoveStay,
			};
			Alien::Hit fpBMHit[ceiNum] =
			{
				Alien::BMRemove,
			};
			Alien::Hit fpFGHit[ceiNum] =
			{
				Alien::FGRemove,
			};
			Alien::Anim fpAnim[7] =
			{
				Alien::AnimNormal,
				Alien::AnimHorizontal,
				Alien::AnimRotation,
				Alien::AnimReflectDR,
				Alien::AnimReflectUR,
				Alien::AnimReflectDL,
				Alien::AnimReflectUL,
			};
			ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, (fpAnim+rand()%7));
			iCnt = 0;
		}
		//tamesi
		const auto kb = KB::GetState();
		auto pad = JoyPad::GetState(0);
		auto cs = Find<Cursor::Obj>(Cursor::caTaskName);
		float fAng = cs->rCursorBase.GetDeg(&Point(Rec::Win.r*0.5f, Rec::Win.b));
		rHoudai.SetDeg(fAng - 90);
		if (kb->Down('O'))
		{
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			Add<StageLoad::Obj>();
			Pause(2);
			return;
		}
		if (kb->Down('Z') || pad->Down(JOY_BUTTON6))
		{
			auto bmg = Add<BeamGenerator::Obj>();
			bmg->SelectBeamCreate(fAng);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		auto res = RB::Find<StageManager::RS>(StageManager::caResName);
		Frec src(0, 16.f, 16.f, 16.f);
		rHoudai.Draw(&res->iStageImg, &src, true);
	}
}
