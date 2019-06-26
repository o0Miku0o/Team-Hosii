#pragma once
#include "MyGame/MyApp.h"
#include "Alien.h"

using namespace std;

namespace StageLoad
{
	const char caTaskName[] = { "ロードステージタスク" };
	const char caResName[] = { "ロードステージリソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*タスクオブジェクトクラス*/
	typedef class Obj : public TaskBase
	{
	public:
		/*必要なメンバはここに追加*/
		struct Base
		{
			bool state;
			int iNum;
			vector<Point> vpPos;
		};
		struct Fragment : public Base {
			vector<int> iColor;
		}sFragement;

		struct Star : public Base {
			vector<int> viChange;
			vector<float>vfSize;
		}sStar;

		struct BreakStar : public Base {
			vector<int> viChange;
			vector<bool> bMode;
		}sBreakStar;

		struct Planet  {
			bool state;
			Rec rec;
		}sJupiter, sNeptune, sSaturn;

		struct SMeteo : public Base {
			vector<Vector2> vvSpd;
		}sMeteo;

		struct SAlien : public Base {
			vector<Alien::Move> vaMove;
			vector<Alien::Hit> vaBMHit, vaFGHit;
			vector<Alien::Anim> vaAnim;
		}sAlien;

		struct SBlackhole : public Base {
			vector<float> vpSize;
			vector<int>   viMode;
		}sblackhole;

		struct SReuslt {
			bool state;
			int iFragement, iNextStage;
		}sResult;

		byte bStageNum;

		bool isLoad;
		bool LoadStage(int iStage);
		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
		void LoadFragments(ifstream &ifs);
		void LoadStar(ifstream &ifs);
		void LoadBreakStar(ifstream &ifs);
		void LoadPlanet(ifstream &ifs, Planet &planet);
		void LoadMeteo(ifstream &ifs);
		void LoadAlien(ifstream &ifs);
		void LoadBlackHole(ifstream &ifs);
		void LoadResult(ifstream &ifs);

	public:
		void Update();
		void Render();
	}*Obj_ptr;

	inline const unsigned int StageGroup(const unsigned int auiStageNum)
	{
		return (auiStageNum / 10);
	}
	inline const unsigned int StageNumber(const unsigned int auiStageNum)
	{
		return (auiStageNum % 10);
	}
}