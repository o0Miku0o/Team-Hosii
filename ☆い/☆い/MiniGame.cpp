#include "MiniGame.h"
#include "Fragment.h"
#include "Star.h"
#include "Beam.h"
#include <fstream>

//ミニゲームで使うタスクです
//カウントやらなんやらをします
namespace MiniGame
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iButton.ImageCreate("./data/image/other/button.bmp");
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
		RB::Add<MiniGame::RS>(caResName);
		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(1.f);
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
		rButton = Rec(1820.f, 980.f, 16.f * 11.f, 16.f * 11.f);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		if (score < fFragmentCnt)
		{
			std::ofstream ofs;
			ofs.open("./data/log/log.txt", std::ios_base::trunc);
			if (ofs)
			{
				ofs << fFragmentCnt;
				ofs.close();
			}
		}
		myMsg.Close();
		highMsg.Close();
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto pd = JoyPad::GetState(0);
		if (pd->Down(JOY_BUTTON6))
		{
			if (score < fFragmentCnt)
			{
				std::ofstream ofs;
				ofs.open("./data/log/log.txt", std::ios_base::trunc);
				if (ofs)
				{
					ofs << fFragmentCnt;
					ofs.close();
				}
			}
			myMsg.Close();
			highMsg.Close();
			std::ifstream ifs("./data/log/log.txt");
			if (ifs)
			{
				ifs >> score;
				ifs.close();
			}
			{
				float prefFragCnt = fFragmentCnt;
				auto fr = FindAll<Fragment::Obj>(Fragment::caTaskName);
				for (auto vf : fr)
				{
					if (vf->bMoveActive)
					{
						fFragmentCnt = prefFragCnt;
					}
					else
					{
						fFragmentCnt = 0;
					}
				}
			}
		}
		myMsg.SetMsg(str[0] + std::to_string((int)fFragmentCnt));
		highMsg.SetMsg(str[1] + std::to_string(score));
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		myMsg.DrawAscii(pos1, width, height);
		highMsg.DrawAscii(pos2, width, height);
		if (auto s = RB::Find<MiniGame::RS>(MiniGame::caResName))
		{
			rButton.Draw(&s->iButton, &Frec(16.f * 13.f, 0.f, 16.f, 16.f), true);
		}
	}
}