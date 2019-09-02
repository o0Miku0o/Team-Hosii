#pragma once
#include "MyGame/MyApp.h"

namespace StagePicture
{
	const char caTaskName[] = { "ステージピクチャータスク" };
	const char caResName[] = { "ステージピクチャーリソース" };

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

		Obj() {}
		~Obj() {}
	private:
		Image iStageImg;
		Rec rPictureBase;
		bool bIsLoaded;

		RS_ptr res;
		void Init();
		void Finalize();

	public:
		void Update();
		void Render();

		/*ステージの画像読み込み。パスは./data/image/other/Stage/st(auiStageNumber ステージの番号).bmpになる。*/
		void LoadImg(const unsigned int auiStageNumber);
		/*サイズ調整*/
		void SetSize(const float afWidth, const float afHeight);
		/*座標調整*/
		void SetPos(const Point * const appPos);
	}*Obj_ptr;
}