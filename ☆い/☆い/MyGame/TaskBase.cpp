#include "TaskBase.h"

#ifdef _DEBUG
#include "..\StageManager.h"
#endif // _DEBUG

//スタティック変数の初期化
ResourceBase *ResourceBase::top = nullptr;

//ResourceBase::

//
//void ResourceBase::

//スタティック変数の初期化
TaskBase *TaskBase::top = nullptr;

//TaskBase::TaskBase()

//void TaskBase::SysFinalize()

//bool TaskBase::SysUpdate()

void TaskBase::SysRender()
{
	if (top)
	{
		std::multimap<float, TaskBase *> mDrawMap;
		for (TaskBase *it = top; it != nullptr; it = it->next)
		{
			mDrawMap.insert(std::make_pair(it->GetRenderPriority(), it));
		}
		for (auto mIt : mDrawMap)
		{
			if (mIt.second->tstate == ACTIVE) mIt.second->Render();
		}
		//for (TaskBase *it = top; it != nullptr; it = it->next)
		//{
		//	if (it->tstate == ACTIVE)
		//		it->Render();
		//}

#ifdef _DEBUG
			if (auto sm = Find<StageManager::Obj>("ステージ統括タスク"))
			{
				if (sm->bIsDebug) {
					int pos = 0;
					for (TaskBase *it = top; it != nullptr; it = it->next)
					{
						Font f;
						f.FontCreate("メイリオ");
						f.Draw(&Point(pos / 50 * 180.f, pos % 50 * 20.f), it->tname.c_str());
						++pos;
					}
				}
			}
#endif //_DEBUG
	}
}

//void TaskBase::Remove(TaskBase *endtask_)

//void TaskBase::RemoveAll(const char *taskname_, RemoveFlag rflag_)

//void TaskBase::RemoveAll(const std::initializer_list<std::string> &iInitList, RemoveFlag rflag_)

//void TaskBase::SetName(const char *taskname_)

//void TaskBase::Pause(const std::initializer_list<std::string> &iInitList, const u_int waitframe_, PauseFlag pflag_)

//void TaskBase::Pause(const char *taskname_, const u_int waitframe_, PauseFlag pflag_)

//void TaskBase::Pause(const u_int waitframe_)

//void TaskBase::Pause(const char *taskname_, PauseFlag pflag_)

//void TaskBase::Pause()

//void TaskBase::Restart(const char *taskname_)

//void TaskBase::Restart()

//void TaskBase::SetRenderPriority(const float afPriority)

//const float TaskBase::GetRenderPriority() const