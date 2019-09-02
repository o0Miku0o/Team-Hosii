#pragma once
#include "My/My.h"

//#ifdef _DEBUG
//#include "..\StageManager.h"
//#endif // _DEBUG

//タスクの状態
enum TaskState
{
	ACTIVE,
	END
};

enum RemoveFlag
{
	REMOVE_NAME,
	NOT_REMOVE_NAME
};

enum PauseFlag
{
	PAUSE_NAME,
	NOT_PAUSE_NAME,
};

//継承もとになるリソースクラス
typedef class ResourceBase
{
public:
	//
	ResourceBase()
	{
		next = nullptr;
		prev = nullptr;
	}
	virtual ~ResourceBase() {};
	//
	template<class AddResource>
	static AddResource *Add(const char *resourcename_)
	{
		if (top)
		{
			ResourceBase *t;
			for (t = top; t->next; t = t->next)
			{
				if (t->rname == resourcename_) return nullptr;
			}
			if (t->rname == resourcename_) return nullptr;
			t->next = new AddResource;
			t->next->rname = resourcename_;
			t->next->prev = t;
			return dynamic_cast<AddResource *>(t->next);
		}
		else
		{
			top = new AddResource;
			top->rname = resourcename_;
		}
		return dynamic_cast<AddResource *>(top);
	}
	//
	template<class SearchResource>
	static SearchResource *Find(const char *resourcename_)
	{
		ResourceBase *now = top;
		ResourceBase *pre = top;
		for (; now != nullptr; now = now->next)
		{
			pre = now;
			if (now->rname == resourcename_) break;
		}
		return dynamic_cast<SearchResource *>(now);
	}
	//
	static void Remove(const char *resourcename_ = nullptr)
	{
		if (top)
		{
			if (resourcename_)
			{
				for (ResourceBase *now = top; now != nullptr;)
				{
					ResourceBase *next = now->next;
					if (now->rname == resourcename_)
					{
						ResourceBase *prev = now->prev;

						if (now == top) top = nullptr;
						delete now;

						if (prev) prev->next = next;
						else top = next;
						now = next;
						if (now) now->prev = prev;
					}
					else now = next;
				}
			}
			else
			{
				ResourceBase *buf = nullptr;
				for (ResourceBase *it = top; it != nullptr; it = buf)
				{
					buf = it->next;
					delete it;
				}
				top = nullptr;
			}
		}
	}
private:
	//
	static ResourceBase *top;
	
	std::string rname;
	ResourceBase *next;
	ResourceBase *prev;
	
	virtual void Init() = 0;
	virtual void Finalize() = 0;
}RB;

typedef RB *RB_ptr;

