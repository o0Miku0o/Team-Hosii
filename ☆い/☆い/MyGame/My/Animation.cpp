#include "Animation.h"
Animation *Animation::apTop = nullptr;
/*アニメーション関数を実行*/
void Animation::Update()
{
	if (!this->fpAnimFunc) return;
	this->fpAnimFunc(&this->bFrame, &this->bAnimSrcX, &this->bAnimSrcY);
}
/*全アニメーション関数を実行*/
void Animation::UpdateAll()
{
	auto apIt = apTop;
	while (apIt)
	{
		if(apIt->bUpdFlag) apIt->Update();
		apIt = apIt->apNext;
	}
}
/*コンストラクタ*/
Animation::Animation()
	:
	apNext(nullptr),
	apPrev(nullptr),
	fpAnimFunc(nullptr),
	bFrame(0),
	bAnimSrcX(0),
	bAnimSrcY(0),
	bUpdFlag(false)
{
	if (apTop)
	{
		auto apIt = apTop;
		while (apIt->apNext)
		{
			apIt = apIt->apNext;
		}
		apIt->apNext = this;
		this->apPrev = apIt;
		return;
	}
	apTop = this;
}
/*デストラクタ*/
Animation::~Animation()
{
	if (this->apPrev) this->apPrev->apNext = this->apNext;
	else apTop = this->apNext;
	if (this->apNext) this->apNext->apPrev = this->apPrev;
}
/*アニメーション関数の登録と初期切り取り位置を設定*/
void Animation::SetAnim(AnimFunc fpAnimFunc, const byte bAnimSrcX)
{
	if (this->GetNowAnim() == fpAnimFunc) return;
	this->fpAnimFunc = fpAnimFunc;
	this->bFrame = 0;
	this->bAnimSrcX = bAnimSrcX;
}
/*現在登録されているアニメーション関数*/
const AnimFunc Animation::GetNowAnim() const
{
	return this->fpAnimFunc;
}
/*画像の切り取り位置のX座標*/
const byte Animation::GetSrcX() const
{
	return this->bAnimSrcX;
}
/*画像の切り取り位置のY座標*/
const byte Animation::GetSrcY() const
{
	return this->bAnimSrcY;
}
/*アニメーション再生*/
void Animation::Play()
{
	if(!bUpdFlag) bUpdFlag = true;
}
/*アニメーション停止*/
void Animation::Stop()
{
	if (bUpdFlag) bUpdFlag = false;
}