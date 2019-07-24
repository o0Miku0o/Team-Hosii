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
		enum Value
		{
			STAR, FRAGMENT, PLANET, BLACKHOLE, ALIEN,
			BREAKSTAR, METEO, RESULT, COMMNETSTART, COMMNETEND
		};
		bool state[8];
		struct Base
		{
			int num;
			vector<Point> pos;
			vector<int> imgSrc;
		};

		Base sStar, sFragment;
		enum FragMentImgSrc {
			YELLOW = 2, RED = 60, BLUE = 68
		};

		struct BreakStar : public Base
		{
			vector<bool> mode;
		}sBreakStar;
		enum BreakStarMode {
			BREAKABLE = 34, NONBREAK = 37
		};

		struct Planet : public Base {
			vector<float> size;
		};
		Planet sPlanet;
		enum PlanetType {
			JUPITOR = 112, NEPTUNE = 116, SATURN = 120
		};

		struct BlackHole : public Base {
			vector<float> size;
			vector<int> mode;
		};
		BlackHole sBlackHole;


		struct Meteo : public Base {
			vector<Vector2> moveVec;
		};
		Meteo sMeteo;

		struct SAlien : public Base {
			vector<Alien::Move> aMove;
			vector<Alien::Hit> aBMHit, aFGHit;
			vector<Alien::Anim> aAnim;
		}sAlien;

		enum AlienIMG {
			VERTICAL = 14, HORIZONTAL = 16, ROTATION = 18, ROTATIONREVERSE = 20, REFLECTDR = 128, REFLECTUR = 130, REFLECTDL = 76, REFLECTUL = 78
		};
		enum AlienMOVE {
			MOVESTAY, MOVEVERTICAL, MOVEVERTICALREVERSE, MOVEHORIZONTAL, MOVEHORIZONTALREVERSE, MOVEROTATION, MOVEROTATIONREVERSE
		};
		struct SReuslt {
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
		void LoadPlanet(ifstream &ifs);
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