//継承もとになるタスククラス
typedef class TaskBase
{
public:

	TaskBase()
	{
		this->next = nullptr;
		this->prev = nullptr;
		this->wait = 0;
		this->updflag = true;
		this->tstate = ACTIVE;
	}
	virtual ~TaskBase() {};

	static TaskBase *top;

	TaskBase *next;
	TaskBase *prev;
private:
	
	std::string tname;
	int tstate;
	bool updflag;
	long wait;
	float fpriority;

	virtual void Init() = 0;

	virtual void Finalize() = 0;
public:

	virtual void Update() = 0;

	virtual void Render() = 0;

	static void SysFinalize()
	{
		RB::Remove();
		if (top)
		{
			for (TaskBase *it = top; it != nullptr;)
			{
				TaskBase *next = it->next;
				TaskBase *prev = it->prev;

				it->Finalize();

				delete it;

				if (prev)prev->next = next;
				else top = next;
				it = next;
				if (it)it->prev = prev;
			}
		}
	}

	static bool SysUpdate()
	{
		if (top)
		{
			for (TaskBase *it = top; it != nullptr;)
			{
				if (it->next)it->next->prev = it;

				if (it->tstate == ACTIVE)
				{
					if (it->updflag)
					{
						it->Update();
					}
					else if (it->wait > 0)
					{
						--it->wait;
						if (it->wait == 0)
						{
							it->updflag = true;
						}
					}
					it = it->next;
				}
				else if (it->tstate == END)
				{
					TaskBase *next = it->next;
					TaskBase *prev = it->prev;

					it->Finalize();

					delete it;

					if (prev)prev->next = next;
					else top = next;
					it = next;
					if (it)it->prev = prev;
				}
			}
			return 0;
		}
		return 1;
	}

	static void SysRender();

	template<class SearchTask>
	static SearchTask *Find(const char *taskname_)
	{
		TaskBase *now = top;
		TaskBase *pre = top;
		for (; now != nullptr; now = now->next)
		{
			pre = now;
			if (now->tname == taskname_) break;
		}
		return dynamic_cast<SearchTask *>(now);
	}

	template<class SearchTask>
	static std::vector<SearchTask *> FindAll(const char *taskname_)
	{
		std::vector<SearchTask *> find;
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (now->tname == taskname_) find.push_back(dynamic_cast<SearchTask *>(now));
		}
		return find;
	}

	template<class AddTask>
	static AddTask *Add()
	{
		if (top)
		{
			TaskBase *it = top;
			while (it->next)
			{
				it = it->next;
			}
			it->next = new AddTask;

			if (!it->next) return nullptr;

			it->next->prev = it;

			it->next->Init();

			return dynamic_cast<AddTask *>(it->next);
		}
		else
		{
			top = new AddTask;

			top->Init();

			return dynamic_cast<AddTask *>(top);
		}
		//if (this->next)
		//{
		//	TaskBase *buf = this->next;
		//	this->next = new AddTask;
		//	this->next->next = buf;
		//}
		//else this->next = new AddTask;
	}

	template<class PrevTask>
	PrevTask *FindPrev(const char * const ccpPrevTaskName)
	{
		if (!prev) return nullptr;
		auto pIt = prev;
		while (pIt->prev)
		{
			if (pIt->tname == ccpPrevTaskName)
			{
				return dynamic_cast<PrevTask *>(pIt);
			}
			pIt = pIt->prev;
		}
		return nullptr;
	}

	template<class NextTask>
	NextTask *FindNext(const char * const ccpNextTaskName)
	{
		if (!next) return nullptr;
		auto pIt = next;
		while (pIt->next)
		{
			if (pIt->tname == ccpNextTaskName)
			{
				return dynamic_cast<NextTask *>(pIt);
			}
			pIt = pIt->next;
		}
		return nullptr;
	}

	static void Remove(TaskBase *endtask_)
	{
		if (endtask_) endtask_->tstate = END;
	}

	static void RemoveAll(const char *taskname_ = nullptr, RemoveFlag rflag_ = REMOVE_NAME)
	{
		if (rflag_ == REMOVE_NAME)
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				if (taskname_)
				{
					if (now->tname == taskname_)
						now->tstate = END;
				}
				else now->tstate = END;
			}
		}
		else
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				if (taskname_)
				{
					if (now->tname != taskname_)
						now->tstate = END;
				}
				else now->tstate = END;
			}
		}
	}

	static void RemoveAll(const std::initializer_list<std::string> &iInitList, RemoveFlag rflag_ = REMOVE_NAME)
	{
		if (rflag_ == REMOVE_NAME)
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				bool bEndTaskFlag = false;
				for (const auto &it : iInitList)
				{
					if (now->tname == it)
					{
						bEndTaskFlag = true;
						break;
					}
				}
				if (bEndTaskFlag)
				{
					now->tstate = END;
				}
			}
		}
		else
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				bool bEndTaskFlag = true;
				for (const auto &it : iInitList)
				{
					if (now->tname == it)
					{
						bEndTaskFlag = false;
						break;
					}
				}
				if (bEndTaskFlag)
				{
					now->tstate = END;
				}
			}
		}
	}

	void SetName(const char *taskname_)
	{
		this->tname = taskname_;
	}

	static void Pause(const std::initializer_list<std::string> &iInitList, const u_int waitframe_, PauseFlag pflag_ = PAUSE_NAME)
	{
		if (pflag_ == PauseFlag::PAUSE_NAME)
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				bool bFlag = false;
				for (const auto &it : iInitList)
				{
					if (now->tname == it)
					{
						bFlag = true;
						break;
					}
				}
				if (bFlag)
				{
					now->updflag = false;
					now->wait = waitframe_;
				}
			}
		}
		else
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				bool bFlag = true;
				for (const auto &it : iInitList)
				{
					if (now->tname == it)
					{
						bFlag = false;
						break;
					}
				}
				if (bFlag)
				{
					now->updflag = false;
					now->wait = waitframe_;
				}
			}
		}
	}

	static void Pause(const char *taskname_, const u_int waitframe_, PauseFlag pflag_ = PAUSE_NAME)
	{
		if (pflag_ == PauseFlag::PAUSE_NAME)
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				if (now->tname == taskname_)
				{
					now->updflag = false;
					now->wait = waitframe_;
				}
			}
		}
		else
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				if (now->tname != taskname_)
				{
					now->updflag = false;
					now->wait = waitframe_;
				}
			}
		}
	}

	static void Pause(const u_int waitframe_)
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			now->updflag = false;
			now->wait = waitframe_;
		}
	}

	static void Pause(const char *taskname_, PauseFlag pflag_ = PAUSE_NAME)
	{
		if (pflag_ == PauseFlag::PAUSE_NAME)
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				if (now->tname == taskname_)
				{
					now->updflag = false;
					now->wait = -1;
				}
			}
		}
		else
		{
			for (TaskBase *now = top; now != nullptr; now = now->next)
			{
				if (now->tname != taskname_)
				{
					now->updflag = false;
					now->wait = -1;
				}
			}
		}
	}

	static void Pause()
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			now->updflag = false;
			now->wait = -1;
		}
	}

	static void Restart(const char *taskname_)
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (now->tname == taskname_)
			{
				now->updflag = true;
				now->wait = 0;
			}
		}
	}

	static void Restart()
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			now->updflag = true;
			now->wait = 0;
		}
	}

	void SetRenderPriority(const float afPriority)
	{
		fpriority = Clamp(afPriority, 0.f, 1.f);
	}

	const float GetRenderPriority() const
	{
		return fpriority;
	}

	static void Swap(TaskBase *apObj1, TaskBase *apObj2)
	{
		if (!apObj1 || !apObj2) return;
		/*強制的に入れ替え*/
		auto smn = apObj1->next;
		auto smp = apObj1->prev;
		auto n = apObj2->next;
		auto p = apObj2->prev;

		if (p) p->next = apObj1;
		else TaskBase::top = apObj1;
		if (n) n->prev = apObj1;
		apObj1->next = n;
		apObj1->prev = p;

		if (smp) smp->next = apObj2;
		else TaskBase::top = apObj2;
		if (smn) smn->prev = apObj2;
		apObj2->next = smn;
		apObj2->prev = smp;
	}

	//Render順番を最後のところに移動
	//template<class EndPositonTask>
	//static EndPositonTask* EndPositon(const char *taskname_) {
	//	TaskBase *find, *pre = nullptr, *next = nullptr;
	//	if (find = Find<EndPositonTask>(taskname_)) {
	//		if (find->next != nullptr) {
	//			auto it = top;
	//			for (; it->next != nullptr; ++it);
	//			pre->next = find->next;
	//			next->prev = find->prev;
	//			next->next = find;
	//			find->prev = next;
	//			find->next = nullptr;
	//			
	//		}
	//	}
	//	return dynamic_cast<EndPositonTask*>(find);
	//}
}TB;

typedef TB *TB_ptr;