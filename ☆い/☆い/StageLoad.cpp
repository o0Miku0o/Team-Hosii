#include "FragmentGenerator.h"
#include "StarGenerator.h"
#include "Jupitor.h"
#include "Neptune.h"
#include "Meteo.h"
#include "AlienGenerator.h"
#include "BlackHoleGenerator.h"
#include "StageLoad.h"
#include "StageManager.h"
#include "Player.h"
#include "Stage.h"
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
		SetName("ロードステージタスク");
		/*リソース生成*/

		/*タスクの生成*/
		Add<Player::Obj>();
		isLoad = false;
		sFragement.state = false;
		sStar.state = false;
		sJupiter.state = false;
		sNeptune.state = false;
		sMeteo.state = false;
		sAlien.state = false;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if(auto manager = Find<StageManager::Obj>("ステージ統括タスク")){
			bStageNum = manager->bStageNum;
		}

		if (!isLoad && LoadStage(bStageNum)) {
			if (sFragement.state) {
				auto fg = Add<FragmentGenerator::Obj>();
				fg->Bridge2(sFragement.iNum, sFragement.vpPos, sFragement.iColor);
			}
			if (sStar.state) {
				auto sg = Add<StarGenerator::Obj>();
				sg->Bridge(sStar.iNum, sStar.viChange, sStar.vpPos);
			}
			if (sJupiter.state) {
				auto pj = Add<Jupitor::Obj>();
				pj->rJupitor = sJupiter.rec;
			}
			if (sNeptune.state) {
				auto pn = Add<Neptune::Obj>();
				pn->rNeptune = sNeptune.rec;
			}
			if (sAlien.state) {
				auto al = Add<AlienGenerator::Obj>();
				al->Bridge(sAlien.iNum, sAlien.vpPos, sAlien.vaMove, sAlien.vaBMHit, sAlien.vaFGHit, sAlien.vaAnim);
			}
			if (sblackhole.state) {
				auto bh = Add<BlackHoleGenerator::Obj>();
				bh->Bridge(sblackhole.iNum, sblackhole.vpPos, sblackhole.vpSize, sblackhole.viMode);
			}
			isLoad = true;
			Remove(this);
			Add<Stage::Obj>();
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
	bool Obj::LoadStage(int iStage) {
		string path = "./data/stage/stage" + to_string(iStage / 10) + to_string(iStage % 10) + ".txt";
		ifstream ifs(path);
		if (!ifs) {
			return false;
		}
		string sIdentifier;
		//欠片、星、木星、海王星、隕石、外界人、ブラックホール、コメント始点、コメント終点
		const char* sArr[] = { "F", "S", "J", "N", "M", "A", "B", "R", "/*", "*/", };
		while (!ifs.eof()) {
			ifs >> sIdentifier;
			if (sIdentifier == sArr[0]) {
				LoadFragments(ifs);
				sFragement.state = true;
			}
			else if (sIdentifier == sArr[1]) {
				LoadStar(ifs);
				sStar.state = true;
			}
			else if (sIdentifier == sArr[2]) {
				LoadPlanet(ifs, sJupiter);
				sJupiter.state = true;
			}
			else if (sIdentifier == sArr[3]) {
				LoadPlanet(ifs, sNeptune);
				sNeptune.state = true;
			}
			else if (sIdentifier == sArr[4]) {
				LoadMeteo(ifs);
				sMeteo.state = true;
			}
			else if (sIdentifier == sArr[5]) {
				LoadAlien(ifs);
				sAlien.state = true;
			}
			else if (sIdentifier == sArr[6]) {
				LoadBlackHole(ifs);
				sblackhole.state = true;
			}
			else if (sIdentifier == sArr[7]) {
				//Load 
				sResult.state = true;
			}
			else if (sIdentifier == sArr[8]) {
				string dummy;
				ifs >> dummy;
				while (dummy == sArr[9]) {
					ifs >> dummy;
				}
			}
		}
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
	}
	void Obj::LoadStar(ifstream &ifs) {
		ifs >> sStar.iNum;
		for (int i = 0; i < sStar.iNum; ++i) {
			float x, y;
			int change;
			ifs  >> x >> y >> change;
			sStar.viChange.push_back(change);
			sStar.vpPos.push_back(Point(x, y));
		}
	}

	void Obj::LoadPlanet(ifstream &ifs, Planet &planet) {
		ifs >> planet.iNum;
		for (int i = 0; i < planet.iNum; ++i) {
			float x, y, r;
			ifs >> x >> y >> r;
			planet.rec = Rec(x, y, r, r);
		}
		planet.state = true;
	}

	void Obj::LoadMeteo(ifstream &ifs) {
		ifs >> sMeteo.iNum;
		for (int i = 0; i < sMeteo.iNum; ++i) {
			float x, y;
			ifs >> x >> y;
			sMeteo.vpPos.push_back(Point(x, y));
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
	}
	void Obj::LoadResult(ifstream &ifs) {
		
	}
}
