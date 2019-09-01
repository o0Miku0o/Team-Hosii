#include "Tutorial.h"

namespace Tutorial
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iTutoImg.ImageCreate("./data/image/other/button.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iTutoImg.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);
		/*リソース生成*/
		RB::Add<Tutorial::RS>(caResName);
		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(0.2f);

		tState = Ttl_State::TTS_BUTTON;
		tBtn.bBtn = Buttons::BTN_B;
		tBtn.bState = Btn_State::BS_UP;

		rTutoBase.SetPos(&Point(25.f, 25.f));
		rTutoBase.Scaling(80.f, 80.f);
		rEfBase.SetPos(&Point(50.f + 25.f, 25.f));
		rEfBase.Scaling(50.f, 50.f);

		iaStickState[0] = Stk_State::STS_UP;
		iaStickState[1] = Stk_State::STS_NEUTRAL_L;
		iaStickState[2] = Stk_State::STS_DOWN;
		iaStickState[3] = Stk_State::STS_NEUTRAL_L;

		uiStickStateCount = 1;
		cppTarget = nullptr;
		uiLifeCount = 0;
		iOfsStickState = +1;
		bAnimCount = 0;
		bEfVisible = false;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		if (uiLifeCount <= 0)
		{
			Remove(this);
			return;
		}
		--uiLifeCount;
		if (cppTarget) rTutoBase.SetPos(cppTarget);
		rEfBase.SetPos(&Point(rTutoBase.GetPosX() + 30.f, rTutoBase.GetPosY() - 14.f));
		if (bAnimCount >= 30)
		{
			bAnimCount = 0;
			bEfVisible ^= 1;
			const int ciBtnState = tBtn.bState;
			tBtn.bState = (Btn_State)(ciBtnState ^ 1);
			
			uiStickStateCount = (uiStickStateCount + 1) % 4;
		}
		else ++bAnimCount;
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<Tutorial::RS>(caResName))
		{
			Frec src(0.f, 0.f, 16.f, 16.f);
			if (tState == Ttl_State::TTS_BUTTON)
			{
				const float cfSrcX = 16.f * tBtn.bBtn * 2;
				const float cfOfs = 16.f * tBtn.bState;
				src.l = cfSrcX + cfOfs;
				rTutoBase.Draw(&res->iTutoImg, &src);
				if (IsFalse(bEfVisible)) return;
				src.l = 16.f * 11;
				rEfBase.Draw(&res->iTutoImg, &src);
			}
			else
			{
				float fSrcX = 0.f;
				if (iaStickState[uiStickStateCount] == Stk_State::STS_NEUTRAL_R)
				{
					fSrcX = 16.f * 12;
				}
				else fSrcX = 16.f * (iaStickState[uiStickStateCount] + Buttons::BTN_MAX * 2);
				src.l = fSrcX;
				rTutoBase.Draw(&res->iTutoImg, &src);
			}
		}
	}

	void Obj::SetParam(const unsigned int auiInitLife, const Ttl_State atState, const unsigned int auiBNumber, const Point * const appPos, const Point * const appTarget)
	{
		uiLifeCount = auiInitLife;
		tState = atState;
		if (tState == Ttl_State::TTS_BUTTON)
		{
			tBtn.bBtn = (Buttons)Min(auiBNumber, (unsigned int)(Buttons::BTN_MAX - 1));
		}
		else if (auiBNumber == Stk_State::STS_NEUTRAL_R)
		{
			iaStickState[0] = Stk_State::STS_UP;
			iaStickState[1] = Stk_State::STS_NEUTRAL_R;
			iaStickState[2] = Stk_State::STS_DOWN;
			iaStickState[3] = Stk_State::STS_NEUTRAL_R;
		}
		rTutoBase.SetPos(appPos);
		cppTarget = appTarget;
	}
}