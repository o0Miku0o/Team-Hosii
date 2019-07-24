#include "Saturn.h"
#include "Beam.h"
#include "Fragment.h"
#include "StageManager.h"
#include "Eff1.h"

namespace Saturn
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
		rSaturn = Rec(1000, 500, 16 * 14, 16 * 14);
		cSaturnHitBase = Circle(&rSaturn.GetPos(), rSaturn.GetH()*0.3f);
		cGravityCircle = Circle(&rSaturn.GetPos(), rSaturn.GetW()*0.8f);
		iAnimCount = 0;
		i = 12;
		effsp = Eff1::EffectCreater::SP(new Eff1::EffectCreater("./data/effect/ef_remove_frgY.txt"));
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto vf = FindAll<Fragment::Obj>(Fragment::caTaskName);
		for (auto &f : vf)
		{
			FragmentCheckhit(f);
			if (cGravityCircle.CheckHit(&f->rFragment.GetPos()) && !cGravityCircle.CheckHit(&f->pPrevPos)) {
				/*if (!f->bRotationActive)
				{
					f->pRotPos = cGravityCircle.GetPos();
					f->fRotRadius = cGravityCircle.GetRadius() - 1;
					f->bRotationActive = true;
					f->bMoveActive = false;
				}*/
			}
		}
		if (auto beam = Find<Beam::Obj>(Beam::caTaskName))
		{
			Obj::BeamCheckhit(beam);
		}
		cSaturnHitBase.SetPos(&rSaturn.GetPos());
		cSaturnHitBase.SetRadius(rSaturn.GetH()*0.3f);
		cGravityCircle.SetPos(&rSaturn.GetPos());
		cGravityCircle.SetRadius(rSaturn.GetW()*0.8f);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * (iAnimCount + 20), 16, 16, 16);
			if (i >= 25)
			{
				i = 0;
				iAnimCount = (iAnimCount + 1) % 4;
			}
			++i;
			rSaturn.Draw(&res->iStageImg, &src, true);
		}
#ifdef _DEBUG
		cSaturnHitBase.Draw();
		cGravityCircle.Draw();
		Font f;
		std::string s = std::to_string(rSaturn.GetPosX()) + " " + std::to_string(rSaturn.GetPosY()) + " " + std::to_string(rSaturn.GetH());
		f.Draw(&rSaturn.GetPos(), s.c_str());
#endif // _DEBUG

	}
	void Obj::BeamCheckhit(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBmHit;
		cBmHit.SetRadius(oBeam->rHitBase.GetW()*0.5f);
		cBmHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cSaturnHitBase.CheckHit(&cBmHit))
		{
			Remove(bm);
		}
	}
	void Obj::FragmentCheckhit(TaskBase* fr)
	{
		Fragment::Obj* oFragment = (Fragment::Obj*)fr;
		Circle cFrHit;
		cFrHit.SetRadius(oFragment->rFragment.GetW()*0.5f);
		cFrHit.SetPos(&oFragment->rFragment.GetPos());
		if (cSaturnHitBase.CheckHit(&cFrHit))
		{
			/*エフェクト放出*/
			static std::string fileName[3] = { "y_frg","r_frg","b_frg" };
			//Eff1::Create(fileName[oFragment->iColor], &oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
			effsp->_set_chip_type(fileName[oFragment->iColor]);
			effsp->run(oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
			/*byte loopmax = 31;
			for (byte b = 0; b < loopmax; ++b)
			{
				auto ef1 = Add<Eff1::Obj>();
				const fix fAng = ModAngle(360.f / loopmax * b);
				Rec rEf(f->rFragment.GetPosX(), f->rFragment.GetPosY(), 5, 5);//constつけなくてもOK
				Vector2 vSpd(cos(DtoR(fAng)) * 10, sin(DtoR(fAng)) * 10);
				ef1->SetParam(&rEf, &vSpd, 15, Eff1::Type::TYPE_Y_FRG, fAng);
			}*/
			oFragment->rFragment.SetDeg(rSaturn.GetDeg(&oFragment->rFragment));
			//oFragment->bRotationActive = oFragment->bPreRotationActive;
			//oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//oFragment->bMoveActive = false;
			//oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//oFragment->bMoveActive = false;
			//oFragment->bRotationActive = false;
		}
	}
}
