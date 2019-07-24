#include "Jupitor.h"
#include "StageManager.h"
#include "Beam.h"
#include "Fragment.h"
#include "Eff1.h"

namespace Jupitor
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
		rJupitor = Rec(800, 270, 16 * 20, 16 * 20);
		cJupitorHitBase = Circle(&rJupitor.GetPos(), rJupitor.GetW()*0.4f);
		cGravityCircle = Circle(&rJupitor.GetPos(), rJupitor.GetW()*0.8f);
		cGravityCircle.SetColor(0, 255, 0);
		rGravityCircle = Rec(rJupitor.GetPosX(), rJupitor.GetPosY(), rJupitor.GetW()*2.f, rJupitor.GetH()*2.f);
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
			if (cGravityCircle.CheckHit(&f->rFragment.GetPos()) && !cGravityCircle.CheckHit(&f->pPrevPos))
			{
				if (!f->bRotationActive)
				{
					f->pRotPos = cGravityCircle.GetPos();
					f->fRotRadius = cGravityCircle.GetRadius() - 1;
					f->bRotationActive = true;
					f->bMoveActive = false;
				}
			}
		}
		if (auto beam = Find<Beam::Obj>(Beam::caTaskName))
		{
			BeamCheckhit(beam);
		}
		cJupitorHitBase.SetPos(&rJupitor.GetPos());
		cJupitorHitBase.SetRadius(rJupitor.GetW()*0.4f);
		cGravityCircle.SetPos(&rJupitor.GetPos());
		cGravityCircle.SetRadius(rJupitor.GetW()*0.8f);
		rGravityCircle = Rec(rJupitor.GetPosX(), rJupitor.GetPosY(), rJupitor.GetW()*2.f, rJupitor.GetH()*2.f);

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * (iAnimCount + 12), 16, 16, 16);
			if (i >= 20)
			{
				i = 0;
				iAnimCount = (iAnimCount + 1) % 4;
			}
			++i;
			rJupitor.Draw(&res->iStageImg, &src, true);
		}
		cGravityCircle.Draw();
#ifdef _DEBUG
		cJupitorHitBase.Draw();
		Font f;
		std::string s = std::to_string(rJupitor.GetPosX()) + " " + std::to_string(rJupitor.GetPosY()) + " " + std::to_string(rJupitor.GetH());
		f.Draw(&rJupitor.GetPos(), s.c_str());
#endif // _DEBUG
	}
	void Obj::BeamCheckhit(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBmHit;
		cBmHit.SetRadius(oBeam->rHitBase.GetW()*0.5f);
		cBmHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cJupitorHitBase.CheckHit(&cBmHit))
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
		if (cJupitorHitBase.CheckHit(&cFrHit))
		{
			/*エフェクト放出*/
			static std::string fileName[3] = { "y_frg","r_frg","b_frg" };
			//Eff1::Create(fileName[oFragment->iColor], &oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
			effsp->_set_chip_type(fileName[oFragment->iColor]);
			effsp->run(oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
			oFragment->rFragment.SetDeg(rJupitor.GetDeg(&oFragment->rFragment));
			//oFragment->bPreRotationActive = !oFragment->bRotationActive;
			//oFragment->HitAfterInit();
			//oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//oFragment->bMoveActive = false;
			//oFragment->bRotationActive = true;
		}
	}
}
