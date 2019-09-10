#include "Alien.h"
#include "Beam.h"
#include "Fragment.h"
#include "StageManager.h"
#include "StageSelect.h"

namespace Alien
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
		rAlienR = Rec(1400, 200, 16 * 7, 16 * 7);
		cAlienRHitBase = Circle(&rAlienR.GetPos(), rAlienR.GetW() * 0.4f);
		iTime = 0;
		iAnimCount = 0;
		iOffSetX = 0;
		iOffSetY = 0;
		iAddOffSet = 0;
		fAddAngle = 0.f;
		moveFunc = MoveRotation;
		BMHitFunc = BMReflectDR;
		FGHitFunc = FGReflectDR;
		AnimFunc = AnimRotation;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (Find<Beam::Obj>(Beam::caTaskName))
		{
			for (auto &bm : FindAll<Beam::Obj>(Beam::caTaskName))
			{
				BeamCheckhit(bm);
			}
		}
		//auto vFgm = FindAll <Fragment::Obj>("欠片タスク");
		//if (vFgm.size())
		//{
		//	for (auto &vf : vFgm)
		//	{
		//		FragmentCheckhit(vf);
		//	}
		//}
		Point pPos;
		/*移動関係の関数を実行*/
		if (moveFunc)
		{
			moveFunc(&pPos, &pCenter, &iTime, &fAddAngle);
		}
		rAlienR.SetPos(&pPos);

		rAlienR.SetDeg(rAlienR.GetDeg() + fAddAngle);
		cAlienRHitBase.SetPos(&rAlienR.GetPos());
		/*アニメーション関数を実行*/
		if (AnimFunc)
		{
			AnimFunc(&iAnimCount, &iAddOffSet, &iOffSetX, &iOffSetY);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * (iOffSetX + iAddOffSet), 16.f * iOffSetY, 16, 16);

			rAlienR.Draw(&res->iStageImg, &src);
#ifdef _DEBUG
			cAlienRHitBase.Draw();
