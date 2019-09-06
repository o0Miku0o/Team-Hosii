#include "TimeAttack.h"
#include "FadeInOut.h"
#include <fstream>

//タイムアタックで使うタスクです
//カウントやらなんやらをします
namespace TimeAttack
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

		/*データの初期化*/
		SetRenderPriority(1.f);
		iTimeCnt = 0;
		iFrameCnt = 0;
		width = 50.f * 1.2f;
		height = 100.f * 1.2f;
		pos = Point(Rec::Win.r * 0.8f + width, Rec::Win.t + height - 30);
		str = "00:00";
		timeMsg.SetMsg(str);
		timeMsg.Color(RGB(255, 150, 150));
		bIsSaved = false;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		SaveTime();
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto kb = KB::GetState();
		if (auto fi = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
		{
			if (fi->IsComplete() == false)
			{
				return;
			}
		}

		if (iFrameCnt >= 60 || kb->On('A'))
		{
			iFrameCnt = 0;
			iTimeCnt++;
			std::string mn = (iTimeCnt / 60) < 10 ? "0" + std::to_string(iTimeCnt / 60) : std::to_string(iTimeCnt / 60);
			std::string sc = (iTimeCnt % 60) < 10 ? "0" + std::to_string(iTimeCnt % 60) : std::to_string(iTimeCnt % 60);
			str = mn + ":" + sc;
			timeMsg.SetMsg(str);
		}
		iFrameCnt++;
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		timeMsg.DrawAscii(pos, width, height);
	}
	void Obj::SaveTime()
	{
		if (bIsSaved)return;
		std::ofstream off("./data/ta_data/ta.txt", std::ios_base::app);
		if (!off)return;
		off << iTimeCnt << "\n";
		off.close();
		bIsSaved = true;
	}
}