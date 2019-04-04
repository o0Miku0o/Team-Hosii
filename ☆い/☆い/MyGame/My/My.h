#pragma once
#include <Windows.h>
#include <stdarg.h>
#include <tchar.h>
#include <string>
#include <time.h>
#include <vector>
#include <mmsystem.h>
#include "FixedPoint.h"
#include "CGDM.h"

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

//おすすめ
//Xinput
//Xaudio

#ifdef _DEBUG
#define DBG_OUT(ccpDbgText) MessageBox(nullptr, (const char * const)ccpDbgText, "DBG", MB_OK)
#else
#define DBG_OUT(ccpDbgText) __noop
#endif

//Myネームスペース内のクラスで使用する透明色
constexpr COLORREF TRANSPARENT_COLOR = RGB(255, 0, 255);

constexpr char FTYPE_GOTHIC[] = "ＭＳ ゴシック";
constexpr char FTYPE_MINCHOU[] = "ＭＳ 明朝";
constexpr char FTYPE_MEIRIO[] = "メイリオ";

//マウスボタンのタイプ
enum MouseButton
{
	MS_LB,
	MS_RB,
	MS_MB,
	MS_BUT_MAX
};

enum Rec_Point
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	CENTER,
	POINT_MAX
};

/*円周率*/
constexpr double PI = 3.141592653589793238;

//角度変換関数
//度からラジアンに変換
inline constexpr float DtoR(const float angleD_)
{
	constexpr double cedTmp = PI / 180.0;
	return float(angleD_ * cedTmp);
}
//角度変換関数
//ラジアンから度に変換
inline constexpr float RtoD(const float angleR_)
{
	constexpr double cedTmp = 180. / PI;
	return float(angleR_ * cedTmp);
}
inline constexpr int I_DtoR(const float angleD_)
{
	return int(DtoR(angleD_));
}
inline constexpr int I_RtoD(const float angleR_)
{
	return int(RtoD(angleR_));
}
//角度の修正
inline constexpr float ModAngle(const float angleD_)
{
	float ang = angleD_;
	if (ang > 180.f)
	{
		while (ang > 180.f)
		{
			ang -= 360.f;
		}
	}
	else if (ang < -180.f)
	{
		while (ang < -180.f)
		{
			ang += 360.f;
		}
	}
	return ang;
}
//平方根計算関数（標準より高速！）
inline float Sqrt(const float val_)
{
	float xHalf = 0.5f * val_;
	int   tmp = 0x5F3759DF - (*(int*)&val_ >> 1); //initial guess
	float xRes = *(float*)&tmp;

	xRes *= float(1.5 - (xHalf * xRes * xRes));
	xRes *= float(1.5 - (xHalf * xRes * xRes));//コメントアウトを外すと精度が上がる
	return xRes * val_;
}
//平方根計算関数（標準より高速！）
inline double Sqrt(const double val_)
{
	double         xHalf = 0.5 * val_;
	long long int  tmp = 0x5FE6EB50C7B537AAl - (*(long long int*)&val_ >> 1);//initial guess
	double         xRes = *(double*)&tmp;

	xRes *= (1.5 - (xHalf * xRes * xRes));
	xRes *= (1.5 - (xHalf * xRes * xRes));//コメントアウトを外すと精度が上がる
	return xRes * val_;
}
/*abs()*/
template<class Value>
inline constexpr Value Abs(const Value &x)
{
	return Value((x > 0) ? x : ((x < 0) ? -x : 0));
}
/*max(a, b)*/
template<class Value1, class Value2>
inline constexpr Value1 Max(const Value1 &a, const Value2 &b)
{
	return Value1((a > (Value1)b) ? a : (Value1)b);
}
/*min(a, b)*/
template<class Value1, class Value2>
inline constexpr Value1 Min(const Value1 a, const Value2 b)
{
	return Value1((a < (Value1)b) ? a : (Value1)b);
}

