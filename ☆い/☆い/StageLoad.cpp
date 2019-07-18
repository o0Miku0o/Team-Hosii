#include "FragmentGenerator.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "Jupitor.h"
#include "Neptune.h"
#include "Saturn.h"
#include "MeteoGenerator.h"
#include "AlienGenerator.h"
#include "BlackHoleGenerator.h"
#include "StageLoad.h"
#include "StageManager.h"
#include "Player.h"
#include "Stage.h"
#include "Back.h"
#include "StageSelect.h"
#include "FadeInOut.h"
#include "Gas.h"
#include "Rail.h"
#include "Tutorial.h"
#include <fstream>

namespace StageLoad
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
#ifndef _DEBUG
		Add<Gas::Obj>();
#endif
		Add<Player::Obj>();

		isLoad = false;
		for (int i = 0; i < 8; ++i) {
			state[i] = false;
		}
		bStageNum = 11;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (auto manager = Find<StageManager::Obj>(StageManager::caTaskName)) {
			bStageNum = manager->bStageNum;
		}

		if (!isLoad && LoadStage(bStageNum)) {
			//惑星は欠片を呼ぶ前に必ず
			if (state[PLANET]) {
				for (int i = 0; i < sPlanet.num; ++i) {
					if (sPlanet.imgSrc.at(i) == PlanetType::JUPITOR) {
						auto pj = Add<Jupitor::Obj>();
						pj->rJupitor = Rec(sPlanet.pos.at(i).x, sPlanet.pos.at(i).y, sPlanet.size.at(i), sPlanet.size.at(i));
					}
					else if (sPlanet.imgSrc.at(i) == PlanetType::NEPTUNE) {
						auto pn = Add<Neptune::Obj>();
						pn->rNeptune = Rec(sPlanet.pos.at(i).x, sPlanet.pos.at(i).y, sPlanet.size.at(i), sPlanet.size.at(i));
					}
					else if (sPlanet.imgSrc.at(i) == PlanetType::SATURN) {
						auto ps = Add<Saturn::Obj>();
						ps->rSaturn = Rec(sPlanet.pos.at(i).x, sPlanet.pos.at(i).y, sPlanet.size.at(i), sPlanet.size.at(i));
					}
				}
			}

			if (state[STAR]) {
				auto sg = Add<StarGenerator::Obj>();
				sg->Bridge(sStar.num, sStar.imgSrc, sStar.pos);
			}

			//欠片は惑星たちを読んだ後に
			if (state[FRAGMENT]) {
				auto fg = Add<FragmentGenerator::Obj>();
				fg->Bridge2(sFragment.num, sFragment.pos, sFragment.imgSrc);
			}

			if (state[BLACKHOLE]) {
				auto bh = Add<BlackHoleGenerator::Obj>();
				bh->Bridge(sBlackHole.num, sBlackHole.pos, sBlackHole.size, sBlackHole.mode);
			}

			if (state[BREAKSTAR]) {
				auto bs = Add<BreakStarGenerator::Obj>();
				bs->Bridge(sBreakStar.num, sBreakStar.imgSrc, sBreakStar.pos, sBreakStar.mode);
			}

			if (state[METEO]) {
				auto met = Add<MeteoGenerator::Obj>();
				met->Bridge(sMeteo.num, sMeteo.pos, sMeteo.moveVec);
			}

			if (state[ALIEN]) {
				auto al = Add<AlienGenerator::Obj>();
				al->Bridge(sAlien.num, sAlien.pos, sAlien.aMove, sAlien.aBMHit, sAlien.aFGHit, sAlien.aAnim);
			}

			if (state[RESULT]) {
				if (auto ma = Find<StageManager::Obj>(StageManager::caTaskName)) {
					ma->usBeamCount = 0;
					ma->bClearFragmentNum = 0;
					ma->bClearFragmentNumMax = sResult.iFragement;
					ma->bNextStage = sResult.iNextStage;
				}
			}
			isLoad = true;
			Remove(this);
			Add<Stage::Obj>();
			Add<Rail::Obj>();
			/*ためし*/
			const Point *ppTutorialPos = nullptr;
			if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
			{
				ppTutorialPos = &sm->pTutorialPos;
			}
			Tutorial::Ttl_State tState = Tutorial::Ttl_State::TTS_BUTTON;
			unsigned int uiBtnOrStick = Tutorial::Buttons::BTN_R;

			if (StageGroup(bStageNum) == 1)
			{
				if (StageNumber(bStageNum) == 2)
				{
					tState = Tutorial::Ttl_State::TTS_STICK;
				}
				else if (StageNumber(bStageNum) == 3)
				{
					tState = Tutorial::Ttl_State::TTS_STICK;
					uiBtnOrStick = Tutorial::Stk_State::STS_NEUTRAL_R;
				}
				auto tu = Add<Tutorial::Obj>();
				tu->SetParam(600, tState, uiBtnOrStick, &Point(50.f, 50.f), ppTutorialPos);
			}
			else if (StageNumber(bStageNum) == 1)
			{
				auto tu = Add<Tutorial::Obj>();
				tu->SetParam(600, tState, uiBtnOrStick, &Point(50.f, 50.f), ppTutorialPos);
			}
			/**/
			if (auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
			{
				//fade->bActive = false;
				fade->Start();
				fade->bIsIn = false;
			}
			else
			{
				fade = Add<FadeInOut::Obj>();
				fade->bIsIn = false;
			}
			//auto fade = Add<FadeInOut::Obj>();
			//fade->bIsIn = false;
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
	bool Obj::LoadStage(int iStage) {
		string path = "./data/stage/stage" + to_string(StageGroup(iStage)) + to_string(StageNumber(iStage)) + ".txt";
		ifstream ifs(path);
		if (!ifs) {
			return false;
		}
		string sIdentifier;
		//欠片、星、壊れる星、木星、海王星、土星、隕石、外界人、ブラックホール、コメント始点、コメント終点
		const char* sArr[] = { "Star", "Fragment", "Planet", "BlackHole", "Alien", "BreakStar", "Meteo", "Result", "/*", "*/", };

		while (!ifs.eof()) {
			ifs >> sIdentifier;
			if (sIdentifier == sArr[STAR]) {
				LoadStar(ifs);
			}
			else if (sIdentifier == sArr[FRAGMENT]) {
				LoadFragments(ifs);
			}
			else if (sIdentifier == sArr[PLANET]) {
				LoadPlanet(ifs);
			}
			else if (sIdentifier == sArr[BLACKHOLE]) {
				LoadBlackHole(ifs);
			}
			else if (sIdentifier == sArr[ALIEN]) {
				LoadAlien(ifs);
			}
			else if (sIdentifier == sArr[BREAKSTAR]) {
				LoadBreakStar(ifs);
			}
			else if (sIdentifier == sArr[METEO]) {
				LoadMeteo(ifs);
			}
			else if (sIdentifier == sArr[RESULT]) {
				LoadResult(ifs);
			}
			else if (sIdentifier == sArr[COMMNETSTART]) {
				string dummy;
				ifs >> dummy;
				while (dummy == sArr[COMMNETEND]) {
					ifs >> dummy;
				}
			}
		}
		ifs.close();
		return true;
	}

	void Obj::LoadStar(ifstream &ifs) {
		Point pos;
		int img;
		ifs >> pos.x >> pos.y >> img;
		sStar.pos.push_back(pos);
		sStar.imgSrc.push_back(img);
		sStar.num = sStar.pos.size();

		state[STAR] = true;
	}

	void Obj::LoadFragments(ifstream &ifs) {
		Point pos;
		int img;
		ifs >> pos.x >> pos.y >> img;
		sFragment.pos.push_back(pos);

		if (img == FragMentImgSrc::YELLOW)
			sFragment.imgSrc.push_back(0);
		else if (img == FragMentImgSrc::RED)
			sFragment.imgSrc.push_back(1);
		else if (img == FragMentImgSrc::BLUE)
			sFragment.imgSrc.push_back(2);

		sFragment.num = sFragment.pos.size();

		state[FRAGMENT] = true;
	}


	void Obj::LoadBreakStar(ifstream &ifs) {
		Point pos;
		int img;
		ifs >> pos.x >> pos.y >> img;
		sBreakStar.pos.push_back(pos);
		sBreakStar.imgSrc.push_back(img);
		if (img == BreakStarMode::BREAKABLE)
			sBreakStar.mode.push_back(false);
		else if (img == BreakStarMode::NONBREAK)
			sBreakStar.mode.push_back(true);
		sBreakStar.num = sBreakStar.pos.size();

		state[BREAKSTAR] = true;
	}

	void Obj::LoadPlanet(ifstream &ifs) {
		Point pos;
		int img;
		float size;
		ifs >> pos.x >> pos.y >> img >> size;

		sPlanet.pos.push_back(pos);
		sPlanet.imgSrc.push_back(img);
		sPlanet.size.push_back(size);
		sPlanet.num = sPlanet.pos.size();

		state[PLANET] = true;
	}

	void Obj::LoadMeteo(ifstream &ifs) {
		Point pos;
		int img;
		float size, vecY;
		ifs >> pos.x >> pos.y >> img >> size >> vecY;

		sMeteo.pos.push_back(pos);
		sMeteo.moveVec.push_back(Vector2(0, vecY));
		sMeteo.num = sMeteo.pos.size();
		state[METEO] = true;
	}

	void Obj::LoadAlien(ifstream &ifs) {
		/*
		const char* arrMove[] = { "aMH", "aMH_", "aMV", "aMV_", "aMR", "aMR_", "aMS" };
		Alien::Move fPmove[7] = { Alien::MoveHorizontal, Alien::Move_Horizontal, Alien::MoveVertical,
			Alien::Move_Vertical, Alien::MoveRotation, Alien::Move_Rotation, Alien::MoveStay };
		const char* arrHitB[] = { "aBRE", "aBDR", "aBUR", "aBDL", "aBUL" };
		Alien::Hit fpBMHit[5] = { Alien::BMRemove, Alien::BMReflectDR, Alien::BMReflectUR, Alien::BMReflectDL, Alien::BMReflectUL };
		const char* arrHitF[] = { "aFRE", "aFDR", "aFUR", "aFDL", "aFUL" };
		Alien::Hit fpFGHit[5] = { Alien::FGRemove, Alien::FGReflectDR,Alien::FGReflectUR,Alien::FGReflectDL,Alien::FGReflectUL };
		const char* arrAnim[] = { "aANo", "aAHo", "aARo", "aADR", "aAUR", "aADL", "aAUL" };
		Alien::Anim fpAnim[7] = { Alien::AnimNormal, Alien::AnimHorizontal, Alien::AnimRotation,Alien::AnimReflectDR,
			Alien::AnimReflectUR, Alien::AnimReflectDL, Alien::AnimReflectUL };
		*/
		const char* arrMove[] = { "停止", "U方向", "D方向", "R方向", "L方向","R回転","L回転" };

		Point pos;
		int img;
		string mode;
		Alien::Move aMove;
		Alien::Hit aBHit, aFHit;
		Alien::Anim aAnim;

		ifs >> pos.x >> pos.y >> img >> mode;

		//エイリアンの決め
		switch (img)
		{
		case AlienIMG::VERTICAL:
			aAnim = Alien::AnimNormal;
			aBHit = Alien::BMReflectUL;
			aFHit = Alien::FGReflectUL;
			break;
		case AlienIMG::HORIZONTAL:
			aAnim = Alien::AnimHorizontal;
			aBHit = Alien::BMReflectDL;
			aFHit = Alien::FGReflectDL;
			break;
		case AlienIMG::ROTATION:
			aAnim = Alien::AnimRotation;
			aBHit = Alien::BMReflectDL;
			aFHit = Alien::FGReflectDL;
			break;
		case AlienIMG::ROTATIONREVERSE:
			aAnim = Alien::AnimRotation;
			aBHit = Alien::BMReflectUR;
			aFHit = Alien::FGReflectUR;
			break;
		case AlienIMG::REFLECTDR:
			aAnim = Alien::AnimReflectDR;
			aBHit = Alien::BMReflectDR;
			aFHit = Alien::FGReflectDR;
			break;
		case AlienIMG::REFLECTUR:
			aAnim = Alien::AnimReflectUR;
			aBHit = Alien::BMReflectUR;
			aFHit = Alien::FGReflectUR;
			break;
		case AlienIMG::REFLECTDL:
			aAnim = Alien::AnimReflectDL;
			aBHit = Alien::BMReflectDL;
			aFHit = Alien::FGReflectDL;
			break;
		case AlienIMG::REFLECTUL:
			aAnim = Alien::AnimReflectUL;
			aBHit = Alien::BMReflectUL;
			aFHit = Alien::FGReflectUL;
			break;
		}

		//エイリアンの移動決め
		int div = 0;
		for (; div < sizeof(arrMove) / sizeof(char*); ++div) {
			if (mode == arrMove[div]) {

				break;
			}
		}
		switch (div)
		{
		case AlienMOVE::MOVESTAY:
			aMove = Alien::MoveStay;
			break;
		case AlienMOVE::MOVEVERTICAL:
			aMove = Alien::MoveVertical;
			break;
		case AlienMOVE::MOVEVERTICALREVERSE:
			aMove = Alien::Move_Vertical;
			aBHit = Alien::BMReflectDL;
			aFHit = Alien::FGReflectDL;
			break;
		case AlienMOVE::MOVEHORIZONTAL:
			aMove = Alien::MoveHorizontal;
			break;
		case AlienMOVE::MOVEHORIZONTALREVERSE:
			aMove = Alien::Move_Horizontal;
			aBHit = Alien::BMReflectDL;
			aFHit = Alien::FGReflectDL;
			break;
		case AlienMOVE::MOVEROTATION:
			aMove = Alien::MoveRotation;
			break;
		case AlienMOVE::MOVEROTATIONREVERSE:
			aMove = Alien::Move_Rotation;
			break;
		}

		sAlien.pos.push_back(pos);
		sAlien.aMove.push_back(aMove);
		sAlien.aBMHit.push_back(aBHit);
		sAlien.aFGHit.push_back(aFHit);
		sAlien.aAnim.push_back(aAnim);


		//string bufMove, bufHitB, bufHitF, bufAnim;
		//ifs >> x >> y >> bufMove >> bufHitB >> bufHitF >> bufAnim;
		//sAlien.vpPos.push_back(Point(x, y));
		////移動タイプを検索
		//for (int i = 0; i < sizeof(arrMove) / sizeof(char*); ++i) {
		//	if (bufMove == arrMove[i]) {
		//		sAlien.vaMove.push_back(fPmove[i]);
		//		break;
		//	}
		//}
		////ビームの行動タイプを検索
		//for (int i = 0; i < sizeof(arrHitB) / sizeof(char*); ++i) {
		//	if (bufHitB == arrHitB[i]) {
		//		sAlien.vaBMHit.push_back(fpBMHit[i]);
		//		break;
		//	}
		//}
		////欠片の行動タイプを検索
		//for (int i = 0; i < sizeof(arrHitF) / sizeof(char*); ++i) {
		//	if (bufHitF == arrHitF[i]) {
		//		sAlien.vaFGHit.push_back(fpFGHit[i]);
		//		break;
		//	}
		//}
		////欠片の行動タイプを検索
		//for (int i = 0; i < sizeof(arrAnim) / sizeof(char*); ++i) {
		//	if (bufAnim == arrAnim[i]) {
		//		sAlien.vaAnim.push_back(fpAnim[i]);
		//		break;
		//	}
		//}
		sAlien.num = sAlien.pos.size();
		state[ALIEN] = true;
	}
	//座標、大きさ
	void Obj::LoadBlackHole(ifstream &ifs) {
		Point pos;
		float size;
		int img;
		ifs >> pos.x >> pos.y >> img >> size;

		sBlackHole.pos.push_back(pos);
		sBlackHole.imgSrc.push_back(img);
		sBlackHole.size.push_back(size);
		//仮処理
		sBlackHole.mode.push_back(0);
		sBlackHole.num = sBlackHole.pos.size();

		state[BLACKHOLE] = true;
	}
	void Obj::LoadResult(ifstream &ifs) {
		ifs >> sResult.iFragement >> sResult.iNextStage;
		state[RESULT] = true;
	}
}
