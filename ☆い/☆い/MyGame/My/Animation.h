#ifndef ANIM
#define ANIM
typedef unsigned char byte;
using AnimFunc = void(*)(byte * const, byte * const, byte * const);
/*アニメーションクラス*/
class Animation
{
	static Animation *apTop;
	Animation *apNext;
	Animation *apPrev;
	AnimFunc fpAnimFunc;
	byte bFrame;
	byte bAnimSrcX;
	byte bAnimSrcY;
	bool bUpdFlag;

	/*アニメーション関数を実行*/
	void Update();
public:
	/*全アニメーション関数を実行*/
	static void UpdateAll();
	/*コンストラクタ*/
	Animation();
	/*デストラクタ*/
	~Animation();
	/*アニメーション関数の登録と初期切り取り位置を設定*/
	void SetAnim(AnimFunc fpAnimFunc, const byte bAnimSrcX);
	/*現在登録されているアニメーション関数*/
	const AnimFunc GetNowAnim() const;
	/*画像の切り取り位置のX座標*/
	const byte GetSrcX() const;
	/*画像の切り取り位置のY座標*/
	const byte GetSrcY() const;
	/*アニメーション再生*/
	void Play();
	/*アニメーション停止*/
	void Stop();
};
#endif