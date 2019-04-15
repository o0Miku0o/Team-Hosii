#include "BlackHole.h"
#include "Game.h"
#include "Beam.h"
#include "StageManager.h"
#include "BeamGenerator.h"
#include "Fragment.h"

namespace BlackHole
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
		SetName("ブラックホールタスク");

		/*リソース生成*/

		bCreate = false;
		bBigger = false;
		bMove = false;
		fAngle = 0;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		/*リソースの消去*/
	}
	/*タスクごとの更新処理*/
	void Obj::Update()
	{
		if (!bCreate) {
			bCreate = IsCreate();
		}
		if (bBigger) {
			bBigger = IsBigger();
		}
		if (bMove) {
			bMove = IsMove();
		}

		if (auto beam = Find<Beam::Obj>("ビームタスク")) {
			CheckHitBeam(beam);
		}

		auto frag = FindAll<Fragment::Obj>("欠片タスク");
		for (const auto fg : frag) {
			CheckHitFragment(fg);

		}
		pPos = rBlackHole.GetPos();
		cInnerCircle.SetPos(&pPos);
		cOutCircle.SetPos(&pPos);
		cOutCircle.SetRadius(cInnerCircle.GetRadius()*2.00f);
		++fAngle;
		rBlackHole.SetDeg(fAngle);

	}
	/*タスクごとの描画処理*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>("ステージ統括リソース")) {
			rBlackHole.Draw(&stageRes->iStageImg, &Frec(192, 0, 16, 16), true);
		}
#ifdef _DEBUG
		cInnerCircle.Draw();
		cOutCircle.Draw();
#endif // DEBUG
	}
	bool Obj::IsCreate() {
		rBlackHole.SetPos(&pPos);
		cInnerCircle.SetPos(&pPos);
		cInnerCircle.SetRadius(rBlackHole.GetW()*0.5f);
		return true;
	}
	bool Obj::IsBigger() {
		float radius, radiusMax = 256.f;
		radius = rBlackHole.GetW();
		radius = ++radius <= radiusMax ? radius : radiusMax;
		rBlackHole = Rec(pPos.x, pPos.y, radius, radius);
		cInnerCircle.SetRadius(rBlackHole.GetW()*0.5f);
		return radius >= radiusMax ? false : true;
	}

	bool Obj::IsMove() {
		float fLenX = abs(rBlackHole.GetPos().x - pEndPos.x);
		float fLenY = abs(rBlackHole.GetPos().y - pEndPos.y);
		float fTime = sqrt(fLenX * fLenX + fLenY * fLenY);
		fLenX = pEndPos.x < rBlackHole.GetPos().x ? fLenX * -1 : fLenX;
		fLenY = pEndPos.y < rBlackHole.GetPos().y ? fLenY * -1 : fLenY;
		float fMoveX = 0, fMoveY = 0;
		if (fLenX > 1) {
			fMoveX = fLenX / fTime;
			fLenX -= fMoveX;
		}
		else if (fLenX < -1) {
			fMoveX = fLenX / fTime;
			fLenX += fMoveX;
		}
		else {
			fMoveX = fLenX;
			fLenX = 0;
		}
		if (fLenY > 1) {
			fMoveY = fLenY / fTime;
			fLenY -= fMoveY;
		}
		else if (fLenY < -1) {
			fMoveY = fLenY / fTime;
			fLenY += fMoveY;
		}
		else {
			fMoveY = fLenY;
			fLenY = 0;
		}
		rBlackHole.Move(&Vector2(fMoveX, fMoveY));
		return fLenX == 0 && fLenY == 0 ? false : true;
	}

	void Obj::CheckHitBeam(TaskBase* bm) {
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBm;
		cBm.SetRadius(oBeam->rHitBase.GetW()*0.5f);
		cBm.SetPos(&oBeam->rHitBase.GetPos());
		if (cOutCircle.CheckHit(&cBm)) {
			if (cInnerCircle.CheckHit(&cBm)) {
				Remove(bm);
			}
			else {
				while (oBeam->rHitBase.GetDeg() > 360) {
					float angle = oBeam->rHitBase.GetDeg();
					oBeam->rHitBase.SetDeg(angle -= 360);
				}
				oBeam->rHitBase.SetDeg(CalcAngle(oBeam->rHitBase.GetPos(), cOutCircle.GetPos(), oBeam->rHitBase.GetDeg()));
			}
		}
	}
	void Obj::CheckHitFragment(TaskBase* fg) {
		Fragment::Obj* oFrag = (Fragment::Obj*)fg;
		Circle cFg;
		cFg.SetRadius(oFrag->rFragment.GetW()*0.5f);
		cFg.SetPos(&oFrag->rFragment.GetPos());
		if (oFrag->bMoveActive) {
			if (cOutCircle.CheckHit(&cFg)) {
				if (cInnerCircle.CheckHit(&cFg)) {
					oFrag->rFragment.SetPos(&oFrag->pInitPos);
					oFrag->bMoveActive = false;
				}
				else {
					while (oFrag->rFragment.GetDeg() > 360) {
						float angle = oFrag->rFragment.GetDeg();
						oFrag->rFragment.SetDeg(angle -= 360);
					}
					oFrag->rFragment.SetDeg(CalcAngle(oFrag->rFragment.GetPos(), cOutCircle.GetPos(), oFrag->rFragment.GetDeg()));
				}
			}
		}
	}
	float Obj::CalcAngle(const Point targetPos, const Point bhPos, const float targetAngle) {
		float rtAngle = targetAngle;
		if (targetPos.x < bhPos.x) {
			if (targetPos.y < bhPos.y)
				targetAngle > 100 && targetAngle < 240 ? rtAngle -= 1 : rtAngle += 1;
			else if (targetPos.y > bhPos.y)
				targetAngle > 100 && targetAngle < 240 ? rtAngle += 1 : rtAngle -= 1;
		}
		else if (targetPos.x > bhPos.x) {
			if (targetPos.y < bhPos.y)
				targetAngle > 100 && targetAngle < 330 ? rtAngle -= 1 : rtAngle += 1;
			else if (targetPos.y > bhPos.y)
				targetAngle > 100 && targetAngle < 240 ? rtAngle += 1 : rtAngle -= 1;
		}
		return rtAngle;
	}
}