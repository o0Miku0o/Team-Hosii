#include "BreakStar.h"
#include "Beam.h"
#include "StageManager.h"
#include "FragmentGenerator.h"
#include "BlackHoleGenerator.h"
#include "Title.h"
#include "Fragment.h"
#include "Eff1.h"
#include "Player.h"

namespace BreakStar
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
		SetRenderPriority(0.1f);
		rStar = Rec(Rec::Win.r * 0.75f, Rec::Win.b * 0.5f, 100, 100);
		cHitbase = Circle(&rStar.GetPos(), rStar.GetW() / 2);
		for (int i = 0; i < 5; i++)
		{
			rFrg[i] = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, 100.f, 100.f);
			rFrg[i].SetPos(&rStar.GetPos());
			rFrg[i].SetDeg(-90.f + (float)i * 72.f);
		}
		//rFrg1 = Rec(Rec::Win.r*0.5f, Rec::Win.b*0.5f, 100.f, 100.f);
		//rFrg2 = Rec(Rec::Win.r*0.5f, Rec::Win.b*0.5f, 100.f, 100.f);
		//rFrg3 = Rec(Rec::Win.r*0.5f, Rec::Win.b*0.5f, 100.f, 100.f);
		//rFrg4 = Rec(Rec::Win.r*0.5f, Rec::Win.b*0.5f, 100.f, 100.f);
		//rFrg0.SetDeg(90.f);
		//rFrg1.SetDeg(18.f);
		//rFrg2.SetDeg(-54.f);
		//rFrg3.SetDeg(-126.f);
		//rFrg4.SetDeg(162.f);
		iChange = 34;/*普通の星は34黒い星は37で初期値を設定する*/
		bHitAct = false;
		bBlackMode = true;
		bCrach = false;
		cnt = 0;
		effsp = Eff1::EffectCreater::SP(new Eff1::EffectCreater("./data/effect/ef_star_chipY.txt"));
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (!bHitAct && !bBlackMode)
		{
			if (auto beam = Find<Beam::Obj>(Beam::caTaskName))
			{
				BeamCheckHit(beam);
			}
			auto vFgm = FindAll <Fragment::Obj>(Fragment::caTaskName);
			if (vFgm.size())
			{
				for (auto& vf : vFgm)
				{
					FragmentCheckHit(vf);
				}
			}
		}
		if (!Find<Beam::Obj>(Beam::caTaskName))
		{
			bHitAct = false;
		}
		if (bBlackMode)
		{
			++iTime;
		}
		if (bCrach)
		{
			if (cnt > 20)
			{
				FrgCreate();
				Remove(this);
			}
			for (int i = 0; i < 5; i++)
			{
				vVec.SetVec(rFrg[i].GetDeg(), 10.f);
				rFrg[i].Move(&vVec);
			}
			Pause(Player::caTaskName, 1);
			//vVec.SetVec(rFrg1.GetDeg(), 1.f);
			//rFrg1.Move(&vVec);
			//vVec.SetVec(rFrg2.GetDeg(), 1.f);
			//rFrg2.Move(&vVec);
			//vVec.SetVec(rFrg3.GetDeg(), 1.f);
			//rFrg3.Move(&vVec);
			//vVec.SetVec(rFrg4.GetDeg(), 1.f);
			//rFrg4.Move(&vVec);

			cnt++;
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		//Font f;
		//f.FontCreate("メイリオ");
		//string temp = "temptempetmep " + std::to_string(rFrg[4].GetPosX()) + " " + std::to_string(rFrg[4].GetPosY()) + " ";
		//f.Draw(&Point(960.f, 540.f), temp.c_str());
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			if (bBlackMode)
			{
				Frec src(16.f * (iChange + iTime / 100), 0, 16.f, 16.f);
				rStar.Draw(&res->iStageImg, &src);
			}
			else
			{
				if (!bCrach)
				{
					Frec src(16.f * iChange, 0, 16.f, 16.f);
					rStar.Draw(&res->iStageImg, &src);
				}
				else
				{
					Frec frg1(16.f * 2, 0.f, 16.f, 16.f);
					for (int i = 0; i < 5; i++)
					{
						rFrg[i].Draw(&res->iStageImg, &frg1);
					}
					//rFrg1.Draw(&res->iStageImg, &frg1, true);
					//rFrg2.Draw(&res->iStageImg, &frg1, true);
					//rFrg3.Draw(&res->iStageImg, &frg1, true);
					//rFrg4.Draw(&res->iStageImg, &frg1, true);
				}
			}
#ifdef _DEBUG
			rStar.Draw();
#endif
			if (iTime > 299)
			{
				Remove(this);
				auto bf = Add<BlackHoleGenerator::Obj>();
				float size = 300.f;
				const int ciMode = 0;
				bf->Bridge(1, &Point(rStar.GetPosX(), rStar.GetPosY()), &size, &ciMode);
			}
			//else
			//{
			//	rStar.Draw(&res->iStageImg, &src, true);
			//	rStar.Draw();
			//}
			//if (iChange == 1)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}
			//if (iChange == 2)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}
			//if (iChange == 3)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}
			//if (iChange == 4)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}

#ifdef _DEBUG
			cHitbase.Draw();
#endif // _DEBUG
		}
	}
	void Obj::BeamCheckHit(TaskBase * bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cHit;
		cHit.SetRadius(oBeam->rHitBase.GetH());
		cHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cHitbase.CheckHit(&cHit))
		{
			if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
			{
				--sm->usBeamCount;
			}
			auto res = RB::Find<StageManager::RS>(StageManager::caResName);
			if (!bBlackMode)
			{
				if (iChange <= 36)
				{
					if (res)
					{
						res->wsTest6.Play();
					}
					//Eff1::Create("./data/effect/ef_star_chipY.txt", &rStar.GetPos(), 0);
					effsp->run(rStar.GetPos(), rStar.GetDeg());
					++iChange;
				}
				if (iChange > 36)
				{
					bCrach = true;
					if (res)
					{
						res->wsTest3.Play();
					}
				}
			}
			RemoveAll(Beam::caTaskName);
			bHitAct = true;
		}
	}
	void Obj::FragmentCheckHit(TaskBase * fr)
	{
		Fragment::Obj* oFragment = (Fragment::Obj*)fr;
		//Circle cHit;
		//cHit.SetRadius(oFragment->cFragmentHitBase.GetRadius());
		//cHit.SetPos(&oFragment->cFragmentHitBase.GetPos());
		if (cHitbase.CheckHit(&oFragment->cFragmentHitBase))
		{
			auto res = RB::Find<StageManager::RS>(StageManager::caResName);
			if (iChange <= 36)
			{
				if (res)
				{
					res->wsTest6.Play();
				}
				//Eff1::Create("./data/effect/ef_star_chipY.txt", &rStar.GetPos(), 0);
				effsp->run(rStar.GetPos(), rStar.GetDeg());
				++iChange;
			}
			if (iChange > 36)
			{
				bCrach = true;
				if (res)
				{
					res->wsTest3.Play();
				}
				//auto fg = Add<FragmentGenerator::Obj>();
				////Point pArr[5] = {/*Point(1000.f, 300.f) , Point(800.f, 500.f),Point(1200.f,500.f),Point(900.f,700.f),Point(1100.f,700.f)*/ };
				//Point pArr[5] = {
				//	Point(rStar.GetPosX(),rStar.GetPosY() - 200.f),Point(rStar.GetPosX() - 200.f,rStar.GetPosY()),Point(rStar.GetPosX() + 200.f,rStar.GetPosY()),
				//	Point(rStar.GetPosX() - 100.f,rStar.GetPosY() + 200.f), Point(rStar.GetPosX() + 100.f,rStar.GetPosY() + 200.f)
				//};
				//int iColor[5] = {};
				//fg->Bridge(5, pArr, iColor);
			}
			oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->rFragment.SetDeg(oFragment->fInitAngle);
			oFragment->cFragmentHitBase.SetPos(&oFragment->rFragment.GetPos());
			oFragment->bMoveActive = false;
			bHitAct = true;
		}
	}
	void Obj::FrgCreate()
	{
		auto fg = Add<FragmentGenerator::Obj>();
		//Point pArr[5] = {/*Point(1000.f, 300.f) , Point(800.f, 500.f),Point(1200.f,500.f),Point(900.f,700.f),Point(1100.f,700.f)*/ };
		vector<Point> pArr;
		vector<int> iColor;
		vector<float> angle;
		for (int i = 0; i < 5; i++)
		{
			pArr.push_back(rFrg[i].GetPos());
			iColor.push_back(0);
			angle.push_back(rFrg[i].GetDeg());
			//pArr[i] = rFrg[i].GetPos();
			//pArr
		}
		fg->Bridge3(5, pArr, iColor, angle);
	}
}