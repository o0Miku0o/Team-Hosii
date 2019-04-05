#include "TaskBase.h"

//スタティック変数の初期化
ResourceBase *ResourceBase::top = nullptr;

ResourceBase::ResourceBase()
{
	next = nullptr;
	prev = nullptr;
}

//
void ResourceBase::Remove(const char *resourcename_)
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

//スタティック変数の初期化
TaskBase *TaskBase::top = nullptr;

TaskBase::TaskBase()
{
	this->next = nullptr;
	this->prev = nullptr;
	this->wait = 0;
	this->updflag = true;
	this->tstate = ACTIVE;
}

void TaskBase::SysFinalize()
{
	RB::Remove();
	if (top)
	{
		TaskBase *buf = nullptr;
		for (TaskBase *it = top; it != nullptr; it = buf)
		{
			buf = it->next;

			it->Finalize();

			delete it;
		}
	}
}

bool TaskBase::SysUpdate()
{
	if (top)
	{
		for (TB_ptr it = top; it != nullptr;)
		{
			if (it->next)it->next->prev = it;

			if (it->tstate == ACTIVE)
			{
				if (it->updflag)
				{
					it->Update();
				}
				else if(it->wait > 0)
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
				TB_ptr next = it->next;
				TB_ptr prev = it->prev;

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

void TaskBase::SysRender()
{
	if (top)
	{
		for (TB_ptr it = top; it != nullptr; it = it->next)
		{
			if (it->tstate == ACTIVE)
				it->Render();
		}

#ifdef _DEBUG
		int pos = 0;
		for (TB_ptr it = top; it != nullptr; it = it->next)
		{
			Font f;
			f.FontCreate("メイリオ");
			f.Draw(&Point(pos / 50 * 180.f, pos % 50 * 20.f), it->tname.c_str());
			++pos;
		}
#endif //_DEBUG
	}
}

void TaskBase::Remove(TaskBase *endtask_)
{
	if (endtask_) endtask_->tstate = END;
}

void TaskBase::RemoveAll(const char *taskname_, RemoveFlag rflag_)
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

void TaskBase::SetName(const char *taskname_)
{
	this->tname = taskname_;
}

void TaskBase::Pause(const char *taskname_, const u_int waitframe_)
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

void TaskBase::Pause(const u_int waitframe_)
{
	for (TaskBase *now = top; now != nullptr; now = now->next)
	{
		now->updflag = false;
		now->wait = waitframe_;
	}
}

void TaskBase::Pause(const char *taskname_)
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

void TaskBase::Pause()
{
	for (TaskBase *now = top; now != nullptr; now = now->next)
	{
		now->updflag = false;
		now->wait = -1;
	}
}

void TaskBase::Restart(const char *taskname_)
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

void TaskBase::Restart()
{
	for (TaskBase *now = top; now != nullptr; now = now->next)
	{
		now->updflag = true;
		now->wait = 0;
	}
}