//二次元ベクトルクラス
class Vector2
{
private:
	float x;
	float y;

public:
	/*ゼロベクトル*/
	static const Vector2 zero;
	/*左向き単位ベクトル*/
	static const Vector2 left;
	/*右向き単位ベクトル*/
	static const Vector2 right;
	/*上向き単位ベクトル*/
	static const Vector2 up;
	/*下向き単位ベクトル*/
	static const Vector2 down;

	//コンストラクタ
	Vector2(float x_, float y_);
	//コンストラクタ
	Vector2();
	//コピーコンストラクタ
	Vector2(const Vector2 &cpy_);
	//角度と長さからベクトルを設定
	void SetVec(const float angleD_, const float len_);
	//Xの値を取得
	const float GetX() const;
	//Yの値を取得
	const float GetY() const;
	//ベクトルの長さを取得
	const float GetLen() const;
	//ベクトルの角度を取得
	const float GetDeg() const;
	//内積を計算
	const float Dot(const Vector2 *vec2_) const;
	//外積を計算
	const float Cross(const Vector2 *vec2_) const;
	//ベクトルのスカラー倍
	void MulVec(const float scalar_);
	//ベクトルのスカラー倍
	const Vector2 operator * (const float scalar_) const;
	//ベクトルの比較
	const bool operator == (const Vector2 &vec2_) const;
	//ベクトルの比較
	const bool operator != (const Vector2 &vec2_) const;
};

//二次元座標構造体
struct Point
{
	float x;
	float y;
	/*コンストラクタ*/
	Point();
	/*コンストラクタ*/
	Point(const float x_, const float y_);
	/*POINTへのキャスト*/
	operator POINT ();
};

//フロート型RECT
struct Frec
{
	float l;
	float r;
	float t;
	float b;
	/*コンストラクタ*/
	Frec();
	/*コンストラクタ*/
	Frec(const float l_, const float t_, const float r_, const float b_);
	/*RECTへのキャスト*/
	operator RECT ();
};

//キーボードクラス
class KB
{
private:
	/*現在のキー状態*/
	byte nowkey[256];
	/*前フレームのキー状態*/
	byte prevkey[256];
	/*キーボード状態取得のためのインスタンスのポインタ*/
	static KB *instance;

public:
	/*コンストラクタ*/
	KB();
	//キー入力を取得するメンバ関数
	static bool GetKeyState();
	/*インスタンスのアドレスを取得*/
	static KB *GetState();
	/*現在のキー入力状態を取得*/
	byte Now(const char key_);
	/*前フレームのキー入力状態を取得*/
	byte Prev(const char key_);

	bool Down(const char cKey);

	bool On(const char cKey);

	bool Up(const char cKey);

	bool Off(const char cKey);
};

//マウスクラス
class MS
{
private:
	static HWND hWnd;
	Point pos;
	byte nowbut[MS_BUT_MAX];
	byte prevbut[MS_BUT_MAX];

	static MS *instance;

public:

	/*コンストラクタ*/
	MS(const HWND hWnd_);
	//マウス入力を取得するメンバ関数
	static bool GetMouseState();
	/*インスタンスのアドレスを取得*/
	static MS *GetState();
	/*現在のマウス入力状態を取得*/
	byte Now(const MouseButton but_);
	/*前フレームのマウス入力状態を取得*/
	byte Prev(const MouseButton but_);

	bool Down(const MouseButton but_);

	bool On(const MouseButton but_);

	bool Up(const MouseButton but_);

	bool Off(const MouseButton but_);
	/*カーソルの位置を取得*/
	const Point &GetPos();
	/*カーソルのX座標*/
	float GetPosX();
	/*カーソルのY座標*/
	float GetPosY();
};

//BMP管理クラス
class Image
{
private:
	HDC hBmpDC, hMaskBmpDC;
	HBITMAP hBmp, hMaskBmp;
	COLORREF oldBkColor;
	BITMAP BmpInfo;

public:
	//コンストラクタ
	Image();
	//デストラクタ
	~Image();
	//BMPファイル読み込みメンバ関数
	bool ImageCreate(const char * const bmpfilename_);
	//画像の解放
	void Release();
	//
	const BITMAP &GetBmpInfo() const;
	//
	const HDC GetImageHandle() const;
	//
	const HBITMAP GetMaskHandle() const;
};

