#pragma once
#include "MyGame/MyApp.h"

namespace FadeInOut
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
		bool bIsIn;			//インかアウトか判別

		Obj() {}
		~Obj() {}
	private:
		Rec rSquere[4];			//フェイドインアウト用の角側に配置
		float fSize;		//矩形の大きさ
		float fSizeValue;	//fSizeの変化量
		bool bActive;		//起動フラグ

		Rec rStar;
		float fStarSize;
		float fStarSizeValue;

		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
}