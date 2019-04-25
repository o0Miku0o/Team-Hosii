#include "Jupitor.h"
#include "StageManager.h"
#include "Beam.h"
#include "Fragment.h"

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
		SetName("木星タスク");
		/*リソース生成*/
		/*タスクの生成*/

		/*データの初期化*/
		rJupitor = Rec(800, 270, 16 * 20, 16 * 20);
		cJupitorHitBase = Circle(&rJupitor.GetPos(), rJupitor.GetW()*0.4f);
		cGravityCircle = Circle(&rJupitor.GetPos(), rJupitor.GetW()*0.8f);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto vf = FindAll<Fragment::Obj>("欠片タスク");
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
		if (auto beam = Find<Beam::Obj>("ビームタスク"))
		{
			BeamCheckhit(beam);
		}
		cJupitorHitBase.SetPos(&rJupitor.GetPos());
		cJupitorHitBase.SetRadius(rJupitor.GetW()*0.4f);
		cGravityCircle.SetPos(&rJupitor.GetPos());
		cGravityCircle.SetRadius(rJupitor.GetW()*0.8f);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
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
#ifdef _DEBUG
		cJupitorHitBase.Draw();
		cGravityCircle.Draw();
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
			oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->bMoveActive = false;
		}
	}
}
