#pragma once
#include "MyGame/MyApp.h"

namespace FadeInOut
{
	const char caTaskName[] = { "フェイドインアウトタスク" };
	const char caResName[] = { "フェイドインアウトリソース" };

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
		
		float fStarSizeMax;
		float fStarSizeMin;

		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();

		/*仮*/
		void Start();
		void Stop();
		const bool IsComplete() const;
	}*Obj_ptr;
}