#endif
		}
	}
	void Obj::BeamCheckhit(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBmHit;
		cBmHit.SetRadius(oBeam->rHitBase.GetH()*0.5f);
		cBmHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cAlienRHitBase.CheckHit(&cBmHit))
		{
			if (BMHitFunc) BMHitFunc(bm);

			if (Find<StageSelect::Obj>(StageSelect::caTaskName))
			{
				Remove(this);
			}
		}
	}
	//void Obj::FragmentCheckhit(TaskBase* fr)
	//{
	//	Fragment::Obj* oFragment = (Fragment::Obj*)fr;
	//	Circle cFrHit;
	//	cFrHit.SetRadius(oFragment->rFragment.GetW()*0.5f);
	//	cFrHit.SetPos(&oFragment->rFragment.GetPos());
	//	if (cAlienRHitBase.CheckHit(&cFrHit))
	//	{
	//		if(FGHitFunc) FGHitFunc(fr);
	//		//Remove(fr);

	//		//oFragment->rFragment.SetPos(&oFragment->pInitPos);
	//		//oFragment->bMoveActive = false;
	//	}
	//}
	void MoveHorizontal(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle)
	{
		float fPos;
		fPos = (cos(DtoR((float)*iCount)) * 300.f + pCenter->x);
		*pPos = Point(fPos, pCenter->y);

		*iCount = (*iCount + 2) % 360;

		*fAddAngle = 0.f;
	}
	void Move_Horizontal(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle)
	{
		float fPos;
		fPos = (sin(DtoR((float)*iCount)) * 300.f + pCenter->x);
		*pPos = Point(fPos, pCenter->y);

		*iCount = (*iCount + 2) % 360;

		*fAddAngle = 0.f;
	}
	void MoveVertical(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle)
	{
		float fPos;
		fPos = (cos(DtoR((float)*iCount)) * 300.f + pCenter->y);
		*pPos = Point(pCenter->x, fPos);

		*iCount = (*iCount + 2) % 360;

		*fAddAngle = 0.f;
	}
	void Move_Vertical(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle)
	{
		float fPos;
		fPos = (sin(DtoR((float)*iCount)) * 300.f + pCenter->y);
		*pPos = Point(pCenter->x, fPos);

		*iCount = (*iCount + 2) % 360;

		*fAddAngle = 0.f;
	}
	void MoveRotation(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle)
	{
		float fPosX, fPosY;
		fPosX = (cos(DtoR((float)*iCount)) * 250.f + pCenter->x);
		fPosY = (sin(DtoR((float)*iCount)) * 300.f + pCenter->y);
		*pPos = Point(fPosX, fPosY);

		*iCount = (*iCount + 2) % 360;

		*fAddAngle = 7.5f;
	}
	void Move_Rotation(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle)
	{
		float fPosX, fPosY;
		fPosX = (cos(DtoR((float)*iCount)) * 300.f + pCenter->x);
		fPosY = (sin(DtoR((float)*iCount)) * 300.f + pCenter->y);
		*pPos = Point(fPosX, fPosY);

		*iCount = (*iCount - 2) % 360;

		*fAddAngle = 7.5f;
	}
	void MoveStay(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle)
	{
		*pPos = *pCenter;

		*fAddAngle = 0.f;
	}

	void BMRemove(TaskBase * const tTask)
	{
		auto bm = (Beam::Obj*)tTask;
		bm->Remove(bm);
	}
	void BMReflectDR(TaskBase * const tTask)
	{
		auto bm = (Beam::Obj*)tTask;
		bm->rHitBase.SetDeg(45.f);
	}
	void BMReflectUR(TaskBase * const tTask)
	{
		auto bm = (Beam::Obj*)tTask;
		bm->rHitBase.SetDeg(315.f);
	}
	void BMReflectDL(TaskBase * const tTask)
	{
		auto bm = (Beam::Obj*)tTask;
		bm->rHitBase.SetDeg(115.f);
	}
	void BMReflectUL(TaskBase * const tTask)
	{
		auto bm = (Beam::Obj*)tTask;
		bm->rHitBase.SetDeg(225.f);
	}

	void FGRemove(TaskBase * const tTask)
	{
		auto fgm = (Fragment::Obj*)tTask;
		fgm->rFragment.SetPos(&fgm->pInitPos);
		fgm->bMoveActive = false;
	}
	void FGReflectDR(TaskBase * const tTask)
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsTest7.Play();
		}
		auto fgm = (Fragment::Obj*)tTask;
		fgm->rFragment.SetDeg(45.f);
		fgm->bMoveActive = true;
	}
	void FGReflectUR(TaskBase * const tTask)
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsTest7.Play();
		}
		auto fgm = (Fragment::Obj*)tTask;
		fgm->rFragment.SetDeg(315.f);
		fgm->bMoveActive = true;
	}
	void FGReflectDL(TaskBase * const tTask)
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsTest7.Play();
		}
		auto fgm = (Fragment::Obj*)tTask;
		fgm->rFragment.SetDeg(135.f);
		fgm->bMoveActive = true;
	}
	void FGReflectUL(TaskBase * const tTask)
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsTest7.Play();
		}
		auto fgm = (Fragment::Obj*)tTask;
		fgm->rFragment.SetDeg(225.f);
		fgm->bMoveActive = true;
	}

	void AnimNormal(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 14;
		*iOffSetY = 0;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 2;
		}
		++*iAnimCount;
	}
	void AnimHorizontal(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 16;
		*iOffSetY = 0;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 2;
		}
		++*iAnimCount;
	}
	void AnimRotation(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 18;
		*iOffSetY = 0;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 2) % 4;
		}
		++*iAnimCount;
	}
	void AnimReflectDR(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 28;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 2;
		}
		++*iAnimCount;
	}
	void AnimReflectUR(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 30;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 2;
		}
		++*iAnimCount;
	}
	void AnimReflectUL(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 78;
		*iOffSetY = 0;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 2;
		}
		++*iAnimCount;
	}
	void AnimReflectDL(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 76;
		*iOffSetY = 0;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 2;
		}
		++*iAnimCount;
	}
}