struct FontOP
{
	int Weight;          // 太さ 
	DWORD Italic;        // イタリック 
	DWORD Underline;     // 下線 
	DWORD StrikeOut;     // 抹消線 
	DWORD CharSet;       // 書体設定 
	DWORD PitchAndFamily;// 文字の間隔

	FontOP();
	FontOP(const int Weight_, const DWORD Italic_, const DWORD Underline_, const DWORD StrikeOut_, const DWORD CharSet_, const DWORD PitchAndFamily_);
};

const FontOP FOP_DEFAULT(FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, FIXED_PITCH | FF_MODERN);

//フォントクラス
class Font
{
private:
	COLORREF col;
	HDC hOff;
	HFONT hf;
public:
	//コンストラクタ
	Font();
	//デストラクタ
	~Font();
	//フォント作成
	bool FontCreate(const char *fontname_, const FontOP *fontoption_ = &FOP_DEFAULT, int h_ = 0, float angleD_ = 0);
	//フォントの消去
	void Release();
	//色設定
	void SetColor(COLORREF col_);
	//色設定
	void SetColor(const byte r_, const byte g_, const byte b_);
	//描画
	void Draw(const Point * const pos_, const char * const text_);
};

/*waveファイル再生クラス*/
class WSound
{
	/*実体リストの先頭アドレス*/
	static WSound *pwsTop;
	/*ウェーブフォーマット*/
	WAVEFORMATEX wFormatEx;
	/*ウェーブヘッダ*/
	WAVEHDR wHdr;
	/*デバイスへのポインタ*/
	HWAVEOUT hWaveOut;
	/*コールバックウィンドウ*/
	HWND hCallBackWnd;
	/*次の要素*/
	WSound *next;
	/*前の要素*/
	WSound *prev;
	/*再生中かどうか*/
	bool bIsPlaying;
public:
	/*MM_WOM_DONEメッセージがポストされたら呼ぶ*/
	/*ループ再生を可能にする*/
	static void LoopProc(WPARAM wParam, LPARAM lParam);
	/*コンストラクタ*/
	WSound();
	/*デストラクタ*/
	~WSound();
	/*コールバックウィンドウを設定*/
	/*ウィンドウ名を引数に指定*/
	bool CallBack(const char * const ccpWinName);
	/*wavファイル読み込み*/
	bool SoundCreate(const char * const ccpWaveFileName);
	/*サウンドの破棄*/
	void Release();
	/*一回再生*/
	void Play();
	/*ループ再生*/
	/*適切にLoopProcが呼ばれていればループが機能する*/
	void PlayL();
	/*一時停止*/
	void Pause();
	/*一時停止解除*/
	void Restart();
	/*停止*/
	void Stop();
};

/*JoyPadの方向キー（スティック）*/
enum Joy_Direct
{
	J_UP,
	J_DOWN,
	J_LEFT,
	J_RIGHT,
	J_DIR_MAX,
};
/*JoyPadのボタン*/
enum Joy_Button
{
	//A
	J_BUT_1,
	//B
	J_BUT_2,
	//X
	J_BUT_3,
	//Y
	J_BUT_4,
	//LB
	J_BUT_5,
	//RB
	J_BUT_6,
	//BACK
	J_BUT_7,
	//START
	J_BUT_8,
	//L3
	J_BUT_9,
	//R3
	J_BUT_10,
	J_BUT_MAX,
};

