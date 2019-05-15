#include "Result.h"
#include "StageManager.h"
#include "StageSelect.h"
#include "Star.h"
#include "BreakStar.h"
#include "StarGenerator.h"
#include "Back.h"
#include "StageLoad.h"

namespace Result
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iWord.ImageCreate("./data/image/other/word.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{

	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName("リザルトタスク");
		/*リソース生成*/
		RB::Add<Result::RS>("リザルトリソース");
		/*タスクの生成*/

		/*データの初期化*/
		rBack = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b);

		rPlayer = Rec(180.f, 1000.f, 16.f * 70.f, 16.f * 70.f);
		rPlayer.SetDeg(95);

		rWord = Rec(1370.f, 750.f, 16.f * 60.f, 16.f * 10.f);

		auto sg = Add<StarGenerator::Obj>();
		vector<Point> pStArr = { Point(1100.f,500.f),Point(1300.f,500.f),Point(1500.f,500.f),Point(1100.f - 1000.f,500.f - 1000.f),Point(1300.f - 1000.f,500.f - 1000.f),Point(1500.f - 1000.f,500.f - 1000.f) };
		vector<int> iArr = { 37,37,37,25,25,25 };
		vector<int> iEff = { 55, 55, 55, 47, 47, 47, };
		sg->Bridge(6, iArr, iEff, pStArr);
		bNextStage = 0;
		bMoveStarIdx = 0;
		bScore = 1;

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
		if (bMoveStarIdx < bScore)
		{
			auto st = (Star::OBJ_ptr)vsMoveStar[bMoveStarIdx];
			st->rStar.Move(&Vector2(20.f, 20.f));
			if (st->rStar.GetPosY() >= 500.f)
			{
				++bMoveStarIdx;
				if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
				{
					res->wsTest2.Play();
				}
			}
		}
		//else if (pad->Down(J_BUT_6) || kb->Down(VK_RETURN))
		//{
		//	RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
		//	//			Add<Back::Obj>();
		//	switch (bNextStage)
		//	{
		//	case 1:
		//	{
		//		Add<Stage11::Obj>();
		//		break;
		//	}
		//	case 2:
		//	{
		//		if (auto manager = Find<StageManager::Obj>("ステージ統括タスク")) {
		//			manager->bStageNum = 2;
		//		}
		//		Add<StageLoad::Obj>();
		//		//Add<Stage12::Obj>();
		//		break;
		//	}
		//	case 3:
		//	{
		//		Add<Stage13::Obj>();
		//		break;
		//	}
		//	case 4:
		//	{
		//		Add<Stage21::Obj>();
		//		break;
		//	}
		//	case 5:
		//	{
		//		Add<Stage22::Obj>();
		//		break;
		//	}
		//	case 6:
		//	{
		//		Add<Stage23::Obj>();
		//		break;
		//	}
		//	case 7:
		//	{
		//		Add<Stage31::Obj>();
		//		break;
		//	}
		//	case 8:
		//	{
		//		Add<Stage32::Obj>();
		//		break;
		//	}
		//	case 9:
		//	{
		//		Add<Stage33::Obj>();
		//		break;
		//	}
		//	case 10:
		//	{
		//		Add<Stage41::Obj>();
		//		break;
		//	}
		//	case 11:
		//	{
		//		Add<Stage42::Obj>();
		//		break;
		//	}
		//	case 12:
		//	{
		//		Add<Stage43::Obj>();
		//		break;
		//	}
		//	case 13:
		//	{
		//		Add<Stage51::Obj>();
		//		break;
		//	}
		//	case 14:
		//	{
		//		Add<Stage52::Obj>();
		//		break;
		//	}
		//	case 15:
		//	{
		//		Add<Stage53::Obj>();
		//		break;
		//	}
		//	default:
		//	{
		//		Add<StageSelect::Obj>();
		//		break;
		//	}
		//	}
		//	Pause(2);
		//}
		else if (pad->Down(J_BUT_6) || kb->Down('8') || kb->Down(VK_RETURN)) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			//			Add<Back::Obj>();
			if (auto manager = Find<StageManager::Obj>("ステージ統括タスク")) {
				manager->bStageNum = manager->bNextStage;
				if (manager->bStageNum == 255) {
					RemoveAll();
					Add<StageManager::Obj>();
					Add<Back::Obj>();
					Add<StageSelect::Obj>();
					Pause(2);
				}
				else {
					Add<StageLoad::Obj>();
					Pause(2);
				}
			}
			Pause(2);
		}
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
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			//rBack.Draw(&res->iStageImg, &Frec(16.f * (45.f - (bScore - 1)), 0.f, 16.f, 16.f));

			Frec src(16.f * 6.f, 16.f, 16.f, 16.f);
			rPlayer.Draw(&res->iStageImg, &src, true);
		}

		if (auto s = RB::Find<Result::RS>("リザルトリソース"))
		{
			rWord.Draw(&s->iWord, &Frec(0, 16.f * 6.f, 16.f * 5.f, 16.f), true);
		}
	}
}
