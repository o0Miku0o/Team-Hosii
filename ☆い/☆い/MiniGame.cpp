#include "MiniGame.h"
#include "Fragment.h"
#include "Star.h"
#include "Back.h"
#include <fstream>

//ミニゲームで使うタスクです
//カウントやらなんやらをします
namespace MiniGame
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
		//Add<Back::Obj>();

		/*データの初期化*/
		std::ifstream ifs("./data/log/log.txt");
		score = 0;
		if (ifs)
		{
			ifs >> score;
			ifs.close();
		}
		str[0] = "Your Score:";
		str[1] = "High Score:";
		myMsg.SetMsg(str[0]);
		myMsg.Color(RGB(255, 255, 255));
		highMsg.Color(RGB(255, 255, 255));
		width = 50.f;
		height = 100.f;
		pos1 = Point(Rec::Win.r*0.1f + width, Rec::Win.t + height - 30);
		pos2 = Point(pos1.x + width * str[0].length() + width * 6, Rec::Win.t + height - 30);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		if (score < iFragmentCnt)
		{
			std::ofstream ofs;
			ofs.open("./data/log/log.txt",std::ios_base::trunc);
			if (ofs)
			{
				ofs << iFragmentCnt;
				ofs.close();
			}
		}
		myMsg.Close();
		highMsg.Close();
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto kb = KB::GetState();
		if (kb->Down('A'))
		{
			iFragmentCnt++;
		}
		myMsg.SetMsg(str[0] + std::to_string(iFragmentCnt));
		highMsg.SetMsg(str[1] + std::to_string(score));
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		myMsg.DrawAscii(pos1, width, height);
		highMsg.DrawAscii(pos2, width, height);
	}
}
