#include "Ranking.h"
#include "TimeAttack.h"
#include "Cursor.h"
#include <fstream>
#include <sstream>

namespace Ranking
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iButton.ImageCreate("./data/image/other/ResultResource2.bmp");
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
		RB::Add<Ranking::RS>(caResName);

		/*タスクの生成*/
		auto cs = Add<Cursor::Obj>();
		cs->rCursorBase.SetPos(&Point(1450.f, 1020.f));

		/*データの初期化*/
		SetRenderPriority(0.7f);
		str = "Ranking";
		titleMsg.SetMsg(str);
		titleMsg.Color(RGB(255, 235, 88));
		newMsg.Open("./data/ta_data/newrank.txt");
		newMsg.Color(RGB(255, 235, 88));
		newMsg.Interval(10);
		width = 150.f;
		height = 200.f;
		pos = Point(Rec::Win.r * 0.19f + width, Rec::Win.t + height - 10);
		iNewindex = 0;
		rwidth = 100.0f;
		rheight = 140.0f;
		rankMsg.Color(RGB(255, 255, 255));
		for (auto &it : sName)
		{
			it = "SNM";
		}
		std::ifstream ifs("./data/ta_data/ta.txt");
		if (!ifs)return;
		std::stringstream ss;
		ss << ifs.rdbuf();
		ifs.close();
		std::string alldata(ss.str());
		alldata.erase(alldata.end() - 1);
		std::string::size_type find = 0;
		while ((find = alldata.find(',')) != std::string::npos)
		{
			alldata.at(find) = ' ';
		}
		ss.str("");
		ss.clear();
		ss << alldata;
		int i = 0;
		for (; !ss.eof(); ++i)
		{
			int iTimeCnt = 0;
			ss >> iTimeCnt;
			std::string mn = (iTimeCnt / 60) < 10 ? "0" + std::to_string(iTimeCnt / 60) : std::to_string(iTimeCnt / 60);
			std::string sc = (iTimeCnt % 60) < 10 ? "0" + std::to_string(iTimeCnt % 60) : std::to_string(iTimeCnt % 60);
			std::string data = mn + ":" + sc;
			std::pair<int, std::string> addpair(iTimeCnt, data);
			newData = mRankmap.insert(addpair);
		}
		iNewindex = i - 1;
		rButton = Rec(1690.f, 980.f, 16.f * 15.f, 16.f * 13.f);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (newMsg.Length() >= 6) newMsg.Clear();
		newMsg.Run();
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto s = RB::Find<Ranking::RS>(Ranking::caResName))
		{
			rButton.Draw(&s->iButton, &Frec(0.f, 0.f, 16.f, 16.f));
		}

		titleMsg.DrawAscii(pos, width, height);

		auto pair = mRankmap.begin();
		for (int i = 0; i < 5; ++i)
		{
			std::string data = "--:--";
			if (pair != mRankmap.end())
			{
				if (newData == pair)
				{
					newMsg.DrawAscii(Point(Rec::Win.r * 0.7f, rheight * (i + 1) + 240), rwidth, rheight);
				}
				data = (pair++)->second;
			}

			std::string s = std::to_string(i + 1) + " "  + data;
			rankpos = Point(Rec::Win.r * 0.24f + rwidth, rheight * (i + 1) + 240);
			rankMsg.SetMsg(s);
			rankMsg.DrawAscii(rankpos, rwidth, rheight);
		}
	}
}
