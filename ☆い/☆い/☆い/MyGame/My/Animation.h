#ifndef ANIM
#define ANIM
using AnimFunc = void(*)(byte * const, byte * const, byte * const);
typedef unsigned char byte;
/*アニメーションクラス*/
class Animation
{
	AnimFunc fpAnimFunc;
	byte bFrame;
	byte bAnimSrcX;
	byte bAnimSrcY;
public:
	/*コンストラクタ*/
	Animation()
		:
		fpAnimFunc(nullptr),
		bFrame(0),
		bAnimSrcX(0),
		bAnimSrcY(0)
	{

	}
	/*アニメーション関数の登録と初期切り取り位置を設定*/
	void SetAnim(AnimFunc fpAnimFunc, const byte bAnimSrcX)
	{
		if (this->GetNowAnim() == fpAnimFunc) return;
		this->fpAnimFunc = fpAnimFunc;
		this->bFrame = 0;
		this->bAnimSrcX = bAnimSrcX;
	}
	/*アニメーション関数を実行*/
	void Update()
	{
		if (!this->fpAnimFunc) return;
		this->fpAnimFunc(&this->bFrame, &this->bAnimSrcX, &this->bAnimSrcY);
	}
	/*現在登録されているアニメーション関数*/
	const AnimFunc GetNowAnim() const
	{
		return this->fpAnimFunc;
	}
	/*画像の切り取り位置のX座標*/
	const byte GetSrcX() const
	{
		return this->bAnimSrcX;
	}
	/*画像の切り取り位置のY座標*/
	const byte GetSrcY() const
	{
		return this->bAnimSrcY;
	}
};
#endif