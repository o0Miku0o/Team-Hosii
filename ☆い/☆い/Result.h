#pragma once
#include "MyGame/MyApp.h"
#include "MyGame/My/EventMsg.h"
#include "Eff1.h"

namespace Result
{
	const char caTaskName[] = { "リザルトタスク" };
	const char caResName[] = { "リザルトリソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iResult;
		Image iHanko;
		Image iPaper;

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
		std::string sPercent;
		int iRandomTime;
		int iHanabiCount;
		int iHanabiTime;

		Rec rBack;
		Rec rResult;
		Rec rNumber;
		Rec rPercent;
		Rec rHanko;
		byte bNextStage;
		byte bMoveStarIdx;

		bool bPushHanko;
		//byte bScore;
		//EventMsg em;

		Rec rRestart;
		std::array<byte, 3> bScore;
		byte bScoreIdx;
		std::shared_ptr<Eff1::EffectCreater> sp_ef;
		byte bStageGroupNumber;

		void ButtonInit();
		//void ButtonResize();
		void DrawButton(RS * const rpRes, const Frec * const fpSrc);

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void SetParam(const byte abStageGroupNumber, const std::array<byte, 3> &abScores);
	}*OBJ_ptr;
}