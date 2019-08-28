#include "Result.h"
#include "StageManager.h"
#include "StageSelect.h"
#include "Star.h"
#include "BreakStar.h"
#include "StarGenerator.h"
#include "Back.h"
#include "StagePicture.h"
#include "StageLoad.h"
#include "StagePicture.h"
#include "Cursor.h"

namespace Result
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iResult.ImageCreate("./data/image/other/ResultResource.bmp");
		iHanko.ImageCreate("./data/image/other/ResultResource2.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{

	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);// "リザルトタスク");

		/*リソース生成*/
		RB::Add<Result::RS>(caResName);// "リザルトリソース");

		/*タスクの生成*/
		auto cs = Add<Cursor::Obj>();
		cs->rCursorBase.SetPos(&Point(1450.f, 1020.f));

		/*データの初期化*/
		ButtonInit();
		rBack = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b);
		rResult = Rec(Rec::Win.r * 0.5f, 700.f, 16.f * 95.f, 16.f * 100.f);
		//rNumber = Rec(1050.f, 800.f, 16.f * 16.f, 16.f * 17.f);

		auto sg = Add<StarGenerator::Obj>();

		//赤い枠線
		//ここにスクショ貼りつける
		for (int i = 0; i < 3; ++i)
		{
			auto sp = Add<StagePicture::Obj>();
			sp->LoadImg(1 * i + 1);
			sp->SetSize(410.0f, 250.0f);
			sp->SetPos(&Point(float(490 + i * 470), 250.f));
		}

		//星の座標
		vector<Frec> pStArr =
		{
			Frec(340.f,430.f , 70.f,70.f),
			Frec(490.f,430.f, 70.f,70.f),
			Frec(640.f,430.f, 70.f,70.f),
			Frec(810.f,430.f, 70.f,70.f),
			Frec(960.f,430.f, 70.f,70.f),
			Frec(1110.f,430.f, 70.f,70.f),
			Frec(1280.f,430.f, 70.f,70.f),
			Frec(1430.f,430.f, 70.f,70.f),
			Frec(1580.f,430.f, 70.f,70.f),
			Frec(340.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(490.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(640.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(810.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(960.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(1100.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(1360.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(1560.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(1760.f - 1000.f,430.f - 1000.f, 70.f,70.f)
		};

		//星の形(リソースの番号)
		vector<int> iArr = { 37, 37, 37, 37, 37, 37, 37, 37, 37, 25, 25, 25, 25, 25, 25, 25, 25, 25 };
		//星のエフェクト(リソースの番号)
		vector<int> iEff = { 55, 55, 55, 55, 55, 55, 55, 55, 55, 47, 47, 47, 47, 47, 47, 47, 47, 47 };

		sg->Bridge(18, iArr, iEff, pStArr);
		bNextStage = 0;
		bMoveStarIdx = 0;
		bScore = 1;

		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsBGM.Pause();
			res->wsBGM2.Pause();
			res->wsBGM1.Pause();
		}
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto pad = JoyPad::GetState(0);
		auto kb = KB::GetState();

		std::vector<TB_ptr> vsMoveStar;
		for (auto &vs : FindAll<Star::Obj>(Star::caTaskName))
		{
			if (vs->starColor == Star::Obj::StarColor::Yellow5)
			{
				vsMoveStar.emplace_back(vs);
			}
		}
		if (bMoveStarIdx < bScore)
		{
			auto st = (Star::Obj_ptr)vsMoveStar[bMoveStarIdx];
			st->rStar.Move(&Vector2(20.f, 20.f));
			if (st->rStar.GetPosY() >= 430.f)
			{
				++bMoveStarIdx;
				if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
				{
					res->wsTest2.Play();
				}
			}
		}
		else if (pad->Down(JOY_BUTTON6) || kb->Down('8') || kb->Down(VK_RETURN))
		{
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			if (auto manager = Find<StageManager::Obj>(StageManager::caTaskName))
			{
				manager->bStageNum = manager->bNextStage;
				if (manager->bStageNum == 255)
				{
					RemoveAll();
					Add<StageManager::Obj>();
					Add<Back::Obj>();
					Add<StageSelect::Obj>();
					Pause(2);
				}
				/*else
				{
					Add<Back::Obj>();
					Add<StageSelect::Obj>();
					Pause(2);
				}*/
			}
			Pause(2);
		}

		ButtonResize();
	}

	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (bScore == 3)
		{
			Rec::FullPaint(RGB(0, 255, 204));
		}
		else if (bScore == 2)
		{
			Rec::FullPaint(RGB(255, 174, 0));
		}
		else
		{
			Rec::FullPaint(RGB(144, 151, 160));
		}
		if (auto s = RB::Find<Result::RS>(Result::caResName))
		{
			rResult.Draw(&s->iResult, &Frec(0.f, 0.f, 16.f, 16.f), true);
			rRestart.Draw(&s->iHanko, &Frec(0.f, 0.f, 16.f, 16.f), true);
			//rNumber.Draw(&s->iResult, &Frec(16.f, 0.f, 16.f, 16.f), true);
		}
	}

	void Obj::ButtonInit()
	{
		rRestart = Rec(0.f, 0.f, 0.f, 0.f);
	}
	void Obj::ButtonResize()
	{
		rRestart = Rec(1630.f, 1020.f, 16.f * 8.f, 16.f * 8.f);
	}
}