/*JoyPad（ゲームパッド）クラス*/
class JoyPad
{
private:
	/*パッドの遊び*/
	static long lStickTolerance;
	/*ゲームパッドの最大数*/
	static constexpr byte PADNUM_MAX = 2;
	/*ゲームパッドからの情報格納変数*/
	static JOYINFOEX joy_ex[PADNUM_MAX];
	/*情報取得用インスタンスへのポインタの動的配列*/
	static std::vector<JoyPad *> instance;
	/*情報取得用インスタンスの数*/
	static byte inst_cnt;
	/*スティック押し込みベクトル*/
	static Vector2 vec2[2][PADNUM_MAX];
	/*現在の方向キーの状態*/
	static byte n_direct[PADNUM_MAX][J_DIR_MAX];
	/*現在のボタンの状態*/
	static byte n_buttons[PADNUM_MAX][J_BUT_MAX];
	/*前フレームの方向キーの状態*/
	static byte p_direct[PADNUM_MAX][J_DIR_MAX];
	/*前フレームのボタンの状態*/
	static byte p_buttons[PADNUM_MAX][J_BUT_MAX];
	/*左スティックのX軸押し込み状態*/
	static long axisx[PADNUM_MAX];
	/*左スティックのY軸押し込み状態*/
	static long axisy[PADNUM_MAX];
	/*左スティックのX軸の初期状態*/
	static unsigned long initaxisx[PADNUM_MAX];
	/*左スティックのY軸の初期状態*/
	static unsigned long initaxisy[PADNUM_MAX];
	/*右スティックのX軸押し込み状態*/
	static long Raxisx[PADNUM_MAX];
	/*右スティックのY軸押し込み状態*/
	static long Raxisy[PADNUM_MAX];
	/*右スティックのX軸の初期状態*/
	static unsigned long Rinitaxisx[PADNUM_MAX];
	/*右スティックのY軸の初期状態*/
	static unsigned long Rinitaxisy[PADNUM_MAX];

	/*インスタンスのID*/
	byte joy_id;

public:
	/*コンストラクタ*/
	JoyPad();
	/*JoyPadクラスの初期化*/
	static bool Init(const long lTolerance);
	/*全JoyPadの情報取得*/
	static bool GetStateAll();
	/*それぞれのJoyPadの情報をインスタンスから取得*/
	static JoyPad *GetState(const byte id_);
	/*現在のボタンの情報取得*/
	byte NowBut(const Joy_Button button_);
	/*現在の方向キーの情報取得*/
	byte NowDir(const Joy_Direct direct_);
	/*前フレームのボタンの情報取得*/
	byte PreBut(const Joy_Button button_);
	/*前フレームの方向キーの情報取得*/
	byte PreDir(const Joy_Direct direct_);

	bool Down(const Joy_Button but_);

	bool On(const Joy_Button but_);

	bool Up(const Joy_Button but_);

	bool Off(const Joy_Button but_);

	bool Down(const Joy_Direct direct_);

	bool On(const Joy_Direct direct_);

	bool Up(const Joy_Direct direct_);

	bool Off(const Joy_Direct direct_);
	/*左スティックのXY軸押し込み状態取得*/
	const Vector2 &GetAxisL() const;
	/*左スティックのXY軸押し込み状態取得*/
	/*引数には "Horizontal","Vertical" のどちらかを指定*/
	float GetAxisL(const char * const axis_) const;
	/*左スティックの押し込み方向（ラジアン）を取得*/
	float GetRadL() const;
	/*左スティックの押し込み方向（ディグリー）を取得*/
	float GetDegL() const;
	/*右スティックのXY軸押し込み状態取得関数*/
	const Vector2 &GetAxisR() const;
	/*右スティックのXY軸押し込み状態取得関数*/
	/*引数には "Horizontal","Vertical" のどちらかを指定*/
	float GetAxisR(const char * const axis_) const;
	/*右スティックの押し込み方向（ラジアン）を取得関数*/
	float GetRadR() const;
	/*右スティックの押し込み方向（ディグリー）を取得関数*/
	float GetDegR() const;
};
/*JoyPadクラスのインスタンスを参照するポインタ*/
typedef JoyPad *PJoyPad;

