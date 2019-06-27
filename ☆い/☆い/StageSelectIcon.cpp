#include "StageSelectIcon.h"
#include "StageManager.h"
#include "Cursor.h"
#include "StageLoad.h"

namespace StageSelectIcon
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
		type = ET;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto pad = JoyPad::GetState(0);
		auto kb = KB::GetState();

		IconAnimation[type](&i, &iAddOffSet, &iOffSetX, &iOffSetY);

		if (auto cr = Find<Cursor::Obj>(Cursor::caTaskName))
		{
			Circle cHit;
			cHit.SetPos(&rIcon.GetPos());
			cHit.SetRadius(rIcon.GetW() / 2);
			if (cHit.CheckHit(&cr->rCursorBase.GetPos()))
			{
				rIcon.Scaling(16.f * 15.f, 16.f * 15.f);
				if (kb->Down(VK_RETURN) || pad->Down(J_BUT_6))
				{
					RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
					if (auto manager = Find<StageManager::Obj>(StageManager::caTaskName))
					{
						manager->bStageNum = (type * 3) + 1;

						Add<StageLoad::Obj>();
						Pause(2);

					}
				}
			}
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * (iOffSetX + iAddOffSet), iOffSetY * 16.f, 16.f, 16.f);
			rIcon.Draw(&res->iStageImg, &src, true);
		}
	}
	void AnimEarth(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 37;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimMeteo(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 41;
		*iOffSetY = 1;
		if (*iAnimCount >= 13)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimGalaxy(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 45;
		*iOffSetY = 1;
		if (*iAnimCount >= 15)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 2) % 8;
		}
		++*iAnimCount;
	}
	void AnimUranus(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 33;
		*iOffSetY = 1;
		if (*iAnimCount >= 15)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimBlackHole(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 53;
		*iOffSetY = 1;
		if (*iAnimCount >= 15)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 2) % 8;
		}
		++*iAnimCount;
	}
	void AnimTimeAttack(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 0;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimFragment(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 4;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
}
