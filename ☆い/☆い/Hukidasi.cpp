#include "Hukidasi.h"

namespace Hukidasi
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
		SetName("吹き出しタスク");
		/*リソース生成*/
		RB::Add<RS>("吹き出しリソース");
		/*タスクの生成*/

		/*データの初期化*/
		rHukidasi = Rec();
		fAddScale = 0.f;
		fWidthMax = 0.f;
		fHeightMax = 0.f;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove("吹き出しリソース");
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		Resize();
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		rHukidasi.Draw();
	}
	/*吹き出しのサイズ変更*/
	void Obj::Resize()
	{
		const float fScaleW = rHukidasi.GetW() + fAddScale;
		const float fScaleH = rHukidasi.GetH() + fAddScale;
		const float fResizeW = Min(Max(fScaleW, 0.f), fWidthMax);
		const float fResizeH = Min(Max(fScaleH, 0.f), fHeightMax);
		rHukidasi.Scaling(fResizeW, fResizeH);
	}
	/**/
	void Obj::SetAddScale(const fix afAddScale)
	{
		fAddScale = afAddScale;
	}
	/**/
	void Obj::SetPos(const Point * const appPos)
	{
		rHukidasi.SetPos(appPos);
	}
}