//矩形クラス
class Rec
{
private:
	static HDC off;
	static HBITMAP hoffbmp;
	static Frec frZoom;
	static Point Cam;
	static Point pAdjust;
	Point p[5];
	float w;
	float h;
	float dx;
	float dy;
	float angle;

public:
	//ウィンドウの矩形
	static Frec Win;
	//矩形クラスに描画バッファを作成（windowのサイズ取得）
	static bool Init(HWND hWnd_);
	//オフスクリーンをリセットする関数
	static void ResetOff(const DWORD rop_);
	//WM_PAINTメッセージ処理内でオンスクリーンに描画
	static void DrawBackToFront(HDC hOn_);
	//オフスクリーンとビットマップを破棄
	static void Release();
	//カメラの座標に合わせて位置を調整する
	static const Point &AdjustCamPos(const Point * const pPos);
	//カメラの座標を設定
	static void SetCameraPos(const Point * const pPos);
	//カメラを移動
	static void MoveCamera(const Vector2 * const vMove);
	//カメラの座標を取得
	static const Point &GetCameraPos();
	//カメラのX座標を取得
	static const float GetCameraPosX();
	//カメラのY座標を取得
	static const float GetCameraPosY();
	//ズーム
	static void Zoom(const float fMagni);
	//オフスクリーンのハンドルを取得
	static HDC GetOffScreenHandle();
	//コンストラクタ
	Rec(const float cx_, const float cy_, const float w_, const float h_, float angleD_ = 0);
	//コンストラクタ
	Rec();
	//コピーコンストラクタ
	Rec(const Rec & cpyrec_);
	//矩形を移動させる
	void SetPos(const Point * const pos_);
	//矩形を拡大縮小させる
	void Scaling(const float recw_, const float rech_);
	//自分の角度（ディグリー）を設定するメンバ関数
	void SetDeg(const float angleD_);
	//自分の角度（ディグリー）を取得するメンバ関数
	float GetDeg() const;
	//読み込んでおいたビットマップを描画(回転も可)
	void Draw(Image * const mybitmap_, const bool rot_ = false);
	//読み込んでおいたビットマップを描画(回転も可)
	void Draw(Image * const mybitmap_, const Frec * const frSrc, const bool rot_ = false);
	//不透明から透明まで値を指定して描画(透明色は無視される)
	void DrawAlpha(Image * const mybitmap_, byte alpha_ = 255);
	//矩形の外枠を描画するメンバ関数
	void Draw(int r_ = 255, int g_ = 255, int b_ = 255);
	//矩形同士の線分交差判定用メンバ関数
	bool CheckHit(const Rec * const rec_);
	//矩形と点の接触判定用メンバ関数
	bool CheckHit(const Point * const pos_);
	//矩形と点の接触判定用メンバ関数
	bool CheckHit(const float x_, const float y_);
	//自分の左が接触しているか
	//判定するメンバ関数
	bool CheckHitLeft(const Rec * const rec_);
	//自分の右が接触しているか
	//判定するメンバ関数
	bool CheckHitRight(const Rec * const rec_);
	//自分の上が接触しているか
	//判定するメンバ関数
	bool CheckHitTop(const Rec * const rec_);
	//自分の下が接触しているか
	//判定するメンバ関数
	bool CheckHitBottom(const Rec * const rec_);
	//矩形の幅
	float GetW() const;
	//矩形の高さ
	float GetH() const;
	//指定座標との角度(ラジアン)を取得するメンバ関数
	float GetRad(const float x_, const float y_) const;
	//別の矩形との角度(ラジアン)を取得するメンバ関数
	float GetRad(const Rec * const rec_) const;
	//指定座標との角度(ディグリー)を取得するメンバ関数
	float GetDeg(const float x_, const float y_) const;
	//指定座標との角度(ディグリー)を取得するメンバ関数
	float GetDeg(const Point * const pos_) const;
	//別の矩形との角度(ディグリー)を取得するメンバ関数
	float GetDeg(const Rec * const rec_) const;
	//矩形を移動させる
	void Move(const Vector2 * const vec2_);
	//点との距離を取得するメンバ関数
	float GetDist(const float x_, const float y_) const;
	//点との距離を取得するメンバ関数
	float GetDist(const Point * const pos_) const;
	//別の矩形との距離を取得するメンバ関数
	float GetDist(const Rec * const rec_) const;
	//矩形の中心点を返すメンバ関数
	const Point &GetPos() const;
	//矩形の中心点のX座標
	float GetPosX() const;
	//矩形の中心点のY座標
	float GetPosY() const;
	//
	const Point &GetTL() const;
	//
	const Point &GetTR() const;
	//
	const Point &GetBL() const;
	//
	const Point &GetBR() const;
};

