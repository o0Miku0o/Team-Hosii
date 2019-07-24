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
		sFragement.state = false;
		sStar.state = false;
		sBreakStar.state = false;
		sJupiter.state = false;
		sNeptune.state = false;
		sSaturn.state = false;
		sMeteo.state = false;
		sAlien.state = false;
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
			if (sJupiter.state) {
				auto pj = Add<Jupitor::Obj>();
				pj->rJupitor = sJupiter.rec;
			}
			if (sNeptune.state) {
				auto pn = Add<Neptune::Obj>();
				pn->rNeptune = sNeptune.rec;
			}
			if (sSaturn.state) {
				auto sa = Add<Saturn::Obj>();
				sa->rSaturn = sSaturn.rec;
			}
			//欠片は惑星たちを読んだ後に
			if (sFragement.state) {
				auto fg = Add<FragmentGenerator::Obj>();
				fg->Bridge2(sFragement.iNum, sFragement.vpPos, sFragement.iColor);
			}
			if (sStar.state) {
				auto sg = Add<StarGenerator::Obj>();
				sg->Bridge(sStar.iNum, sStar.viChange, sStar.vpPos);
			}
			if (sBreakStar.state) {
				auto bs = Add<BreakStarGenerator::Obj>();
				bs->Bridge(sBreakStar.iNum, sBreakStar.viChange, sBreakStar.vpPos, sBreakStar.bMode);
			}
			if (sMeteo.state) {
				auto met = Add<MeteoGenerator::Obj>();
				met->Bridge(sMeteo.iNum, sMeteo.vpPos, sMeteo.vvSpd);
			}
			if (sAlien.state) {
				auto al = Add<AlienGenerator::Obj>();
				al->Bridge(sAlien.iNum, sAlien.vpPos, sAlien.vaMove, sAlien.vaBMHit, sAlien.vaFGHit, sAlien.vaAnim);
			}
			if (sblackhole.state) {
				auto bh = Add<BlackHoleGenerator::Obj>();
				bh->Bridge(sblackhole.iNum, sblackhole.vpPos, sblackhole.vpSize, sblackhole.viMode);
			}
			if (sResult.state) {
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
		const char* sArr[] = { "F", "S", "Bs", "J", "N","Sa", "M", "A", "B", "R",  "/*", "*/", };
		while (!ifs.eof()) {
			ifs >> sIdentifier;
			if (sIdentifier == sArr[0]) {
				LoadFragments(ifs);
			}
			else if (sIdentifier == sArr[1]) {
				LoadStar(ifs);
			}
			else if (sIdentifier == sArr[2]) {
				LoadBreakStar(ifs);
			}
			else if (sIdentifier == sArr[3]) {
				LoadPlanet(ifs, sJupiter);
			}
			else if (sIdentifier == sArr[4]) {
				LoadPlanet(ifs, sNeptune);
			}
			else if (sIdentifier == sArr[5]) {
				LoadPlanet(ifs, sSaturn);
			}
			else if (sIdentifier == sArr[6]) {
				LoadMeteo(ifs);
			}
			else if (sIdentifier == sArr[7]) {
				LoadAlien(ifs);
			}
			else if (sIdentifier == sArr[8]) {
				LoadBlackHole(ifs);
			}
			else if (sIdentifier == sArr[9]) {
				LoadResult(ifs);
			}
			else if (sIdentifier == sArr[10]) {
				string dummy;
				ifs >> dummy;
				while (dummy == sArr[11]) {
					ifs >> dummy;
				}
			}
		}
		ifs.close();
		return true;
	}

	void Obj::LoadFragments(ifstream &ifs) {
		ifs >> sFragement.iNum;
		for (int i = 0; i < sFragement.iNum; ++i) {
			float x, y;
			int color;
			ifs >> x >> y >> color;
			sFragement.vpPos.push_back(Point(x, y));
			sFragement.iColor.push_back(color);
		}
		sFragement.state = true;
	}
	void Obj::LoadStar(ifstream &ifs) {
		ifs >> sStar.iNum;
		for (int i = 0; i < sStar.iNum; ++i) {
			float x, y;
			int change;
			ifs >> x >> y >> change;
			sStar.viChange.push_back(change);
			sStar.vpPos.push_back(Point(x, y));
		}
		sStar.state = true;
	}

	void Obj::LoadBreakStar(ifstream &ifs) {
		ifs >> sBreakStar.iNum;
		for (int i = 0; i < sBreakStar.iNum; ++i) {
			float x, y;
			int change;
			string mode;
			ifs >> x >> y >> change >> mode;
			sBreakStar.vpPos.push_back(Point(x, y));
			sBreakStar.viChange.push_back(change);
			if (mode == "True") {
				sBreakStar.bMode.push_back(true);
			}
			else {
				sBreakStar.bMode.push_back(false);
			}
		}
		sBreakStar.state = true;
	}

	void Obj::LoadPlanet(ifstream &ifs, Planet &planet) {
		float x, y, r;
		ifs >> x >> y >> r;
		planet.rec = Rec(x, y, r, r);
		planet.state = true;
	}

	void Obj::LoadMeteo(ifstream &ifs) {
		ifs >> sMeteo.iNum;
		for (int i = 0; i < sMeteo.iNum; ++i) {
			float posX, posY, x, y;
			ifs >> posX >> posY >> x >> y;
			sMeteo.vpPos.push_back(Point(posX, posY));
			sMeteo.vvSpd.push_back(Vector2(x, y));
		}
		sMeteo.state = true;
	}

	void Obj::LoadAlien(ifstream &ifs) {
		ifs >> sAlien.iNum;
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
		for (int i = 0; i < sAlien.iNum; ++i) {
			float x, y;
			string bufMove, bufHitB, bufHitF, bufAnim;
			ifs >> x >> y >> bufMove >> bufHitB >> bufHitF >> bufAnim;
			sAlien.vpPos.push_back(Point(x, y));
			//移動タイプを検索
			for (int i = 0; i < sizeof(arrMove) / sizeof(char*); ++i) {
				if (bufMove == arrMove[i]) {
					sAlien.vaMove.push_back(fPmove[i]);
					break;
				}
			}
			//ビームの行動タイプを検索
			for (int i = 0; i < sizeof(arrHitB) / sizeof(char*); ++i) {
				if (bufHitB == arrHitB[i]) {
					sAlien.vaBMHit.push_back(fpBMHit[i]);
					break;
				}
			}
			//欠片の行動タイプを検索
			for (int i = 0; i < sizeof(arrHitF) / sizeof(char*); ++i) {
				if (bufHitF == arrHitF[i]) {
					sAlien.vaFGHit.push_back(fpFGHit[i]);
					break;
				}
			}
			//欠片の行動タイプを検索
			for (int i = 0; i < sizeof(arrAnim) / sizeof(char*); ++i) {
				if (bufAnim == arrAnim[i]) {
					sAlien.vaAnim.push_back(fpAnim[i]);
					break;
				}
			}
		}
		sAlien.state = true;
	}
	//座標、大きさ
	void Obj::LoadBlackHole(ifstream &ifs) {
		ifs >> sblackhole.iNum;
		for (int i = 0; i < sblackhole.iNum; ++i) {
			float x, y, r;
			int m;
			ifs >> x >> y >> r >> m;
			sblackhole.vpPos.push_back(Point(x, y));
			sblackhole.vpSize.push_back(r);
			sblackhole.viMode.push_back(m);
		}
		sblackhole.state = true;
	}
	void Obj::LoadResult(ifstream &ifs) {
		ifs >> sResult.iFragement >> sResult.iNextStage;
		sResult.state = true;
	}
}
