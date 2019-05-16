#include "StageManager.h"
#include "Fragment.h"
#include "Star.h"
#include "Beam.h"
#include "Title.h"
#include "Player.h"
#include "Alien.h"
#include "Effect.h"

namespace Fragment
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
		SetName("欠片タスク");
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/
		rFragment = Rec(Rec::Win.r*0.5f, Rec::Win.b*0.5f, 100.f, 100.f);
		cFragmentHitBase = Circle(&rFragment.GetPos(), rFragment.GetW()*0.4f);
		pInitPos = Point();
		pRotPos = Point();
		fRotRadius = 0.f;
		iColor = 0;/*黄色が0、赤が1、青が2*/
		bMoveActive = false;
		bRotationActive = false;
		bPreRotationActive = false;
		aAnim.SetAnim(AnimFragmentY, 0);
		aAnim.SetAnim(AnimFragmentR, 0);
		aAnim.SetAnim(AnimFragmentB, 0);
		aAnim.Play();
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		pPrevPos = rFragment.GetPos();
		const auto kb = KB::GetState();
		/*if (kb->Now('T') == 1)
		{
			RemoveAll();
			Add<Title::Obj>();
		}*/
		if (auto beam = Find<Beam::Obj>("ビームタスク"))
		{
			//test追加記入
			//bPreRotationActive = bRotationActive;

			Checkhitbeam(beam);
		}
		auto frg = FindAll<Fragment::Obj>("欠片タスク");
		for (const auto fr : frg)
		{
			if (fr != this)
			{
				//test追加記入
				bPreRotationActive = bRotationActive;

				Checkhitfagment(fr);
			}
		}
		/*移動処理*/
		if (bMoveActive)
		{
			vMove.SetVec(rFragment.GetDeg(), 15.f);
			rFragment.Move(&vMove);
		}

		//auto star = FindAll<Star::Obj>("星タスク");
		//for (const auto st : star)
		//{
		//	st->CheckHit(&cFragmentHitBase);
		//}
		//if (kb->Now('S'))/*回転のON,OFF*/
		//{
		//	bRotationActive = true;
		//}
		/*回転処理*/
		if (bRotationActive)
		{
			Point pRotPos(cos(DtoR((float)iRotation)) * fRotRadius + pRotPos.x, sin(DtoR((float)iRotation)) * fRotRadius + pRotPos.y);
			iRotation = (iRotation + 1) % 360;
			rFragment.SetPos(&pRotPos);
		}
		cFragmentHitBase.SetPos(&rFragment.GetPos());
		if (rFragment.GetPosY() < Rec::Win.t - rFragment.GetH())
		{
			rFragment.SetPos(&pInitPos);
			bMoveActive = false;
			//Add<Fragment::Obj>();
			//Remove(this);
		}
		if (rFragment.GetPosY() > Rec::Win.b + rFragment.GetH())
		{
			rFragment.SetPos(&pInitPos);
			bMoveActive = false;
			//Add<Fragment::Obj>();
			//Remove(this);
		}
		if (rFragment.GetPosX() > Rec::Win.r + rFragment.GetW())
		{

			rFragment.SetPos(&pInitPos);
			bMoveActive = false;
			//Add<Fragment::Obj>();	
			//Remove(this);
		}
		if (rFragment.GetPosX() < Rec::Win.l - rFragment.GetW())
		{
			rFragment.SetPos(&pInitPos);

			//仮
			rFragment.SetDeg(0.f);
			bMoveActive = false;
		}
		auto vAli = FindAll<Alien::Obj>("宇宙人タスク");
		if (vAli.size())
		{
			for (auto&va : vAli)
			{
				CheckhitAlien(va);
			}
		}

		if (!bMoveActive) return;

		/*エフェクト放出*/
		for (byte b = 0; b < 4; ++b)
		{
			auto ef1 = Add<Eff1::Obj>();
			const fix fAng = ModAngle(rFragment.GetDeg() + 180.f + (rand() % 41 - 20));
			const fix fRad = DtoR(fAng);
			const fix fSpdX = cos_fast((float)fRad) * 2.f;
			const fix fSpdY = sin_fast((float)fRad) * 2.f;
			Rec rEf(rFragment.GetPosX() + cos_fast(DtoR(ModAngle(fAng + (b * 180.f - 90.f)))) * (rand() % 16 - 4.f), rFragment.GetPosY() + sin_fast(DtoR(ModAngle(fAng + (b * 180.f - 90.f)))) * (rand() % 16 - 4.f), 3.f, 3.f, fAng);
			Eff1::Type tEffectType = Eff1::Type::TYPE_R_FRG;
			if (iColor == 0)
			{
				tEffectType = Eff1::Type::TYPE_Y_FRG;
			}
			else if (iColor == 1)
			{
				tEffectType = Eff1::Type::TYPE_R_FRG;
			}
			else if (iColor == 2)
			{
				tEffectType = Eff1::Type::TYPE_B_FRG;
			}
			ef1->SetParam(&rEf, &Vector2(fSpdX, fSpdY), 20, tEffectType, fAng);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			if (iColor == 0)
			{
				Frec src(16.f * (aAnim.GetSrcX() + 2), 0.f, 16.f, 16.f);
				rFragment.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iColor == 1)
			{

				Frec src(16.f * (aAnim.GetSrcX() + 60), 0.f, 16.f, 16.f);
				rFragment.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iColor == 2)
			{

				Frec src(16.f * (aAnim.GetSrcX() + 68), 0.f, 16.f, 16.f);
				rFragment.Draw(&stageRes->iStageImg, &src, true);
			}
		}
		//cFragmentHitBase.Draw();
	}

	void Obj::Checkhitbeam(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cHit;
		cHit.SetRadius(oBeam->rHitBase.GetH() * 0.4f);
		cHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cFragmentHitBase.CheckHit(&cHit))
		{
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				res->wsTest.Play();
				//res->wsTest1.Pause();
			}
			rFragment.SetDeg(oBeam->rHitBase.GetDeg(&rFragment));
			oBeam->rHitBase.SetDeg(rFragment.GetDeg(&oBeam->rHitBase));
			if (auto pl = Find<Player::Obj>("プレイヤータスク"))
			{
				if (pl->lGuideLineFgm.GetLen())
				{
					rFragment.SetDeg(pl->lGuideLineFgm.GetDeg());
					oBeam->rHitBase.SetDeg(pl->lGuideLineFgm.GetDeg() + 180.f);
				}
			}
			//呼び出し前から呼び出し後に移動
			bPreRotationActive = bRotationActive;
			bRotationActive = false;
			Pause(30);
			/**/

			/*/
			RemoveAll("ビームタスク");//ビームタスクを消す（仮処理）
			/**/
			bMoveActive = true;
		}
	}
	void Obj::Checkhitfagment(TaskBase* fg)
	{
		Fragment::Obj* oFragment = (Fragment::Obj*)fg;
		Circle cHit;
		cHit.SetRadius(oFragment->cFragmentHitBase.GetRadius());
		cHit.SetPos(&oFragment->cFragmentHitBase.GetPos());
		if (cFragmentHitBase.CheckHit(&cHit))
		{
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				res->wsTest5.Play();
				//res->wsTest1.Pause();
			}

			oFragment->rFragment.SetDeg(rFragment.GetDeg(&oFragment->rFragment));
			//rFragment.SetDeg(oFragment->rFragment.GetDeg(&rFragment));
			oFragment->bRotationActive = false;
			oFragment->bMoveActive = true;
		}
	}
	void Obj::CheckhitAlien(TaskBase* al)
	{
		Alien::Obj* oAlien = (Alien::Obj*)al;
		Circle cAlHit;
		cAlHit.SetRadius(oAlien->cAlienRHitBase.GetRadius());
		cAlHit.SetPos(&oAlien->cAlienRHitBase.GetPos());
		Circle cPreHit;
		cPreHit.SetRadius(cFragmentHitBase.GetRadius());
		Point pPrePos;
		pPrePos = Point(cFragmentHitBase.GetPosX() - vMove.GetX(), cFragmentHitBase.GetPosY() - vMove.GetY());
		cPreHit.SetPos(&pPrePos);
		if (cFragmentHitBase.CheckHit(&cAlHit) && !cAlHit.CheckHit(&cPreHit))
		{
			rFragment.SetPos(&oAlien->cAlienRHitBase.GetPos());
			if (oAlien->FGHitFunc)oAlien->FGHitFunc(this);
		}
	}

	//ヒット後のInit
	void Obj::HitAfterInit() {
		rFragment.SetPos(&pInitPos);
		bMoveActive = false;
		bRotationActive = bPreRotationActive;
		/*bRotationActive = true;*/
	}


	void AnimFragmentY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 2) % 8;
		}
		++*bFrame;
	}
	void AnimFragmentR(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 2) % 8;
		}
		++*bFrame;
	}
	void AnimFragmentB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 2) % 8;
		}
		++*bFrame;
	}
}