/*円クラス*/
class Circle
{
private:
	/*中心座標*/
	Point center;
	/**/
	HDC hOff;
	/*ペン*/
	HPEN hPen;
	/*カラー*/
	COLORREF color;
	/*半径*/
	float radius;

public:
	/*コンストラクタ*/
	Circle();
	/*コンストラクタ*/
	Circle(const Point * const position_, const float radius_);
	/*中心座標設定*/
	void SetPos(const Point * const pos_);
	/*半径設定*/
	void SetRadius(const float radius_);
	/*色設定*/
	void SetColor(const byte r_, const byte g_, const byte b_);
	/*座標取得*/
	const Point &GetPos() const;
	/*X座標取得*/
	const float GetPosX() const;
	/*Y座標取得*/
	const float GetPosY() const;
	/*半径取得*/
	const float GetRadius() const;
	/*描画*/
	void Draw();
	/*当たり判定*/
	const bool CheckHit(const Circle * const circle_) const;
	/*当たり判定*/
	const bool CheckHit(const Point * const point_) const;
};

/*線クラス*/
class Line
{
	/*始点*/
	Point spos;
	/*終点*/
	Point epos;
	/*ある円との交点*/
	Point inter;
	/**/
	Vector2 vec2;
	/**/
	HDC hOff;
	/*ペン*/
	HPEN hPen;
	/*カラー*/
	COLORREF color;
	/*角度*/
	float angle;
	/*幅*/
	int width;
	/*長さ*/
	float len;
public:
	/*コンストラクタ*/
	Line();
	/*コンストラクタ*/
	Line(const Point * const spos_, const Point * const epos_);
	/*始点設定*/
	void SetPos(const Point * const spos_);
	/*始点と終点設定*/
	void SetPos(const Point * const spos_, const Point * const epos_);
	/*始点と終点設定*/
	void SetPos(const Point * const spos_, const float angleD_, const float len_);
	/*始点設定*/
	void SetSPos(const Point * const spos_);
	/*終点設定*/
	void SetEPos(const Point * const epos_);
	/*色設定*/
	void SetColor(const byte r_, const byte g_, const byte b_);
	/*幅設定*/
	void SetWidth(const int width_);
	/*角度設定*/
	void SetDeg(const float angleD_);
	/*長さ設定*/
	void SetLen(const float len_);
	/*始点取得*/
	const Point &GetSPos() const;
	/*終点取得*/
	const Point &GetEPos() const;
	/*角度取得*/
	float GetDeg() const;
	/*角度取得*/
	float GetDeg(const Line * const line_) const;
	/*角度取得*/
	float GetDeg(const Rec * const rec_) const;
	/*角度取得*/
	float GetDeg(const Point * const pos_) const;
	/*長さ取得*/
	float GetLen() const;
	/*距離取得*/
	float GetDist(const Circle * const circle_) const;
	/*距離取得*/
	float GetDist(const Point * const pos_) const;
	/*ベクトル取得*/
	const Vector2 &GetVec() const;
	/*線と円の交点を取得*/
	const Point &GetPOI(const Circle * const circle_);
	/*線と線の交点を取得*/
	const Point &GetPOI(const Line * const line_);
	/*移動*/
	void Move(const float movespd_);
	/*描画*/
	void Draw();
	/*当たり判定*/
	bool CheckHit(const Line * const line_);
	/*当たり判定*/
	bool CheckHit(const Rec * const rec_);
	/*当たり判定*/
	bool CheckHit(const Circle * const circle_);
};

