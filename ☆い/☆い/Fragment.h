#pragma once
#include "MyGame/MyApp.h"

namespace Fragment
{
	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*タスクオブジェクトクラス*/
	typedef class Obj : public TaskBase
	{
	public:
		/*必要なメンバはここに追加*/
		Rec rFragment;
		Circle cFragmentHitBase;
		Point pInitPos;
		Point pRotPos;
		Point pPrevPos;
		float fRotRadius;

		int iRotation;
		int iColor;/*黄色が0、赤が1、青が2*/
		bool bMoveActive;
		bool bRotationActive;
		Vector2 vMove;

		Animation aAnim;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void Checkhitbeam(TaskBase* bm);
		void Checkhitfagment(TaskBase* fg);
		void CheckhitAlien(TaskBase* al);
	}*OBJ_ptr;
	void AnimFragmentY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimFragmentR(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimFragmentB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);

}