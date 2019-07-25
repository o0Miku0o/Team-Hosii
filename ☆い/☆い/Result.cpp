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
		iPaper.ImageCreate("./data/image/other/re.bmp");
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
		//auto cs = Add<Cursor::Obj>();
		//cs->rCursorBase.SetPos(&Point(1450.f, 1020.f));

		/*データの初期化*/
		ButtonInit();
		rBack = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b);
		rResult = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f/*700.f*/, 16.f * 95.f, Rec::Win.b/*16.f * 100.f*/);
		//rNumber = Rec(1050.f, 800.f, 16.f * 16.f, 16.f * 17.f);

		auto sg = Add<StarGenerator::Obj>();

		//赤い枠線
		//ここにスクショ貼りつける

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
			Frec(1110.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(1280.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(1430.f - 1000.f,430.f - 1000.f, 70.f,70.f),
			Frec(1580.f - 1000.f,430.f - 1000.f, 70.f,70.f)
		};

		//星の形(リソースの番号)
		vector<int> iArr = { 37, 37, 37, 37, 37, 37, 37, 37, 37, 25, 25, 25, 25, 25, 25, 25, 25, 25 };
		//星のエフェクト(リソースの番号)
		vector<int> iEff = { 55, 55, 55, 55, 55, 55, 55, 55, 55, 47, 47, 47, 47, 47, 47, 47, 47, 47 };

		sg->Bridge(18, iArr, iEff, pStArr);
		bNextStage = 0;
		bMoveStarIdx = 0;
		//bScore = 9;//1;
		iRandomTime = 60;
		iHanabiCount = 0;
		iHanabiTime = 0;
		bScore.at(0) = 3;
		bScore.at(1) = 3;
		bScore.at(2) = 3;
		bScoreIdx = 0;
		rPercent.SetPos(&Point(1190.f, 780.f));
		rPercent.Scaling(120.f, 120.f);
		rHanko.SetPos(&Point(0.f, 0.f));
		rHanko.Scaling(0.f, 0.f);
		bPushHanko = false;
		sp_ef = std::shared_ptr<Eff1::EffectCreater>(new Eff1::EffectCreater("./data/effect/ef_result_hanabi.txt"));

		//em.Color(RGB(0, 255, 255));

		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
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
		for (auto &vs : FindAll<Star::Obj>("星タスク"))
		{
			if (vs->starColor == Star::Obj::StarColor::Yellow5)
			{
				vsMoveStar.emplace_back(vs);
			}
		}
		if (bScoreIdx < 3)
		{
			if (bMoveStarIdx < bScore.at(bScoreIdx))
			{
				auto st = (Star::Obj_ptr)vsMoveStar.at(bMoveStarIdx + bScoreIdx * 3);
				st->rStar.Move(&Vector2(40.f, 40.f));
				if (st->rStar.GetPosY() >= 430.f)
				{
					++bMoveStarIdx;
					if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
					{
						res->wsTest2.Play();
					}
				}
				return;
			}
			bMoveStarIdx = 0;
			++bScoreIdx;
			Pause(caTaskName, 30);
			return;
		}
		if (iRandomTime <= 0)
		{
			if (bPushHanko)
			{
				const float fW = (rHanko.GetW() <= rRestart.GetW()) ? rRestart.GetW() : rHanko.GetW() - 120.f;
				const float fH = (rHanko.GetH() <= rRestart.GetH()) ? rRestart.GetH() : rHanko.GetH() - 100.f;
				rHanko.Scaling(fW, fH);
				rHanko.SetPos(&rRestart.GetPos());
			}
			//static int tmp = 0, tmp2 = 0;
			if (iHanabiCount >= (bScore.at(0) + bScore.at(1) + bScore.at(2)) / 3) return;
			if (iHanabiTime >= 30)
			{
				iHanabiTime = 0;
				if (iHanabiCount == 1) sp_ef->_set_chip_type("b_sta");
				else sp_ef->_set_chip_type("r_sta");
				const Point pos[3] =
				{
					Point(Rec::Win.r * 0.25f, Rec::Win.b * 0.55f),
					Point(Rec::Win.r * 0.55f, Rec::Win.b * 0.75f),
					Point(Rec::Win.r * 0.25f, Rec::Win.b * 0.85f)
				};
				sp_ef->run(pos[iHanabiCount], 0);
				++iHanabiCount;
			}
			++iHanabiTime;
			sPercent = std::to_string(int((bScore.at(0) + bScore.at(1) + bScore.at(2)) * 100 / 9.f));	
			return;
		}
		if (iRandomTime <= 1)
		{
			auto cs = Add<Cursor::Obj>();
			cs->rCursorBase.SetPos(&Point(1450.f, 1020.f));
		}
		--iRandomTime;
		sPercent = std::to_string(rand() % 101);

		//constexpr float fPercent = 100 / 9.f;

		//else if (pad->Down(JOY_BUTTON6) || kb->Down('8') || kb->Down(VK_RETURN))
		//{
		//	RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
		//	if (auto manager = Find<StageManager::Obj>(StageManager::caTaskName))
		//	{
		//		manager->bStageNum = manager->bNextStage;
		//		if (manager->bStageNum == 255)
		//		{
		//			RemoveAll();
		//			Add<StageManager::Obj>();
		//			Add<Back::Obj>();
		//			Add<StageSelect::Obj>();
		//			Pause(2);
		//		}
		//		/*else
		//		{
		//			Add<Back::Obj>();
		//			Add<StageSelect::Obj>();
		//			Pause(2);
		//		}*/
		//	}
		//	Pause(2);
		//}
		//ButtonResize();
	}

	/*タスクの描画処理*/
	void Obj::Render()
	{
		if ((bScore.at(0) + bScore.at(1) + bScore.at(2)) >= 9)
		{
			Rec::FullPaint(RGB(0, 255, 204));
		}
		else if ((bScore.at(0) + bScore.at(1) + bScore.at(2)) >= 6)
		{
			Rec::FullPaint(RGB(255, 174, 0));
		}
		else
		{
			Rec::FullPaint(RGB(144, 151, 160));
		}
		if (auto s = RB::Find<Result::RS>(Result::caResName))
		{
			//rResult.Draw(&s->iResult, &Frec(0.f, 0.f, 16.f, 16.f));
			rResult.Draw(&s->iPaper, &Frec(0.f, 0.f, 64.f, 64.f));
			if (!bPushHanko)
			{
				rRestart.Draw(&s->iHanko, &Frec(16.f * 4, 0.f, 16.f, 16.f));
				//#ifdef _DEBUG
				rRestart.SetColor(RGB(255, 0, 0));
				rRestart.Draw();
				//#endif
			}
			auto divScore = (bScore.at(0) + bScore.at(1) + bScore.at(2)) / 3;
			auto srcIdxX = (divScore <= 0) ? 1 : divScore;
			rHanko.Draw(&s->iHanko, &Frec(16.f * srcIdxX, 0.f, 16.f, 16.f));
			//rNumber.Draw(&s->iResult, &Frec(16.f, 0.f, 16.f, 16.f), true);

			for (size_t i = 0; i < sPercent.length(); ++i)
			{
				Rec rd(120 + 550.f, 120 + 600.f, 240.f, 240.f);
				if (sPercent.length() >= 3) rd.Move(&Vector2(-240.f, 0));
				const float fOfsX = (sPercent.at(i) - '0' + 1) * 16.f;
				rd.Move(&Vector2(i * 240.f, 0.f));
#ifdef _DEBUG
				rd.SetColor(RGB(255, 0, 0));
				rd.Draw();
#endif
				rd.Draw(&s->iResult, &Frec(fOfsX, 0.f, 16.f, 16.f));
			}
#ifdef _DEBUG
			rPercent.SetColor(RGB(255, 0, 0));
			rPercent.Draw();
#endif
			if (iRandomTime == 60) return;
			rPercent.Draw(&s->iResult, &Frec(0.f, 16.f, 16.f, 16.f));
		}
	}
		//Point pPos(800, 1000);
		//if (sPercent.length() >= 3) pPos.x -= 6 * 30;
		//em.Msg() = sPercent;
		//em.DrawAscii(pPos, 6 * 30, 24 * 30);
	}

	void Obj::ButtonInit()
	{
		rRestart = Rec(1460.f, 720.f, 0.f, 0.f);
	}
	void Obj::SetParam(const byte abStageGroupNumber, const std::array<byte, 3> &abScores)
	{
		bStageGroupNumber = abStageGroupNumber;
		for (int i = 0; i < 3; ++i)
		{
			auto sp = Add<StagePicture::Obj>();
			sp->LoadImg((bStageGroupNumber - 1) * 3 + i + 1);
			sp->SetSize(410.0f, 250.0f);
			sp->SetPos(&Point(490 + i * 470.f, 250.f));
		}
		for (size_t i = 0; i < abScores.size(); ++i)
		{
			bScore.at(i) = abScores.at(i);
		}
	}
}
