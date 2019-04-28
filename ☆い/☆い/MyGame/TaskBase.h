#pragma once
#include "My/My.h"

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

//継承もとになるリソースクラス
typedef class ResourceBase
{
public:
	//
	ResourceBase();
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
	static void Remove(const char *resourcename_ = nullptr);
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

	TaskBase();
	virtual ~TaskBase() {};
private:
	static TaskBase *top;
	
	std::string tname;
	TaskBase *next;
	TaskBase *prev;
	int tstate;
	bool updflag;
	long wait;

	virtual void Init() = 0;

	virtual void Finalize() = 0;
public:

	virtual void Update() = 0;

	virtual void Render() = 0;

	template<class InitTask>
	static void SysInit()
	{
		top = new InitTask;

		top->Init();
	}

	static void SysFinalize();

	static bool SysUpdate();

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

	static void Remove(TaskBase *endtask_);

	static void RemoveAll(const char *taskname_ = nullptr, RemoveFlag rflag_ = REMOVE_NAME);

	void SetName(const char *taskname_);

	static void Pause(const char *taskname_, const u_int waitframe_);

	static void Pause(const u_int waitframe_);

	static void Pause(const char *taskname_);

	static void Pause();

	static void Restart(const char *taskname_);

	static void Restart();
}TB;

typedef TB *TB_ptr;