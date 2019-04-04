#include "BlackHole.h"
#include "Game.h"
#include "Beam.h"
#include "StageManager.h"
#include "BeamGenerator.h"

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

#ifdef _DEBUG
		auto kb = KB::GetState();
		if (kb->Now('V') == 1) {
			auto beamGen = Add<BeamGenerator::Obj>();
		}
#endif
		if (auto beam = Find<Beam::Obj>("ビームタスク")) {
			CheckHit(beam);
		}
		pPos = rBlackHole.GetPos();
		cInnerCircle.SetPos(&pPos);
	}
	/*タスクごとの描画処理*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>("ステージ統括リソース")) {
			rBlackHole.Draw(&stageRes->iStageImg, &Frec(192, 0, 16, 16), true);
		}
		cInnerCircle.Draw();
		Circle cOut;
		cOut.SetRadius(cInnerCircle.GetRadius()*2.00f);
		cOut.SetPos(&cInnerCircle.GetPos());
		cOut.Draw();

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

	void Obj::CheckHit(TaskBase* bm) {
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBm, cOut;
		cBm.SetRadius(oBeam->rHitBase.GetW()*0.5f);
		cBm.SetPos(&oBeam->rHitBase.GetPos());
		cOut.SetRadius(cInnerCircle.GetRadius()*2.0f);
		cOut.SetPos(&cInnerCircle.GetPos());
		if (cOut.CheckHit(&cBm)) {
			if (cInnerCircle.CheckHit(&cBm)) {
				Remove(bm);
			}
			else {
				float angle = oBeam->rHitBase.GetDeg();
				while (angle > 360) {
					angle -= 360;
				}
				float x, y, cx, cy;
				x = oBeam->rHitBase.GetPosX();
				y = oBeam->rHitBase.GetPosY();
				cx = cOut.GetPos().x;
				cy = cOut.GetPos().y;
				if (x < cx) {
					if (y < cy)
						angle = angle > 100 && angle < 260 ? angle -= 2 : angle += 2;
					else if (y > cy)
						angle = angle > 100 && angle < 260 ? angle += 2 : angle -= 2;
					else {

					}
				}
				else if (x > cx) {
					if (y < cy)
						angle = angle > 100 && angle < 260 ? angle -= 2 : angle += 2;
					else if (y > cy)
						angle = angle > 100 && angle < 260 ? angle += 2 : angle -= 2;
					else {

					}
				}
				oBeam->rHitBase.SetDeg(angle);
			}
		}
	}
}