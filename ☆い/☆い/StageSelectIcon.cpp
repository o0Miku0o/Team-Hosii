#include "StageSelectIcon.h"
#include "StageManager.h"
#include "Cursor.h"
#include "StageLoad.h"
#include "Hukidasi.h"

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
		rIcon.Scaling(16.f * 10.f, 16.f * 10.f);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);

		IconAnimation[type](&i, &iAddOffSet, &iOffSetX, &iOffSetY);

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * (iOffSetX + iAddOffSet), iOffSetY * 16.f, 16.f, 16.f);
			rIcon.Draw(&res->iStageImg, &src);
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
		*iOffSetX = 85;
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
		*iOffSetX = 89;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
}