//ファイルを操作するクラス
class FileIO
{
private:
	FILE * fp;

public:
	//コンストラクタ
	FileIO();
	//デストラクタ
	~FileIO();
	//ファイルへ書き込むメンバ関数
	bool SaveFile(const void * const buf_, const int elementsize_);
	//ファイルから読み込むメンバ関数
	bool LoadFile(void * const buf_, const int elementsize_);
	//ファイルへの書き込み
	template<class T>
	void operator << (const T &in_)
	{
		if (!fp) return;
		fwrite(&in_, sizeof(in_), 1, fp);
	}
	//ファイルからの読み込み
	template<class T>
	void operator >> (T &out_)
	{
		if (!fp && feof(fp) == EOF) return;
		fread(&out_, sizeof(out_), 1, fp);
	}
	//ファイルを開くメンバ関数
	bool Open(const char *filename_, const char * const format_);
	//ファイルを閉じるメンバ関数
	bool Close();
};

//タイマークラス
class Timer
{
private:
	bool active;
	int interval;
	int cntmax;
	int cnt;

public:
	//コンストラクタ
	Timer(const int interval_);
	//コンストラクタ
	Timer();
	//インターバル設定
	void Set(const int interval_);
	//スタート
	void Start();
	//インターバルごとにtrueを返す
	bool Tick();
	//ストップ
	void Stop();
};

class Pixel
{
	Point pPos;
	COLORREF cColor;
	HDC hOff;
public:
	Pixel()
		:
		pPos({}),
		cColor(0),
		hOff(Rec::GetOffScreenHandle())
	{
	}
	Pixel(const Point &crefpPos, const COLORREF ccColor)
		:
		pPos(crefpPos),
		cColor(ccColor),
		hOff(Rec::GetOffScreenHandle())
	{
	}
	Pixel(const Pixel &crefPixel)
		:
		pPos(crefPixel.pPos),
		cColor(crefPixel.cColor),
		hOff(Rec::GetOffScreenHandle())
	{
	}
	const Point SetPos(const Point * const cppPos)
	{
		const Point cpOld = pPos;
		pPos = *cppPos;
		return cpOld;
	}
	const COLORREF SetColor(const COLORREF ccColor)
	{
		const COLORREF ccOld = cColor;
		cColor = ccColor;
		return ccOld;
	}
	const Point &GetPos() const
	{
		return pPos;
	}
	const float GetPosX() const
	{
		return pPos.x;
	}
	const float GetPosY() const
	{
		return pPos.y;
	}
	void Draw() const
	{
		SetPixel(hOff, int(pPos.x), int(pPos.y), cColor);
	}
};

#ifdef _DEBUG
struct DBG
{
private:
	static Point spDrawPos;
	static Font sfFont;
public:
	static void ResetPos()
	{
		spDrawPos = { Rec::GetCameraPosX() - Rec::Win.r * 0.5f, Rec::GetCameraPosY() - Rec::Win.b * 0.5f };
	}
	template<class Type>
	static void OutPut(const Type &tValue)
	{
		sfFont.FontCreate("メイリオ");
		sfFont.SetColor(RGB(150, 200, 255));
		sfFont.Draw(&spDrawPos, std::to_string(tValue).c_str());
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
	static void OutPut(const char(&ccaFmt)[])
	{
		sfFont.FontCreate("メイリオ");
		sfFont.SetColor(RGB(150, 200, 255));
		sfFont.Draw(&spDrawPos, ccaFmt);
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
	template<unsigned short usBufSize, class Type>
	static void OutPut(const char(&ccaFmt)[], const Type &tValue)
	{
		sfFont.FontCreate("メイリオ");
		sfFont.SetColor(RGB(150, 200, 255));
		char caText[usBufSize] = {};
		sprintf_s(caText, ccaFmt, tValue);
		sfFont.Draw(&spDrawPos, caText);
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
	template<unsigned short usBufSize, class Type>
	static void OutPut(const char * const ccpFmt, const Type &tValue)
	{
		sfFont.FontCreate("メイリオ");
		sfFont.SetColor(RGB(150, 200, 255));
		char caText[usBufSize] = {};
		sprintf_s(caText, ccpFmt, tValue);
		sfFont.Draw(&spDrawPos, caText);
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
};
#endif