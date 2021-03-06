#pragma once
#include "MyGame\TaskBase.h"
#include "MyGame/My/Animation.h"

namespace BlackHole
{
	const char caTaskName[] = { "ブラックホールタスク" };
	const char caResName[] = { "ブラックホールリソース" };

	/*リソース*/
	class RS : public ResourceBase
	{
	public:
		/*ここに共通変数を追加*/
		/*以下変更不要*/
		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;

	/*タスクオブジェクト*/
	typedef class Obj : public TaskBase
	{
	public:
		/*ここにタスクごとの変数を追加*/
		Rec	rBlackHole; //描画用
		Circle cInnerCircle , cOutCircle; //内側円
		Circle cInnerInner;
		Point pPos;
		bool bBigger;
		bool bMove;
		bool bCreate;
		Point pEndPos;
		Point pStartPos;
		float fAngle;
		Animation aAnim;

		//普通
		bool IsCreate();
		//どんどん大きくなる
		bool IsBigger();
		//移動する
		bool IsMove();

		void CheckHitBeam(TaskBase *bm);
		void CheckHitFragment(TaskBase *fg);
		float CalcAngle(const Point targetPos, const Point bhPos, const float targetAngle);
		//消滅までの処理

		/*以下変更不要*/
		Obj() { Init(); }
		~Obj() { Finalize(); }
	private:
		/*リソースを参照*/
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*Obj_ptr;

	void AnimBH(byte *bFrame, byte *bSrcX, byte *bSrcY);
}