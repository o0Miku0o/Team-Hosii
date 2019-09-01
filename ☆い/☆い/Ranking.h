#pragma once
#include "MyGame/MyApp.h"
#include "../☆い/MyGame/My/EventMsg.h"

namespace Ranking
{
	const char caTaskName[] = { "ランキングタスク" };
	const char caResName[] = { "ランキングリソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iButton;

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
		Rec rButton;
		float width;
		float height;
		Point pos;
		std::string str;
		EventMsg titleMsg;
		std::string sName[5];
		float rwidth;
		float rheight;
		EventMsg rankMsg;
		Point rankpos;
		std::multimap<int, std::string> mRankmap;
		std::multimap<int, std::string>::iterator newData;
		int iNewindex;
		EventMsg newMsg;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void BeamCheckhit(TaskBase* bm);
		void FragmentCheckhit(TaskBase* fr);
	}*OBJ_ptr;
}