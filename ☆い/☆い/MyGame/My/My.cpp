#include "My.h"

//キーボードクラス
KB *KB::instance = nullptr;
//コンストラクタ
KB::KB()
{
	instance = this;
	for (int i = 0; i < 256; ++i)
		nowkey[i] = 0;
	for (int i = 0; i < 256; ++i)
		prevkey[i] = 0;
}
//キー入力を取得するメンバ関数
bool KB::GetKeyState()
{
	if (!instance) return 1;
	for (int i = 0; i < 256; ++i)
		instance->prevkey[i] = instance->nowkey[i];

	unsigned char bufkey[256] = {};
	GetKeyboardState(bufkey);
	for (int i = 0; i < 256; ++i)
	{
		if (bufkey[i] & 0x80)
		{
			++instance->nowkey[i];
			if (instance->nowkey[i] >= 255) instance->nowkey[i] = 2;
		}
		else
			instance->nowkey[i] ^= instance->nowkey[i];
	}
	return 0;
}
KB *KB::GetState()
{
	return instance;
}
/*現在のキー入力状態を取得*/
byte KB::Now(const char key_)
{
	return nowkey[key_];
}
/*前フレームのキー入力状態を取得*/
byte KB::Prev(const char key_)
{
	return prevkey[key_];
}

bool KB::Down(const char cKey)
{
	return (!prevkey[cKey] && nowkey[cKey]);
}

bool KB::On(const char cKey)
{
	return (prevkey[cKey] && nowkey[cKey]);
}

bool KB::Up(const char cKey)
{
	return (prevkey[cKey] && !nowkey[cKey]);
}

bool KB::Off(const char cKey)
{
	return (!prevkey[cKey] && !nowkey[cKey]);
}

/*マウスクラス*/
HWND MS::hWnd = nullptr;
MS *MS::instance = nullptr;

//コンストラクタ
MS::MS(const HWND hWnd_)
	:
	pos(0.f, 0.f)
{
	hWnd = hWnd_;
	instance = this;
	for (int i = 0; i < MS_BUT_MAX; ++i)
		nowbut[i] = 0;
	for (int i = 0; i < MS_BUT_MAX; ++i)
		prevbut[i] = 0;
}
//マウスの入力状態を取得するメンバ関数
bool MS::GetMouseState()
{
	if (!instance) return 1;
	for (int i = 0; i < MS_BUT_MAX; ++i)
		instance->prevbut[i] = instance->nowbut[i];

	char b[MS_BUT_MAX] = { VK_LBUTTON ,VK_RBUTTON ,VK_MBUTTON };

	for (int i = 0; i < MS_BUT_MAX; ++i)
	{
		if (GetAsyncKeyState(b[i]) & 0x8000)
		{
			++instance->nowbut[i];
			if (instance->nowbut[i] >= 255) instance->nowbut[i] = 2;
		}
		else
			instance->nowbut[i] ^= instance->nowbut[i];
	}

	if (!hWnd) return 1;
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hWnd, &point);
	/**/instance->pos = { (float)point.x, (float)point.y };
	/*/instance->pos = Rec::AdjustCamPos(&Point((float)point.x, (float)point.y));/**/
	return 0;
}
/*インスタンスのアドレスを取得*/
MS *MS::GetState()
{
	return instance;
}
/*マウスカーソルの表示の有無*/
bool MS::Visible(const bool bVisible)
{
	while (ShowCursor(bVisible) != -1);
	return 1;
}
/*現在のマウス入力状態を取得*/
byte MS::Now(const MouseButton but_)
{
	return nowbut[but_];
}
/*前フレームのマウス入力状態を取得*/
byte MS::Prev(const MouseButton but_)
{
	return prevbut[but_];
}

bool MS::Down(const MouseButton but_)
{
	return (!prevbut[but_] && nowbut[but_]);
}

bool MS::On(const MouseButton but_)
{
	return (prevbut[but_] && nowbut[but_]);
}

bool MS::Up(const MouseButton but_)
{
	return (prevbut[but_] && !nowbut[but_]);
}

bool MS::Off(const MouseButton but_)
{
	return (!prevbut[but_] && !nowbut[but_]);
}
/*カーソルの位置を取得*/
const Point &MS::GetPos()
{
	return pos;
}
/*カーソルのX座標*/
float MS::GetPosX()
{
	return pos.x;
}
/*カーソルのY座標*/
float MS::GetPosY()
{
	return pos.y;
}

//
const Vector2 Vector2::zero = Vector2(0.f, 0.f);
const Vector2 Vector2::left = Vector2(-1.f, 0.f);
const Vector2 Vector2::right = Vector2(1.f, 0.f);
const Vector2 Vector2::up = Vector2(0.f, -1.f);
const Vector2 Vector2::down = Vector2(0.f, 1.f);
//
Vector2::Vector2(float x_, float y_)
	:x(x_), y(y_)
{

}
//
Vector2::Vector2()
	: x(0.f), y(0.f)
{

}
//
Vector2::Vector2(const Vector2 &cpy_)
	: x(cpy_.x), y(cpy_.y)
{

}
//
void Vector2::SetVec(const float angleD_, const float dist_)
{
	const double ang = (double)DtoR(ModAngle(angleD_));
	x = (float)cos_fast(ang) * dist_;
	y = (float)sin_fast(ang) * dist_;

	//x = cos(DtoR(angleD_)) * dist_;
	//y = sin(DtoR(angleD_)) * dist_;
}
//
const float Vector2::GetX() const
{
	return x;
}
//
const float Vector2::GetY() const
{
	return y;
}
//ベクトルの長さを取得
const float Vector2::GetLen() const
{
	return Sqrt(x * x + y * y);
}
//ベクトルの角度を取得
const float Vector2::GetDeg() const
{
	return RtoD(atan2(y, x));
}
//
const float Vector2::Dot(const Vector2 *vec2_) const
{
	return (x * vec2_->x + y * vec2_->y);
}
//
const float Vector2::Cross(const Vector2 *vec2_) const
{
	return (x * vec2_->y - y * vec2_->x);
}
//ベクトルのスカラー倍
void Vector2::MulVec(const float scalar_)
{
	x *= scalar_;
	y *= scalar_;
}
//ベクトルのスカラー倍
const Vector2 Vector2::operator * (const float scalar_) const
{
	return Vector2(x * scalar_, y * scalar_);
}
//ベクトルの比較
const bool Vector2::operator == (const Vector2 &vec2_) const
{
	return ((x == vec2_.x) ? ((y == vec2_.y) ? 1 : 0) : 0);
}
//ベクトルの比較
const bool Vector2::operator != (const Vector2 &vec2_) const
{
	return ((x != vec2_.x) ? 1 : ((y != vec2_.y) ? 1 : 0));
}

/*二次元座標構造体*/
/*コンストラクタ*/
Point::Point()
	:
	x(0.f),
	y(0.f)
{

}
/*コンストラクタ*/
Point::Point(const float x_, const float y_)
	:
	x(x_),
	y(y_)
{

}
/*POINTへのキャスト*/
Point::operator POINT ()
{
	return { (long)x, (long)y };
}

/*フロート型RECT*/
/*コンストラクタ*/
Frec::Frec()
	:
	l(0.f),
	r(0.f),
	t(0.f),
	b(0.f)
{

}
/*コンストラクタ*/
Frec::Frec(const float l_, const float t_, const float r_, const float b_)
	:
	l(l_),
	r(r_),
	t(t_),
	b(b_)
{

}
/*RECTへのキャスト*/
Frec::operator RECT()
{
	return { (long)l, (long)t, (long)r, (long)b };
}

//
//コンストラクタ
Image::Image()
	:hBmpDC(nullptr), hMaskBmpDC(nullptr),
	hBmp(nullptr), hMaskBmp(nullptr),
	oldBkColor(0),
	BmpInfo({})
{
}

Image::~Image()
{
	Release();
}

bool Image::ImageCreate(const char * const bmpfilename_)
{
	hBmp = (HBITMAP)LoadImage(NULL, bmpfilename_, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (!hBmp)
		return 1;
	GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

	hBmpDC = CreateCompatibleDC(NULL);
	if (!hBmpDC)
		return 1;

	SelectObject(hBmpDC, hBmp);

	oldBkColor = SetBkColor(hBmpDC, TRANSPARENT_COLOR);

	hMaskBmpDC = CreateCompatibleDC(NULL);
	if (!hMaskBmpDC)
		return 1;

	hMaskBmp = CreateBitmap(BmpInfo.bmWidth, BmpInfo.bmHeight, 1, 1, NULL);
	if (!hMaskBmp)
		return 1;

	SelectObject(hMaskBmpDC, hMaskBmp);

	BitBlt(hMaskBmpDC, 0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, hBmpDC, 0, 0, NOTSRCCOPY);//色反転

	SetBkColor(hBmpDC, oldBkColor);
	return 0;
}
//画像の解放
void Image::Release()
{
	if (hBmpDC)
	{
		DeleteDC(hBmpDC);
		hBmpDC = nullptr;
	}
	if (hMaskBmpDC)
	{
		DeleteDC(hMaskBmpDC);
		hMaskBmpDC = nullptr;
	}
	if (hBmp)
	{
		DeleteObject(hBmp);
		hBmp = nullptr;
	}
	if (hMaskBmp)
	{
		DeleteObject(hMaskBmp);
		hMaskBmp = nullptr;
	}
}
//
const BITMAP &Image::GetBmpInfo() const
{
	return BmpInfo;
}
//
const HDC Image::GetImageHandle() const
{
	return hBmpDC;
}
//
const HDC Image::GetMaskHandle() const
{
	return hMaskBmpDC;
}
//
const HBITMAP Image::GetMaskBitMap() const
{
	return hMaskBmp;
}

FontOP::FontOP()
	:
	Weight(FW_REGULAR),
	Italic(FALSE),
	Underline(FALSE),
	StrikeOut(FALSE),
	CharSet(SHIFTJIS_CHARSET),
	PitchAndFamily(FIXED_PITCH | FF_MODERN)
{

}

FontOP::FontOP(const int Weight_, const DWORD Italic_, const DWORD Underline_, const DWORD StrikeOut_, const DWORD CharSet_, const DWORD PitchAndFamily_)
	:
	Weight(Weight_),
	Italic(Italic_),
	Underline(Underline_),
	StrikeOut(StrikeOut_),
	CharSet(CharSet_),
	PitchAndFamily(PitchAndFamily_)
{

}
//
Font::Font()
	:
	hf(nullptr),
	hOff(Rec::GetOffScreenHandle()),
	col(WHITE_COLOR)
{

}
//
Font::~Font()
{
	Release();
}
//
bool Font::FontCreate(const char *fontname_, int h_, float angleD_, const FontOP *fontoption_)
{
	hf = CreateFont
	(
		h_,
		0,
		(int)angleD_,
		0,
		fontoption_->Weight,
		fontoption_->Italic,
		fontoption_->Underline,
		fontoption_->StrikeOut,
		fontoption_->CharSet,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		fontoption_->PitchAndFamily,
		fontname_
	);
	return 0;
}
//
void Font::Release()
{
	if (hf) DeleteObject(hf);
}
//色設定
void Font::SetColor(COLORREF col_)
{
	col = col_;
}
//色設定
void Font::SetColor(const byte r_, const byte g_, const byte b_)
{
	col = RGB(r_, g_, b_);
}

void Font::Draw(const Point * const pos_, const char * const text_)
{
	const POINT dp = { (long)Rec::AdjustCamPos(pos_).x, (long)Rec::AdjustCamPos(pos_).y };

	HGDIOBJ old = nullptr;
	if (hf) old = SelectObject(hOff, hf);
	//文字色を引数から指定
	SetTextColor(hOff, col);
	//背景色を透過に指定
	SetBkMode(hOff, TRANSPARENT);
	//引数から指定されたデバイスコンテキストに文字列を描画
	TextOut(hOff, dp.x, dp.y, text_, lstrlen(text_) + 1);
	if (old) SelectObject(hOff, old);
}

static bool LoadWavFile(const char * const ccpFileName, WAVEFORMATEX *lpwfe, WAVEHDR *lpwhdr)
{
	/*ファイルオープン＆オールコピー*/
	/*ファイルを開いて、その全てをメモリ領域にコピーします。*/
	HANDLE fh = CreateFile
	(
		ccpFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	);
	if (fh == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "ファイルを開けません", ccpFileName, MB_OK);
		return 1;
	}
	DWORD dwFileSize = GetFileSize(fh, NULL);
	BYTE *lpBuf = (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
	DWORD dwReadSize;
	ReadFile(fh, lpBuf, dwFileSize, &dwReadSize, NULL);
	CloseHandle(fh);
	/*ファイル形式のチェック*/
	/*ファイルの先頭から8～11バイトに "WAVE" という文字列があればWAVEファイルであると判断できます。*/
	char str[5];
	strncpy_s(str, (char *)(lpBuf + 8), 4);
	if (strncmp(str, "WAVE", 4))
	{
		HeapFree(GetProcessHeap(), 0, lpBuf);
		MessageBox(NULL, "WAVEファイルを指定して下さい", ccpFileName, MB_OK);
		return 1;
	}
	/*フォーマット情報のコピー*/
	/*フォーマット情報(WAVEの属性)をWAVEFORMATEX構造体にコピーします。
	  ファイルにはPCMWAVEFORMAT構造体の形で保存されていますが、
	  最後のメンバ WORD cbSize が無いだけで、他は同じです。

	  PCMWAVEFORMAT構造体のサイズは16バイトです。
	  ファイルの先頭から16～19バイトにフォーマット情報のバイト数が格納されていますが、
	  PCM形式の場合は16バイトに決まっています。
	  もし16バイトじゃなければPCM形式ではない事になるので、後々のチェックに引っ掛かるでしょう。

	  ちなみに、コピー先であるWAVEFORMATEX構造体のサイズは20バイトなので、
	  sizeof(WAVEFORMATEX) としてはいけません。*/
	CopyMemory(lpwfe, lpBuf + 20, 16);
	/*WAVE形式のチェック*/
	/*形式はWAVEFORMATEX構造体の wFormatTag メンバに格納されています。*/
	if (lpwfe->wFormatTag != WAVE_FORMAT_PCM)
	{
		HeapFree(GetProcessHeap(), 0, lpBuf);
		MessageBox(NULL, "PCM形式のWAVEファイルを指定して下さい", ccpFileName, MB_OK);
		return 1;
	}
	/*ファイルの先頭から波形データの先頭までのバイト数*/
	/*ファイルの先頭から36～39バイトには "fact" か "data" があります。
	  factチャンクには必要な情報はありませんが、factチャンクの有無で後々のアドレスが違ってくるので、
	  ファイルの先頭から波形データの先頭までのバイト数を設定します。*/
	int offset = 0;
	char *pIt = (char *)(lpBuf + 36);
	int count = 0;
	while (strncmp(pIt, "fact", 4) && strncmp(pIt, "data", 4))
	{
		++pIt;
		++count;
	}
	if (!strncmp(pIt, "fact", 4)) offset = count + 56;         // factチャンクが有る
	else if (!strncmp(pIt, "data", 4)) offset = count + 44;    // dataチャンク(factチャンクが無い)
	else
	{
		HeapFree(GetProcessHeap(), 0, lpBuf);
		MessageBox(NULL, "正体不明のファイルです", ccpFileName, MB_OK);
		return 1;
	}
	/*波形データをコピー*/
	/*ファイルの先頭から波形データの先頭までのバイト数である offset の4バイト前には
	  波形データのバイト数が格納されています。
	  波形データのバイト数を取得＆保存したら、
	  このサイズ分の新たなメモリ領域を確保して波形データをコピーしましょう。
	  波形データのコピーが終了したらファイル全体をコピーしたメモリ領域は解放してしまいます。

	  新しく確保しているのはメモリ領域の解放の時を考えての事です。
	  関数を呼び出した側が取得するポインタは
	  波形データの先頭を指すポインタです(WAVEHDR構造体のlpDataメンバ)。
	  当然、メモリ領域の解放にもこのポインタを使うでしょうが、
	  このポインタはメモリ領域の先頭を指していません。
	  メモリ領域の先頭を指していないポインタでメモリ領域を解放する事はできないのです。
	  もちろん関数の詳細を知っていれば先頭のアドレスを計算できますが、関数の使いやすさは大幅減です。

	  新しいメモリ領域には含まれない波形データのバイト数は
	  以前のメモリ領域を解放する前に保存しておく必要がある事に注意して下さい。
	  WAVEHDR構造体の dwBufferLength メンバの設定がまだ残っているからです。*/
	DWORD size = *(DWORD *)(lpBuf + offset - 4);
	BYTE *lpWave = (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
	CopyMemory(lpWave, lpBuf + offset, size);
	HeapFree(GetProcessHeap(), 0, lpBuf);

	/*WAVEHDR構造体の設定*/
	lpwhdr->lpData = (LPSTR)lpWave;
	lpwhdr->dwBufferLength = size;
	lpwhdr->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	lpwhdr->dwLoops = 1;

	return 0;
}

static void CloseWaveFile(HWAVEOUT hWaveOut, WAVEHDR *lpwhdr)
{
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, lpwhdr, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
	if (lpwhdr->lpData) {
		HeapFree(GetProcessHeap(), 0, lpwhdr->lpData);
		lpwhdr->lpData = nullptr;
	};
}

WSound *WSound::pwsTop = nullptr;

void WSound::LoopProc(WPARAM wParam, LPARAM lParam)
{
	for (auto it = pwsTop; it; it = it->next)
	{
		if (it->hCallBackWnd)
		{
			if (it->bIsPlaying)
			{
				if (it->hWaveOut == (HWAVEOUT)wParam && &it->wHdr == (WAVEHDR *)lParam)
				{
					it->Play();
				}
			}
		}
	}
}

WSound::WSound()
	:
	wFormatEx({}),
	wHdr({}),
	hWaveOut(nullptr),
	hCallBackWnd(nullptr),
	next(nullptr),
	prev(nullptr),
	bIsPlaying(false)
{
	if (pwsTop)
	{
		WSound *it = pwsTop;
		WSound *buf = pwsTop;
		while (it->next)
		{
			buf = it;
			it = it->next;
			if (it) it->prev = it;
		}
		it->next = this;
		return;
	}
	pwsTop = this;
}
WSound::~WSound()
{
	CloseWaveFile(hWaveOut, &wHdr);

	if (prev) prev->next = next;
	if (next) next->prev = prev;
}
bool WSound::CallBack(const char * const ccpWinName)
{
	return (hCallBackWnd = FindWindow(nullptr, ccpWinName)) == nullptr;
}
bool WSound::SoundCreate(const char * const ccpWaveFileName)
{
	if (LoadWavFile(ccpWaveFileName, &wFormatEx, &wHdr)) return 1;
	if (hCallBackWnd)
	{
		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wFormatEx, (DWORD)hCallBackWnd, 0, CALLBACK_WINDOW);
		return 0;
	}
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wFormatEx, (DWORD)nullptr, 0, CALLBACK_NULL);
	return 0;
}
void WSound::Release()
{
	CloseWaveFile(hWaveOut, &wHdr);
}
void WSound::Play()
{
	waveOutReset(hWaveOut);
	waveOutPrepareHeader(hWaveOut, &wHdr, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &wHdr, sizeof(WAVEHDR));
}
void WSound::PlayL()
{
	if (!bIsPlaying)
	{
		bIsPlaying = true;
		Play();
	}
}
void WSound::Pause()
{
	waveOutPause(hWaveOut);
}
void WSound::Restart()
{
	waveOutRestart(hWaveOut);
}
void WSound::Stop()
{
	bIsPlaying = false;
	waveOutReset(hWaveOut);
}

long JoyPad::lStickTolerance = 2000;

constexpr byte JoyPad::PADNUM_MAX;

JOYINFOEX JoyPad::joy_ex[PADNUM_MAX] = {};

std::vector<JoyPad *> JoyPad::instance;

byte JoyPad::inst_cnt = 0;

byte JoyPad::n_direct[PADNUM_MAX][J_DIR_MAX] = {};

byte JoyPad::n_buttons[PADNUM_MAX][J_BUT_MAX] = {};

byte JoyPad::p_direct[PADNUM_MAX][J_DIR_MAX] = {};

byte JoyPad::p_buttons[PADNUM_MAX][J_BUT_MAX] = {};

long JoyPad::axisx[PADNUM_MAX] = {};

long JoyPad::axisy[PADNUM_MAX] = {};
/*スティックのX軸の初期状態*/
unsigned long JoyPad::initaxisx[PADNUM_MAX] = {};
/*スティックのY軸の初期状態*/
unsigned long JoyPad::initaxisy[PADNUM_MAX] = {};

long JoyPad::Raxisx[PADNUM_MAX] = {};

long JoyPad::Raxisy[PADNUM_MAX] = {};
/*スティックのX軸の初期状態*/
unsigned long JoyPad::Rinitaxisx[PADNUM_MAX] = {};
/*スティックのY軸の初期状態*/
unsigned long JoyPad::Rinitaxisy[PADNUM_MAX] = {};

Vector2 JoyPad::vec2[2][PADNUM_MAX] = {};

JoyPad::JoyPad()
{
	joy_id = inst_cnt;

	instance.push_back(this);

	for (byte b = 0; b < 4; ++b)
	{
		n_direct[joy_id][b] = 0;
		n_buttons[joy_id][b] = 0;

		p_direct[joy_id][b] = 0;
		p_buttons[joy_id][b] = 0;
	}
	axisx[joy_id] = 0;
	axisy[joy_id] = 0;

	Raxisx[joy_id] = 0;
	Raxisy[joy_id] = 0;

	++inst_cnt;
}

bool JoyPad::Init(const long lTolerance)
{
	lStickTolerance = lTolerance;
	for (byte b = 0; b < PADNUM_MAX; ++b)
	{
		joy_ex[b].dwSize = sizeof(JOYINFOEX);
		joy_ex[b].dwFlags = JOY_RETURNALL;
		/*接続されていたら*/
		if (JOYERR_NOERROR == joyGetPosEx(b, &joy_ex[b]))
		{
			initaxisx[b] = joy_ex[b].dwXpos;
			initaxisy[b] = joy_ex[b].dwYpos;

			Rinitaxisx[b] = joy_ex[b].dwZpos;
			Rinitaxisy[b] = joy_ex[b].dwRpos;
		}
	}
	return 0;
}

bool JoyPad::GetStateAll()
{
	constexpr unsigned long table[10] = { JOY_BUTTON1,JOY_BUTTON2 ,JOY_BUTTON3 ,JOY_BUTTON4,JOY_BUTTON5,JOY_BUTTON6,JOY_BUTTON7,JOY_BUTTON8,JOY_BUTTON1CHG,JOY_BUTTON2CHG };
	/*接続されているJOYPADを検索*/
	for (byte b = 0; b < PADNUM_MAX; ++b)
	{
		/*接続されていたら*/
		if (JOYERR_NOERROR == joyGetPosEx(b, &joy_ex[b]))
		{
			/*前フレームの状態をコピー*/
			memcpy(p_buttons[b], n_buttons[b], sizeof(p_buttons[b]));
			memcpy(p_direct[b], n_direct[b], sizeof(p_direct[b]));

			/*情報を取得*/
			for (byte b2 = 0; b2 < 10; ++b2)
			{
				if (joy_ex[b].dwButtons & table[b2])
				{
					/*ボタンの押されているフレーム数をカウント*/
					++n_buttons[b][b2];
					if (n_buttons[b][b2] >= 255) n_buttons[b][b2] = 2;
				}
				else n_buttons[b][b2] = 0;
			}

			/*スティックもしくは方向キーが右なら*/
			if (joy_ex[b].dwXpos > initaxisx[b] + lStickTolerance)
			{
				axisx[b] = joy_ex[b].dwXpos - (initaxisx[b] + lStickTolerance);
				++n_direct[b][J_RIGHT];
				if (n_direct[b][J_RIGHT] >= 255) n_direct[b][J_RIGHT] = 2;
				n_direct[b][J_LEFT] = 0;
			}
			/*スティックもしくは方向キーが左なら*/
			else if (joy_ex[b].dwXpos < initaxisx[b] - lStickTolerance)
			{
				axisx[b] = joy_ex[b].dwXpos - (initaxisx[b] - lStickTolerance);
				++n_direct[b][J_LEFT];
				if (n_direct[b][J_LEFT] >= 255) n_direct[b][J_LEFT] = 2;
				n_direct[b][J_RIGHT] = 0;
			}
			/*ニュートラルなら*/
			else
			{
				axisx[b] = 0;
				n_direct[b][J_LEFT] = 0;
				n_direct[b][J_RIGHT] = 0;
			}

			/*スティックもしくは方向キーが上なら*/
			if (joy_ex[b].dwYpos < initaxisy[b] - lStickTolerance)
			{
				axisy[b] = joy_ex[b].dwYpos - (initaxisy[b] - lStickTolerance);
				++n_direct[b][J_UP];
				if (n_direct[b][J_UP] >= 255) n_direct[b][J_UP] = 2;
				n_direct[b][J_DOWN] = 0;
			}
			/*スティックもしくは方向キーが下なら*/
			else if (joy_ex[b].dwYpos > initaxisy[b] + lStickTolerance)
			{
				axisy[b] = joy_ex[b].dwYpos - (initaxisy[b] + lStickTolerance);
				++n_direct[b][J_DOWN];
				if (n_direct[b][J_DOWN] >= 255) n_direct[b][J_DOWN] = 2;
				n_direct[b][J_UP] = 0;
			}
			/*ニュートラルなら*/
			else
			{
				axisy[b] = 0;
				n_direct[b][J_UP] = 0;
				n_direct[b][J_DOWN] = 0;
			}

			/*スティックもしくは方向キーが右なら*/
			if (joy_ex[b].dwZpos > Rinitaxisx[b] + lStickTolerance)
			{
				Raxisx[b] = joy_ex[b].dwZpos - (Rinitaxisx[b] + lStickTolerance);
			}
			/*スティックもしくは方向キーが左なら*/
			else if (joy_ex[b].dwZpos < Rinitaxisx[b] - lStickTolerance)
			{
				Raxisx[b] = joy_ex[b].dwZpos - (Rinitaxisx[b] - lStickTolerance);
			}
			/*ニュートラルなら*/
			else
			{
				Raxisx[b] = 0;
			}

			/*スティックもしくは方向キーが上なら*/
			if (joy_ex[b].dwRpos < Rinitaxisy[b] - lStickTolerance)
			{
				Raxisy[b] = joy_ex[b].dwRpos - (Rinitaxisy[b] - lStickTolerance);
			}
			/*スティックもしくは方向キーが下なら*/
			else if (joy_ex[b].dwRpos > Rinitaxisy[b] + lStickTolerance)
			{
				Raxisy[b] = joy_ex[b].dwRpos - (Rinitaxisy[b] + lStickTolerance);
			}
			/*ニュートラルなら*/
			else
			{
				Raxisy[b] = 0;
			}

			vec2[0][b] = Vector2(float(axisx[b] / 3000) * .1f, float(axisy[b] / 3000) * .1f);
			vec2[1][b] = Vector2(float(Raxisx[b] / 3000) * .1f, float(Raxisy[b] / 3000) * .1f);
		}
	}
	return 0;
}

JoyPad *JoyPad::GetState(const byte id_)
{
	byte cnt = 0;
	for (const auto &i : instance)
	{
		if (cnt == id_) return i;
		++cnt;
	}
	return nullptr;
}

byte JoyPad::NowBut(const Joy_Button button_)
{
	return n_buttons[joy_id][button_];
}

byte JoyPad::NowDir(const Joy_Direct direct_)
{
	return n_direct[joy_id][direct_];
}

byte JoyPad::PreBut(const Joy_Button button_)
{
	return p_buttons[joy_id][button_];
}

byte JoyPad::PreDir(const Joy_Direct direct_)
{
	return p_direct[joy_id][direct_];
}

bool JoyPad::Down(const Joy_Button but_)
{
	return (!p_buttons[joy_id][but_] && n_buttons[joy_id][but_]);
}

bool JoyPad::On(const Joy_Button but_)
{
	return (p_buttons[joy_id][but_] && n_buttons[joy_id][but_]);
}

bool JoyPad::Up(const Joy_Button but_)
{
	return (p_buttons[joy_id][but_] && !n_buttons[joy_id][but_]);
}

bool JoyPad::Off(const Joy_Button but_)
{
	return (!p_buttons[joy_id][but_] && !n_buttons[joy_id][but_]);
}

bool JoyPad::Down(const Joy_Direct direct_)
{
	return (!p_direct[joy_id][direct_] && n_direct[joy_id][direct_]);
}

bool JoyPad::On(const Joy_Direct direct_)
{
	return (p_direct[joy_id][direct_] && n_direct[joy_id][direct_]);
}

bool JoyPad::Up(const Joy_Direct direct_)
{
	return (p_direct[joy_id][direct_] && !n_direct[joy_id][direct_]);
}

bool JoyPad::Off(const Joy_Direct direct_)
{
	return (!p_direct[joy_id][direct_] && !n_direct[joy_id][direct_]);
}
/*スティックのXY軸押し込み状態取得関数*/
const Vector2 &JoyPad::GetAxisL() const
{
	return vec2[0][joy_id];
}
float JoyPad::GetAxisL(const char * const axis_) const
{
	const std::string axis[2] = { "Horizontal","Vertical" };
	if (axis_ == axis[0])		return float(axisx[joy_id] / 3000) * .1f;
	else if (axis_ == axis[1])	return float(axisy[joy_id] / 3000) * .1f;
#ifdef _DEBUG
	std::string dbgtex = "スペルが違います \"";
	dbgtex += axis_;
	dbgtex += "\"";
	MessageBox(FindWindow("MyWindow", nullptr), dbgtex.c_str(), "", MB_OK | MB_ICONWARNING);
	PostQuitMessage(0);
#endif
	return 0;
}
/*ラジアンを取得関数*/
float JoyPad::GetRadL() const
{
	if (-float(axisx[joy_id] / 3000) * .1f || float(axisy[joy_id] / 3000) * .1f)
		return (float)atan2(-float(axisx[joy_id] / 3000) * .1f, float(axisy[joy_id] / 3000) * .1f);
	return 0;
}
/*ディグリーを取得関数*/
float JoyPad::GetDegL() const
{
	if (-float(axisx[joy_id] / 3000) * .1f || float(axisy[joy_id] / 3000) * .1f)
		return RtoD(atan2(-float(axisx[joy_id] / 3000) * .1f, float(axisy[joy_id] / 3000) * .1f));
	return 0;
}
/*スティックのXY軸押し込み状態取得関数*/
const Vector2 &JoyPad::GetAxisR() const
{
	return vec2[1][joy_id];
}
float JoyPad::GetAxisR(const char * const axis_) const
{
	const std::string axis[2] = { "Horizontal","Vertical" };
	if (axis_ == axis[0])		return float(Raxisx[joy_id] / 3000) * .1f;
	else if (axis_ == axis[1])	return float(Raxisy[joy_id] / 3000) * .1f;
#ifdef _DEBUG
	std::string dbgtex = "スペルが違います \"";
	dbgtex += axis_;
	dbgtex += "\"";
	MessageBox(FindWindow("MyWindow", nullptr), dbgtex.c_str(), "", MB_OK | MB_ICONWARNING);
	PostQuitMessage(0);
#endif
	return 0;
}
/*ラジアンを取得関数*/
float JoyPad::GetRadR() const
{
	if (-float(Raxisx[joy_id] / 3000) * .1f || float(Raxisy[joy_id] / 3000) * .1f)
		return (float)atan2(-float(Raxisx[joy_id] / 3000) * .1f, float(Raxisy[joy_id] / 3000) * .1f);
	return 0;
}
/*ディグリーを取得関数*/
float JoyPad::GetDegR() const
{
	if (-float(Raxisx[joy_id] / 3000) * .1f || float(Raxisy[joy_id] / 3000) * .1f)
		return RtoD(atan2(-float(Raxisx[joy_id] / 3000) * .1f, float(Raxisy[joy_id] / 3000) * .1f));
	return 0;
}

//スタティック変数の初期化
HDC Rec::off = nullptr;
HBITMAP Rec::hoffbmp = nullptr;
Frec Rec::Win = {};
Frec Rec::frZoom = {};
Point Rec::Cam = {};
Point Rec::pAdjust = {};

//矩形クラスに共通の描画バッファを作成
bool Rec::Init(HWND hWnd_)
{
	//if (off = hOff_) return 0;
	//return 1;
	RECT winrect;
	//
	GetClientRect(hWnd_, &winrect);

	Win.l = (float)winrect.left;
	Win.r = (float)winrect.right;
	Win.t = (float)winrect.top;
	Win.b = (float)winrect.bottom;

	frZoom.l = 0.f;
	frZoom.r = 1.f;
	frZoom.t = 0.f;
	frZoom.b = 1.f;

	Cam = Point(Win.r * 0.5f, Win.b * 0.5f);

	HDC hdc = GetDC(hWnd_);
	//
	off = CreateCompatibleDC(hdc);

	if (!off) return 1;

	hoffbmp = CreateCompatibleBitmap(hdc, int(Win.r), int(Win.b));
	//
	SelectObject(off, hoffbmp);

	//SetStretchBltMode(off, HALFTONE);
	return 0;
}
//オフスクリーンをリセットする関数
void Rec::ResetOff(const DWORD rop_)
{
	PatBlt(off, 0, 0, int(Win.r), int(Win.b), rop_);
}
//WM_PAINTメッセージ処理内でフロントスクリーンに描画
void Rec::DrawBackToFront(HDC hOn_)
{
	/**
	BitBlt(hOn_, 0, 0, int(Win.r), int(Win.b), off, 0, 0, SRCCOPY);
	/*/
	StretchBlt(hOn_, 0, 0, int(Win.r), int(Win.b), off, int(Win.l + frZoom.l), int(Win.t + frZoom.t), int(Win.r * frZoom.r), int(Win.b * frZoom.b), SRCCOPY);
	/**/
}
//オフスクリーンとビットマップを破棄
void Rec::Release()
{
	if (hoffbmp) DeleteObject(hoffbmp);
	if (off) DeleteDC(off);
}
//カメラの座標に合わせて位置を調整する
const Point &Rec::AdjustCamPos(const Point * const pPos)
{
	pAdjust.x = -(Cam.x - Win.r * 0.5f) + pPos->x;
	pAdjust.y = -(Cam.y - Win.b * 0.5f) + pPos->y;
	return pAdjust;
}
//カメラの座標を設定
void Rec::SetCameraPos(const Point * const pPos)
{
	Cam = *pPos;
}
//カメラの座標を取得
const Point &Rec::GetCameraPos()
{
	return Cam;
}
//カメラのX座標を取得
const float Rec::GetCameraPosX()
{
	return Cam.x;
}
//カメラのY座標を取得
const float Rec::GetCameraPosY()
{
	return Cam.y;
}
//画面を塗りつぶす
void Rec::FullPaint(const COLORREF ccColor)
{
	auto hBlush = CreateSolidBrush(ccColor);
	auto hOld = SelectObject(off, hBlush);
	Rectangle(off, 0, 0, (int)Win.r, (int)Win.b);
	SelectObject(off, hOld);
	DeleteObject(hBlush);
}
//カメラを移動
void Rec::MoveCamera(const Vector2 * const vMove)
{
	Cam.x += vMove->GetX();
	Cam.y += vMove->GetY();
}
//ズーム
void Rec::Zoom(const float fMagni)
{
	if (fMagni < 1.f) return;
	frZoom.r = 1.f / fMagni;
	frZoom.b = 1.f / fMagni;
	frZoom.l = (Win.r * (1.f - frZoom.r)) * 0.5f;
	frZoom.t = (Win.b * (1.f - frZoom.b)) * 0.5f;
}
//オフスクリーンのハンドルを取得
HDC Rec::GetOffScreenHandle()
{
	return off;
}
//コンストラクタ
Rec::Rec(const float cx_, const float cy_, const float w_, const float h_, float angleD_)
	:w(w_), h(h_), cColor(WHITE_COLOR)
{
	p[CENTER].x = cx_;
	p[CENTER].y = cy_;

	//原点で拡縮
	p[TOP_LEFT].x = -(w_ * 0.5f);
	p[TOP_LEFT].y = -(h_ * 0.5f);
	p[TOP_RIGHT].x = +(w_ * 0.5f);
	p[TOP_RIGHT].y = -(h_ * 0.5f);
	p[BOTTOM_LEFT].x = -(w_ * 0.5f);
	p[BOTTOM_LEFT].y = +(h_ * 0.5f);
	p[BOTTOM_RIGHT].x = +(w_ * 0.5f);
	p[BOTTOM_RIGHT].y = +(h_ * 0.5f);

	float bufx = p[TOP_LEFT].x - p[TOP_RIGHT].x;
	float bufy = p[TOP_LEFT].y - p[TOP_RIGHT].y;

	//dx = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
	dx = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

	bufx = p[TOP_LEFT].x - p[BOTTOM_LEFT].x;
	bufy = p[TOP_LEFT].y - p[BOTTOM_LEFT].y;

	//dy = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
	dy = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

	angle = angleD_;

	//原点を中心とした位置に移動
	float  pp[4][2] =
	{
		{ -dx , -dy },
		{  dx , -dy },
		{ -dx ,  dy },
		{  dx ,  dy },
	};

	//原点に合わせて回転
	const double ang = (double)DtoR(ModAngle(angleD_));
	for (int i = 0; i < POINT_MAX - 1; ++i)
	{
		p[i].x = float(cos_fast(ang) * pp[i][0] - sin_fast(ang) * pp[i][1]);
		p[i].y = float(sin_fast(ang) * pp[i][0] + cos_fast(ang) * pp[i][1]);

		//p[i].x = cos(DtoR(angle)) * pp[i][0] - sin(DtoR(angle)) * pp[i][1];
		//p[i].y = sin(DtoR(angle)) * pp[i][0] + cos(DtoR(angle)) * pp[i][1];
	}

	for (int i = 0; i < POINT_MAX - 1; ++i)
	{
		//原点に合わせておいたので元に戻す
		p[i].x += p[CENTER].x;
		p[i].y += p[CENTER].y;
	}
}
//コンストラクタ
Rec::Rec()
	:dx(0.f), dy(0.f), angle(0), w(0.f), h(0.f), cColor(WHITE_COLOR)
{
	for (int i = 0; i < POINT_MAX; ++i)
		p[i] = { 0.,0. };
}
//コピーコンストラクタ
Rec::Rec(const Rec & cpyrec_)
	:dx(cpyrec_.dx), dy(cpyrec_.dy), angle(cpyrec_.angle), w(cpyrec_.w), h(cpyrec_.h), cColor(cpyrec_.cColor)
{
	for (int i = 0; i < POINT_MAX; ++i)
		p[i] = cpyrec_.p[i];
}
//
const COLORREF Rec::SetColor(const COLORREF ccColor)
{
	auto cOld = cColor;
	cColor = ccColor;
	return cOld;
}
//矩形を移動させる
void Rec::SetPos(const Point * const pos_)
{
	//原点を中心とした位置に移動
	float  pp[4][2] =
	{
		{ -dx , -dy },
		{ dx , -dy },
		{ -dx ,  dy },
		{ dx ,  dy },
	};

	p[CENTER].x = pos_->x;
	p[CENTER].y = pos_->y;

	for (int i = 0; i < POINT_MAX - 1; ++i)
	{
		p[i].x = p[CENTER].x + pp[i][0];
		p[i].y = p[CENTER].y + pp[i][1];
	}
}
//
void Rec::Scaling(const float recw_, const float rech_)
{
	w = recw_;
	h = rech_;
	//原点で拡縮
	p[TOP_LEFT].x = -(recw_ * 0.5f);
	p[TOP_LEFT].y = -(rech_ * 0.5f);
	p[TOP_RIGHT].x = +(recw_ * 0.5f);
	p[TOP_RIGHT].y = -(rech_ * 0.5f);
	p[BOTTOM_LEFT].x = -(recw_ * 0.5f);
	p[BOTTOM_LEFT].y = +(rech_ * 0.5f);
	p[BOTTOM_RIGHT].x = +(recw_ * 0.5f);
	p[BOTTOM_RIGHT].y = +(rech_ * 0.5f);

	float bufx = p[TOP_LEFT].x - p[TOP_RIGHT].x;
	float bufy = p[TOP_LEFT].y - p[TOP_RIGHT].y;

	//dx = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
	dx = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

	bufx = p[TOP_LEFT].x - p[BOTTOM_LEFT].x;
	bufy = p[TOP_LEFT].y - p[BOTTOM_LEFT].y;

	//dy = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
	dy = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

	double ang = (double)ModAngle(angle);
	if (ang < -1.f || ang > 1.f)
	{
		//原点を中心とした位置に移動
		float  pp[4][2] =
		{
			{ -dx , -dy },
			{  dx , -dy },
			{ -dx ,  dy },
			{  dx ,  dy },
		};
		ang = (double)DtoR((float)ang);
		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			p[i].x = float(cos_fast(ang) * pp[i][0] - sin_fast(ang) * pp[i][1]);
			p[i].y = float(sin_fast(ang) * pp[i][0] + cos_fast(ang) * pp[i][1]);

			//p[i].x = cos(DtoR(angle)) * pp[i][0] - sin(DtoR(angle)) * pp[i][1];
			//p[i].y = sin(DtoR(angle)) * pp[i][0] + cos(DtoR(angle)) * pp[i][1];
		}
	}
	for (int i = 0; i < POINT_MAX - 1; ++i)
	{
		//原点に合わせておいたので元に戻す
		p[i].x += p[CENTER].x;
		p[i].y += p[CENTER].y;
	}
}
//
void Rec::SetDeg(const float angleD_)
{
	angle = angleD_;

	//原点を中心とした位置に移動
	float  pp[4][2] =
	{
		{ -dx , -dy },
		{  dx , -dy },
		{ -dx ,  dy },
		{  dx ,  dy },
	};

	//原点に合わせて回転
	double ang = (double)ModAngle(angle);
	if (ang < -1.f || ang > 1.f)
	{
		ang = (double)DtoR((float)ang);
		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			p[i].x = float(cos_fast(ang) * pp[i][0] - sin_fast(ang) * pp[i][1]);
			p[i].y = float(sin_fast(ang) * pp[i][0] + cos_fast(ang) * pp[i][1]);

			//p[i].x = cos(DtoR(angle)) * pp[i][0] - sin(DtoR(angle)) * pp[i][1];
			//p[i].y = sin(DtoR(angle)) * pp[i][0] + cos(DtoR(angle)) * pp[i][1];
		}

		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			//原点に合わせておいたので元に戻す
			p[i].x += p[CENTER].x;
			p[i].y += p[CENTER].y;
		}
	}
}
//
float Rec::GetDeg() const
{
	return angle;
}
//読み込んでおいたビットマップを描画(回転も可)
void Rec::Draw(Image * const mybitmap_, const bool rot_)
{
	if (AdjustCamPos(&p[CENTER]).x - w > Win.r) return;
	if (AdjustCamPos(&p[CENTER]).y - h > Win.b) return;
	if (AdjustCamPos(&p[CENTER]).x + w < Win.l) return;
	if (AdjustCamPos(&p[CENTER]).y + h < Win.t) return;

	POINT dp[3] = {};
	for (int i = 0; i < 3; ++i)
	{
		dp[i].x = (long)AdjustCamPos(&p[i]).x;
		dp[i].y = (long)AdjustCamPos(&p[i]).y;
	}

	if (rot_)
	{
		//回転と平行移動と拡縮に合わせて描画
		const float ang = ModAngle(angle);
		if ((ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
		{
			//原点を中心とした位置に移動
			float  pp[3][2] =
			{
				{ -dx , -dy },
				{ dx , -dy },
				{ -dx ,  dy },
			};

			for (int i = 0; i < 3; ++i)
			{
				pp[i][0] += AdjustCamPos(&p[CENTER]).x;
				pp[i][1] += AdjustCamPos(&p[CENTER]).y;
			}

			for (int i = 0; i < 3; ++i)
			{
				dp[i].x = (long)pp[i][0];
				dp[i].y = (long)pp[i][1];
			}
			/**/
			PlgBlt(off, dp, mybitmap_->GetImageHandle(), mybitmap_->GetBmpInfo().bmWidth / 2, 0, mybitmap_->GetBmpInfo().bmWidth / 2, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), mybitmap_->GetBmpInfo().bmWidth / 2, 0);
			/**/
		}
		else/**/ PlgBlt(off, dp, mybitmap_->GetImageHandle(), 0, 0, mybitmap_->GetBmpInfo().bmWidth / 2, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), 0, 0);
	}
	else PlgBlt(off, dp, mybitmap_->GetImageHandle(), 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), 0, 0);
}
//読み込んでおいたビットマップを描画(回転も可)
void Rec::Draw(Image * const mybitmap_, const Frec * const frSrc, const bool rot_)
{
	if (AdjustCamPos(&p[CENTER]).x - w > Win.r) return;
	if (AdjustCamPos(&p[CENTER]).y - h > Win.b) return;
	if (AdjustCamPos(&p[CENTER]).x + w < Win.l) return;
	if (AdjustCamPos(&p[CENTER]).y + h < Win.t) return;

	POINT dp[3];
	for (int i = 0; i < 3; ++i)
	{
		dp[i].x = (long)AdjustCamPos(&p[i]).x;
		dp[i].y = (long)AdjustCamPos(&p[i]).y;
	}

	if (rot_)
	{
		//回転と平行移動と拡縮に合わせて描画
		//180度に近いときだけ回転用バッファを使用
		const float ang = ModAngle(angle);
		if ((ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
		{
			//原点を中心とした位置に移動
			float  pp[3][2] =
			{
				{ -dx , -dy },
				{ dx , -dy },
				{ -dx ,  dy },
			};

			for (int i = 0; i < 3; ++i)
			{
				pp[i][0] += AdjustCamPos(&p[CENTER]).x;
				pp[i][1] += AdjustCamPos(&p[CENTER]).y;
			}

			for (int i = 0; i < 3; ++i)
			{
				dp[i].x = (long)pp[i][0];
				dp[i].y = (long)pp[i][1];
			}
			/**/
			PlgBlt(off, dp, mybitmap_->GetImageHandle(), int(frSrc->l + frSrc->r), (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), int(frSrc->l + frSrc->r), (int)frSrc->t);
			/**/
		}
		else PlgBlt(off, dp, mybitmap_->GetImageHandle(), (int)frSrc->l, (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), (int)frSrc->l, (int)frSrc->t);
	}
	else PlgBlt(off, dp, mybitmap_->GetImageHandle(), (int)frSrc->l, (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), (int)frSrc->l, (int)frSrc->t);
}
//
void Rec::DrawAlpha(Image * const mybitmap_, byte alpha_)
{
	POINT dp;
	dp.x = (long)AdjustCamPos(&p[TOP_LEFT]).x;
	dp.y = (long)AdjustCamPos(&p[TOP_LEFT]).y;

	if (dp.x - w > Win.r) return;
	if (dp.y - h > Win.b) return;
	if (dp.x + w < Win.l) return;
	if (dp.y + h < Win.t) return;

	BLENDFUNCTION bfu = {};
	bfu.BlendOp = AC_SRC_OVER;
	bfu.SourceConstantAlpha = alpha_;

	auto hBufDc = CreateCompatibleDC(off);
	auto hBufBmp = CreateCompatibleBitmap(off, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight);
	SelectObject(hBufDc, hBufBmp);

	POINT pBufArr[3] =
	{
		{0, 0},
		{mybitmap_->GetBmpInfo().bmWidth, 0},
		{0, mybitmap_->GetBmpInfo().bmHeight},
	};

	PlgBlt(hBufDc, pBufArr, off, dp.x, dp.y, (int)w, (int)h, nullptr, 0, 0);

	PlgBlt(hBufDc, pBufArr, mybitmap_->GetImageHandle(), 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), 0, 0);

	AlphaBlend(off, dp.x, dp.y, (int)w, (int)h, hBufDc, 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, bfu);

	DeleteObject(hBufBmp);
	DeleteDC(hBufDc);
}
//
void Rec::DrawAlpha(Image * const mybitmap_, const Frec * const frSrc, byte alpha_)
{
	POINT dp;
	dp.x = (long)AdjustCamPos(&p[TOP_LEFT]).x;
	dp.y = (long)AdjustCamPos(&p[TOP_LEFT]).y;

	if (dp.x - w > Win.r) return;
	if (dp.y - h > Win.b) return;
	if (dp.x + w < Win.l) return;
	if (dp.y + h < Win.t) return;

	BLENDFUNCTION bfu = {};
	bfu.BlendOp = AC_SRC_OVER;
	bfu.SourceConstantAlpha = alpha_;

	auto hBufDc = CreateCompatibleDC(off);
	auto hBufBmp = CreateCompatibleBitmap(off, (int)w, (int)h);
	SelectObject(hBufDc, hBufBmp);

	POINT pBufArr[3] =
	{
		{0, 0},
		{(int)w, 0},
		{0, (int)h},
	};

	PlgBlt(hBufDc, pBufArr, off, dp.x, dp.y, (int)w, (int)h, nullptr, 0, 0);

	PlgBlt(hBufDc, pBufArr, mybitmap_->GetImageHandle(), (int)frSrc->l, (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), (int)frSrc->l, (int)frSrc->t);

	AlphaBlend(off, dp.x, dp.y, (int)w, (int)h, hBufDc, 0, 0, (int)w, (int)h, bfu);

	DeleteObject(hBufBmp);
	DeleteDC(hBufDc);
}
//矩形の外枠を描画するメンバ関数
void Rec::Draw()
{
	if (AdjustCamPos(&p[CENTER]).x - w > Win.r) return;
	if (AdjustCamPos(&p[CENTER]).y - h > Win.b) return;
	if (AdjustCamPos(&p[CENTER]).x + w < Win.l) return;
	if (AdjustCamPos(&p[CENTER]).y + h < Win.t) return;

	POINT dp[5];
	for (int i = 0; i < 4; ++i)
	{
		dp[i].x = (long)AdjustCamPos(&p[i]).x;
		dp[i].y = (long)AdjustCamPos(&p[i]).y;
	}

	Swap(dp[BOTTOM_LEFT].x, dp[BOTTOM_RIGHT].x);
	Swap(dp[BOTTOM_LEFT].y, dp[BOTTOM_RIGHT].y);

	dp[4] = dp[TOP_LEFT];

	HPEN hPen = CreatePen(PS_SOLID, 0, cColor);
	HGDIOBJ old = SelectObject(off, hPen);

	Polyline(off, dp, sizeof(dp) / sizeof(dp[0]));

	SelectObject(off, old);
	DeleteObject(hPen);
}
//
constexpr bool LineCheckCross(const float ax, const float ay, const float bx, const float by, const float cx, const float cy, const float dx, const float dy)
{
	float ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
	float tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
	float tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
	float td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);

	return tc * td < 0.f && ta * tb < 0.f;
};
bool Rec::CheckHit(const Rec * const rec_)
{
	const float ang = ModAngle(angle);
	if ((ang >= -1 && ang <= 1) || (ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
	{
		return (p[TOP_LEFT].x < rec_->p[TOP_RIGHT].x && p[TOP_RIGHT].x > rec_->p[TOP_LEFT].x &&
			p[TOP_LEFT].y < rec_->p[BOTTOM_LEFT].y && p[BOTTOM_LEFT].y > rec_->p[TOP_LEFT].y);
	}

	if (
		CheckHit(rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||
		CheckHit(rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
		CheckHit(rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
		CheckHit(rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y)
		)
	{
		return 1;
	}

	if (
		LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
		LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
		LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
		LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||

		LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
		LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
		LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
		LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||

		LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
		LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
		LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
		LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||

		LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
		LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
		LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
		LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y)
		)
	{
		return 1;
	}
	return 0;
}
bool Rec::CheckHit(const Point * const pos_)
{
	double ang = (double)ModAngle(angle);
	if ((ang >= -1 && ang <= 1) || (ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
	{
		return (pos_->x > p[TOP_LEFT].x && pos_->x < p[TOP_RIGHT].x &&
			pos_->y > p[TOP_LEFT].y && pos_->y < p[BOTTOM_LEFT].y);
	}
	ang = (double)DtoR((float)ang);
	float dist = GetDist(pos_->x, pos_->y);
	Point pp = { pos_->x - p[CENTER].x,pos_->y - p[CENTER].y };
	double r1 = 0., r2 = 0.;
	if (pp.x != 0.f)
	{
		r1 = (double)atan(pp.y / pp.x);
	}
	else r1 = (double)DtoR(ModAngle(360.f));
	r2 = r1 - ang;

	pp = { dist * (float)cos_fast(r2),dist * (float)sin_fast(r2) };
	//pp = { dist * cos(r2),dist * sin(r2) };

	pp.x += p[CENTER].x;
	pp.y += p[CENTER].y;

	return(
		p[CENTER].x - dx <= pp.x && pp.x <= p[CENTER].x + dx &&
		p[CENTER].y - dy <= pp.y && pp.y <= p[CENTER].y + dy
		);
}
bool Rec::CheckHit(const float x_, const float y_)
{
	double ang = (double)ModAngle(angle);
	if ((ang >= -1 && ang <= 1) || (ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
	{
		return (x_ > p[TOP_LEFT].x && x_ < p[TOP_RIGHT].x &&
			y_ > p[TOP_LEFT].y && y_ < p[BOTTOM_LEFT].y);
	}
	ang = (double)DtoR((float)ang);
	float dist = GetDist(x_, y_);
	Point pp = { x_ - p[CENTER].x,y_ - p[CENTER].y };
	double r1 = 0., r2 = 0.;
	if (pp.x != 0.f)
	{
		r1 = (double)atan(pp.y / pp.x);
	}
	else r1 = (double)DtoR(ModAngle(360.f));

	r2 = r1 - ang;

	pp = { dist * (float)cos_fast(r2),dist * (float)sin_fast(r2) };
	//pp = { dist * cos(r2),dist * sin(r2) };

	pp.x += p[CENTER].x;
	pp.y += p[CENTER].y;

	return(
		p[CENTER].x - dx <= pp.x && pp.x <= p[CENTER].x + dx &&
		p[CENTER].y - dy <= pp.y && pp.y <= p[CENTER].y + dy
		);
}
//
bool Rec::CheckHitLeft(const Rec * const rec_)
{
	return CheckHit(rec_) && p[CENTER].x > rec_->p[CENTER].x;
}
//
bool Rec::CheckHitRight(const Rec * const rec_)
{
	return CheckHit(rec_) && p[CENTER].x < rec_->p[CENTER].x;
}
//
bool Rec::CheckHitTop(const Rec * const rec_)
{
	return CheckHit(rec_) && p[CENTER].y > rec_->p[CENTER].y;
}
//
bool Rec::CheckHitBottom(const Rec * const rec_)
{
	return CheckHit(rec_) && p[CENTER].y < rec_->p[CENTER].y;
}
//
float Rec::GetW() const
{
	return w;
}
//
float Rec::GetH() const
{
	return h;
}
//指定座標との角度(ラジアン)を取得するメンバ関数
float Rec::GetRad(const float x_, const float y_) const
{
	return atan2(y_ - p[CENTER].y, x_ - p[CENTER].x);
}
//別の矩形との角度(ラジアン)を取得するメンバ関数
float Rec::GetRad(const Rec * const rec_) const
{
	return atan2(rec_->p[CENTER].y - p[CENTER].y, rec_->p[CENTER].x - p[CENTER].x);
}
//指定座標との角度(ディグリー)を取得するメンバ関数
float Rec::GetDeg(const float x_, const float y_) const
{
	return RtoD(atan2(y_ - p[CENTER].y, x_ - p[CENTER].x));
}
//指定座標との角度(ディグリー)を取得するメンバ関数
float Rec::GetDeg(const Point * const pos_) const
{
	return RtoD(atan2(pos_->y - p[CENTER].y, pos_->x - p[CENTER].x));
}
//別の矩形との角度(ディグリー)を取得するメンバ関数
float Rec::GetDeg(const Rec * const rec_) const
{
	return RtoD(atan2(rec_->p[CENTER].y - p[CENTER].y, rec_->p[CENTER].x - p[CENTER].x));
}
//矩形を移動させる
void Rec::Move(const Vector2 * const vec2_)
{
	for (int i = 0; i < POINT_MAX; ++i)
	{
		p[i].x += vec2_->GetX();
		p[i].y += vec2_->GetY();
	}
}
//
float Rec::GetDist(const float x_, const float y_) const
{
	float dx = p[CENTER].x - x_;
	float dy = p[CENTER].y - y_;
	//return (float)Sqrt((unsigned long)(dx * dx + dy * dy));
	return Sqrt(dx * dx + dy * dy);
}
//点との距離を取得するメンバ関数
float Rec::GetDist(const Point * const pos_) const
{
	float dx = p[CENTER].x - pos_->x;
	float dy = p[CENTER].y - pos_->y;
	//return (float)Sqrt((unsigned long)(dx * dx + dy * dy));
	return Sqrt(dx * dx + dy * dy);
}
//別の矩形との距離を取得するメンバ関数
float Rec::GetDist(const Rec * const rec_) const
{
	float dx = p[CENTER].x - rec_->p[CENTER].x;
	float dy = p[CENTER].y - rec_->p[CENTER].y;
	//return (float)Sqrt((unsigned long)(dx * dx + dy * dy));
	return Sqrt(dx * dx + dy * dy);
}
//
const Point &Rec::GetPos() const
{
	return p[CENTER];
}
//矩形の中心点のX座標
float Rec::GetPosX() const
{
	return p[CENTER].x;
}
//矩形の中心点のY座標
float Rec::GetPosY() const
{
	return p[CENTER].y;
}
//矩形の左上の座標を取得
const Point &Rec::GetTL() const
{
	return p[TOP_LEFT];
}
//矩形の右上の座標を取得
const Point &Rec::GetTR() const
{
	return p[TOP_RIGHT];
}
//矩形の左下の座標を取得
const Point &Rec::GetBL() const
{
	return p[BOTTOM_LEFT];
}
//矩形の右下の座標を取得
const Point &Rec::GetBR() const
{
	return p[BOTTOM_RIGHT];
}
//現在のサイズが（0, 0）かどうか
const bool Rec::Zero() const
{
	return (!w && !h);
}

/*円クラス*/
/*コンストラクタ*/
Circle::Circle()
	: hPen(nullptr), hOff(Rec::GetOffScreenHandle()), color(WHITE_COLOR), center({ 0.f,0.f }), radius(1.f)
{

}
/*コンストラクタ*/
Circle::Circle(const Point * const position_, const float radius_)
	: hPen(nullptr), hOff(Rec::GetOffScreenHandle()), color(WHITE_COLOR), center(*position_), radius(radius_)
{

}
/*中心座標設定*/
void Circle::SetPos(const Point * const pos_)
{
	center = *pos_;
}
/*半径設定*/
void Circle::SetRadius(const float radius_)
{
	radius = radius_;
}
/*色設定*/
void Circle::SetColor(const byte r_, const byte g_, const byte b_)
{
	//color = r_ | (unsigned short)g_ << 8 | (unsigned long)b_ << 16;
	color = RGB(r_, g_, b_);
}
/*座標取得*/
const Point &Circle::GetPos() const
{
	return center;
}
/*X座標取得*/
const float Circle::GetPosX() const
{
	return center.x;
}
/*Y座標取得*/
const float Circle::GetPosY() const
{
	return center.y;
}
/*半径取得*/
const float Circle::GetRadius() const
{
	return radius;
}
/*描画*/
void Circle::Draw()
{
	Point dp = Rec::AdjustCamPos(&center);
	if (dp.x - radius > Rec::Win.r) return;
	if (dp.y - radius > Rec::Win.b) return;
	if (dp.x + radius < Rec::Win.l) return;
	if (dp.x + radius < Rec::Win.t) return;

	/*描画用ペンを作成*/
	hPen = CreatePen(PS_INSIDEFRAME, 1, color);
	/*offがペンを使うようにする*/
	HGDIOBJ hOldPen = SelectObject(hOff, hPen);
	HGDIOBJ hOldBlush = SelectObject(hOff, GetStockObject(NULL_BRUSH));

	/*円の描画開始*/
	Ellipse(hOff, int(dp.x - radius), int(dp.y - radius), int(dp.x + radius), int(dp.y + radius));

	/*offが使う描画オブジェクトを元に戻す*/
	SelectObject(hOff, hOldPen);
	SelectObject(hOff, hOldBlush);
	/*ペンを破棄*/
	DeleteObject(hPen);
	hPen = nullptr;
}
/*当たり判定*/
const bool Circle::CheckHit(const Circle * const circle_) const
{
	/*半径の合計*/
	float dist = this->radius + circle_->radius;
	/*中心同士のX軸上の距離*/
	float distx = this->center.x - circle_->center.x;
	/*中心同士のY軸上の距離*/
	float disty = this->center.y - circle_->center.y;
	/*半径よりも中心点同士の距離が短かったら　true　*/
	return ((dist * dist) > (distx * distx + disty * disty));
}
/*当たり判定*/
const bool Circle::CheckHit(const Point * const point_) const
{
	/*中心から点までのX軸上の距離*/
	float distx = center.x - point_->x;
	/*中心から点までのY軸上の距離*/
	float disty = center.y - point_->y;
	/*半径よりも点までの距離が短かったら　true　*/
	return ((radius * radius) > (distx * distx + disty * disty));
}

/*線クラス*/
/*コンストラクタ*/
Line::Line()
	:
	hPen(nullptr),
	hOff(Rec::GetOffScreenHandle()),
	color(WHITE_COLOR),
	spos({ 0.f, 0.f }),
	epos({ 1.f, 0.f }),
	width(1)
{
	const float dx = epos.x - spos.x;
	const float dy = epos.y - epos.y;

	angle = RtoD(atan2(dy, dx));

	len = Sqrt(dx * dx + dy * dy);

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*コンストラクタ*/
Line::Line(const Point * const spos_, const Point * const epos_)
	:
	hPen(nullptr),
	hOff(Rec::GetOffScreenHandle()),
	color(WHITE_COLOR),
	spos(*spos_),
	epos(*epos_),
	width(1)
{
	const float dx = epos.x - spos.x;
	const float dy = epos.y - epos.y;

	angle = RtoD((float)atan2(dx, dy)) - 90;

	len = Sqrt(dx * dx + dy * dy);

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*始点設定*/
void Line::SetPos(const Point * const spos_)
{
	epos = Point(epos.x - spos.x, epos.y - spos.y);
	spos = *spos_;

	epos.x += spos_->x;
	epos.y += spos_->y;
}
/*始点と終点設定*/
void Line::SetPos(const Point * const spos_, const Point * const epos_)
{
	spos = *spos_;
	epos = *epos_;

	const float dx = epos.x - spos.x;
	const float dy = epos.y - epos.y;

	angle = RtoD(atan2(dy, dx));

	len = Sqrt(dx * dx + dy * dy);

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*始点と終点設定*/
void Line::SetPos(const Point * const spos_, const float angleD_, const float len_)
{
	spos = *spos_;

	angle = angleD_;

	len = len_;

	const float ang = DtoR(ModAngle(angle));
	epos = Point((float)cos_fast(ang) * len, (float)sin_fast(ang) * len);

	//epos = Point(cos(DtoR(angle)) * len, sin(DtoR(angle)) * len);

	epos.x += spos.x;
	epos.y += spos.y;

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*始点設定*/
void Line::SetSPos(const Point * const spos_)
{
	spos = *spos_;

	const float dx = epos.x - spos.x;
	const float dy = epos.y - epos.y;

	angle = RtoD(atan2(dy, dx));

	len = Sqrt(dx * dx + dy * dy);

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*終点設定*/
void Line::SetEPos(const Point * const epos_)
{
	epos = *epos_;

	const float dx = epos.x - spos.x;
	const float dy = epos.y - epos.y;

	angle = RtoD(atan2(dy, dx));

	len = Sqrt(dx * dx + dy * dy);

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*色設定*/
void Line::SetColor(const byte r_, const byte g_, const byte b_)
{
	color = RGB(r_, g_, b_);
}
/*幅設定*/
void Line::SetWidth(const int width_)
{
	width = width_;
}
/*角度設定*/
void Line::SetDeg(const float angleD_)
{
	angle = angleD_;

	const float ang = DtoR(ModAngle(angle));
	epos = Point((float)cos_fast(ang) * len, (float)sin_fast(ang) * len);

	//epos = Point(cos(DtoR(angle)) * len, sin(DtoR(angle)) * len);

	epos.x += spos.x;
	epos.y += spos.y;

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*長さ設定*/
void Line::SetLen(const float len_)
{
	len = len_;
	if (len_)
	{
		const float ang = DtoR(ModAngle(angle));
		epos = Point((float)cos_fast(ang) * len_, (float)sin_fast(ang) * len_);

		//epos = Point(cos(DtoR(angle)) * len_, sin(DtoR(angle)) * len_);

		epos.x += spos.x;
		epos.y += spos.y;
	}
	else
	{
		epos = spos;
	}

	vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
}
/*始点取得*/
const Point &Line::GetSPos() const
{
	return spos;
}
/*終点取得*/
const Point &Line::GetEPos() const
{
	return epos;
}
/*角度取得*/
float Line::GetDeg() const
{
	return angle;
}
/*角度取得*/
float Line::GetDeg(const Line * const line_) const
{
	return RtoD(atan2(line_->spos.y - spos.y, line_->spos.x - spos.x));
}
/*角度取得*/
float Line::GetDeg(const Rec * const rec_) const
{
	return RtoD(atan2(rec_->GetPosY() - spos.y, rec_->GetPosX() - spos.x));
}
/*角度取得*/
float Line::GetDeg(const Point * const pos_) const
{
	return RtoD(atan2(pos_->y - spos.y, pos_->x - spos.x));
}
/*長さ取得*/
float Line::GetLen() const
{
	return len;
}
/*距離取得*/
float Line::GetDist(const Circle * const circle_) const
{
	const float dx = spos.x - circle_->GetPos().x;
	const float dy = spos.y - circle_->GetPos().y;

	return Sqrt(dx * dx + dy * dy);
}
/*距離取得*/
float Line::GetDist(const Point * const pos_) const
{
	const float dx = spos.x - pos_->x;
	const float dy = spos.y - pos_->y;

	return Sqrt(dx * dx + dy * dy);
}
/*ベクトル取得*/
const Vector2 &Line::GetVec() const
{
	return vec2;
}
/*線と円の交点を取得*/
const Point &Line::GetPOI(const Circle * const circle_)
{
	double xyr[3] = { circle_->GetPos().x, circle_->GetPos().y, circle_->GetRadius() };
	double pt1[2] = { spos.x, spos.y };
	double pt2[2] = { epos.x, epos.y };
	double xy[2] = {};
	if (lncl(pt1, pt2, xyr, pt1, xy) < 0)
	{
		inter = Point();
		return inter;
	}
	inter = Point((float)*(xy + 0), (float)*(xy + 1));
	return inter;
}
/*線と線の交点を取得*/
const Point &Line::GetPOI(const Line * const line_)
{
	double line1[2][2] =
	{
		{ spos.x, spos.y },
		{ epos.x, epos.y }
	};
	double line2[2][2] =
	{
		{ line_->spos.x, line_->spos.y },
		{ line_->epos.x, line_->epos.y }
	};
	double xy[2] = {};
	if (lnln(line1, line2, xy))
	{
		inter = Point();
		return inter;
	}
	inter = Point((float)*(xy + 0), (float)*(xy + 1));
	return inter;
}
/*移動*/
void Line::Move(const float movespd_)
{
	const double ang = (double)DtoR(ModAngle(angle));
	spos.x += (float)cos_fast(ang) * movespd_;
	spos.y += (float)sin_fast(ang) * movespd_;

	epos.x += (float)cos_fast(ang) * movespd_;
	epos.y += (float)sin_fast(ang) * movespd_;

	//spos.x += cos(DtoR(angle)) * movespd_;
	//spos.y += sin(DtoR(angle)) * movespd_;

	//epos.x += cos(DtoR(angle)) * movespd_;
	//epos.y += sin(DtoR(angle)) * movespd_;
}
/*描画*/
void Line::Draw()
{
	const Point pS = Rec::AdjustCamPos(&spos);
	const Point pE = Rec::AdjustCamPos(&epos);
	if (pS.x > Rec::Win.r && pE.x > Rec::Win.r) return;
	if (pS.y > Rec::Win.b && pE.y > Rec::Win.b) return;
	if (pS.x < Rec::Win.l && pE.x < Rec::Win.l) return;
	if (pS.y < Rec::Win.t && pE.y < Rec::Win.t) return;

	hPen = CreatePen(PS_SOLID, width, color);
	HGDIOBJ old = SelectObject(hOff, hPen);

	MoveToEx(hOff, (int)pS.x, (int)pS.y, nullptr);
	LineTo(hOff, (int)pE.x, (int)pE.y);

	SelectObject(hOff, old);
	DeleteObject(hPen);
}
/*当たり判定*/
bool Line::CheckHit(const Line * const line_)
{
	return LineCheckCross(spos.x, spos.y, epos.x, epos.y, line_->spos.x, line_->spos.y, line_->epos.x, line_->epos.y);
}
/*当たり判定*/
bool Line::CheckHit(const Rec * const rec_)
{
	return
		(
			LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetTL().x, rec_->GetTL().y, rec_->GetTR().x, rec_->GetTR().y) ||
			LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetTR().x, rec_->GetTR().y, rec_->GetBR().x, rec_->GetBR().y) ||
			LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetBR().x, rec_->GetBR().y, rec_->GetBL().x, rec_->GetBL().y) ||
			LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetBL().x, rec_->GetBL().y, rec_->GetTL().x, rec_->GetTL().y)
			);
}
/*当たり判定*/
bool Line::CheckHit(const Circle * const circle_)
{
	Vector2 vecA(circle_->GetPos().x - spos.x, circle_->GetPos().y - spos.y);
	Vector2 vecB(circle_->GetPos().x - epos.x, circle_->GetPos().y - epos.y);
	const float d = abs(vec2.Cross(&vecA) / vec2.GetLen());
	if (d > circle_->GetRadius()) return 0;
	if ((vecA.Dot(&vec2) * vecB.Dot(&vec2)) <= 0.f)
	{
		return 1;
	}
	else if (circle_->GetRadius() > vecA.GetLen() || circle_->GetRadius() > vecB.GetLen())
	{
		return 1;
	}
	return 0;
}

//
//コンストラクタ
FileIO::FileIO()
	:fp(nullptr)
{
}
//デストラクタ
FileIO::~FileIO()
{
	if (fp)
	{
		fclose(fp);
		fp = nullptr;
	}
}
//
bool FileIO::SaveFile(const void * const buf_, const int elementsize_)
{
	if (fp == nullptr)
		return 1;
	fwrite(buf_, elementsize_, 1, fp);
	return 0;
}
//
bool FileIO::LoadFile(void * const buf_, const int elementsize_)
{
	if (fp == nullptr)
		return 1;
	fread(buf_, elementsize_, 1, fp);
	return 0;
}
//
bool FileIO::Open(const char *filename_, const char *format_)
{
	fopen_s(&fp, filename_, format_);
	if (!fp) return 0;
	return 1;
}
//
bool FileIO::Close()
{
	if (!fp) return 0;
	fclose(fp);
	fp = nullptr;
	return 1;
}

//タイマークラス
//
Timer::Timer(const int interval_)
	:active(false), interval(interval_), cnt(0)
{

}
//
Timer::Timer()
	: active(false), interval(0), cnt(0)
{

}
//
void Timer::Set(const int interval_)
{
	interval = interval_;
}
//
void Timer::Start()
{
	active = true;
}
//
bool Timer::Tick()
{
	if (active)
	{
		if (++cnt == interval)
		{
			cnt ^= cnt;
			return 1;
		}
	}
	return 0;
}
//
void Timer::Stop()
{
	active = false;
}

Pixel::Pixel()
	:
	pPos({}),
	cColor(0),
	hOff(Rec::GetOffScreenHandle()),
	bSize(3)
{
}
Pixel::Pixel(const Point &crefpPos, const COLORREF ccColor, const byte cbSize)
	:
	pPos(crefpPos),
	cColor(ccColor),
	hOff(Rec::GetOffScreenHandle()),
	bSize(cbSize)
{
}
Pixel::Pixel(const Pixel &crefPixel)
	:
	pPos(crefPixel.pPos),
	cColor(crefPixel.cColor),
	hOff(Rec::GetOffScreenHandle()),
	hPen(CreatePen(PS_SOLID, 1, cColor)),
	hBrush(CreateSolidBrush(cColor)),
	bSize(crefPixel.bSize)
{
}
Pixel::~Pixel()
{
	if (hPen) DeleteObject(hPen);
	if (hBrush) DeleteObject(hBrush);
}
const Point Pixel::SetPos(const Point * const cppPos)
{
	const Point cpOld = pPos;
	pPos = *cppPos;
	return cpOld;
}
const COLORREF Pixel::SetColor(const COLORREF ccColor)
{
	const COLORREF ccOld = cColor;
	cColor = ccColor;
	if (hPen) DeleteObject(hPen);
	if (hBrush) DeleteObject(hBrush);
	hPen = CreatePen(PS_SOLID, 1, cColor);
	hBrush = CreateSolidBrush(cColor);
	return ccOld;
}
const byte Pixel::SetSize(const byte cbSize)
{
	const byte cbOld = bSize;
	bSize = cbSize;
	return cbOld;
}
const Point &Pixel::GetPos() const
{
	return pPos;
}
const float Pixel::GetPosX() const
{
	return pPos.x;
}
const float Pixel::GetPosY() const
{
	return pPos.y;
}
void Pixel::Draw() const
{
	Point pDp = Rec::AdjustCamPos(&pPos);
	if (pDp.x < Rec::Win.l) return;
	if (pDp.x > Rec::Win.r) return;
	if (pDp.y < Rec::Win.t) return;
	if (pDp.y > Rec::Win.b) return;

	/**
	SetPixel(hOff, (int)pDp.x, (int)pDp.y, cColor);
	/*/
	auto hOldPen = SelectObject(hOff, hPen);
	auto hOldBrush = SelectObject(hOff, hBrush);
	Rectangle(hOff, int(pDp.x - ((bSize - 1) * 0.5f)), int(pDp.y - ((bSize - 1) * 0.5f)), int(pDp.x + ((bSize - 1) * 0.5f)), int(pDp.y + ((bSize - 1) * 0.5f)));
	SelectObject(hOff, hOldPen);
	SelectObject(hOff, hOldBrush);
	/**/
}

Particle * Particle::sppTop = nullptr;

void Particle::Update()
{
	for (auto &vp : vpPix)
	{
		if (vp.bLifeCount >= bLifeMax)
		{
			vp.pPos = vp.pIniPos;
			vp.bLifeCount = byte(rand() % bLifeMax);
		}
		{
			const char cRand = char(rand() % 201 - 100);
			const byte bR = Max(Min(GetRValue(vp.cColor) + cRand, 255), 0);
			const byte bG = Max(Min(GetGValue(vp.cColor) + cRand, 255), 0);
			const byte bB = Max(Min(GetBValue(vp.cColor) + cRand, 255), 0);
			const COLORREF cCol = RGB(bR, bG, bB);
			vp.pPix.SetColor(cCol);
		}
		vp.fSpdX = cos_fast(vp.fAngle + vp.fRandX) * vp.fSpd;
		vp.fSpdY = sin_fast(vp.fAngle + vp.fRandY) * vp.fSpd;
		vp.pPos.x += vp.fSpdX;
		vp.pPos.y += vp.fSpdY;
		vp.pPix.SetPos(&vp.pPos);
		++vp.bLifeCount;
	}
}
void Particle::Draw() const
{
	for (auto &vp : vpPix)
	{
		vp.pPix.Draw();
	}
}
void Particle::UpdateAll()
{
	auto pIt = sppTop;
	while (pIt)
	{
		if (pIt->bUpdateFlag) pIt->Update();

		pIt = pIt->next;
	}
}
void Particle::DrawAll()
{
	auto pIt = sppTop;
	while (pIt)
	{
		if (pIt->bUpdateFlag) pIt->Draw();

		pIt = pIt->next;
	}
}

Particle::Particle()
	:
	vpPix({}), bLifeMax(100), next(nullptr), prev(nullptr), bUpdateFlag(false)
{
	if (!sppTop)
	{
		sppTop = this;
		return;
	}
	auto pIt = sppTop;
	while (pIt->next)
	{
		auto pBuf = pIt;
		pIt = pIt->next;
		pIt->prev = pBuf;
	}
	pIt->next = this;
	this->prev = pIt;
}
Particle::~Particle()
{
	if (!this->prev)
	{
		sppTop = this->next;
		if (!sppTop) return;
		sppTop->prev = nullptr;
		return;
	}
	auto pPre = this->prev;
	auto pNext = this->next;
	pPre->next = pNext;
}
void Particle::SetNum(const unsigned int cuiNum)
{
	auto vpTmp = vpPix;
	vpPix.clear();
	for (unsigned int ui = 0; ui < cuiNum; ++ui)
	{
		_vP vpT;
		if (vpTmp.size() > ui) vpT = vpTmp[ui];
		vpPix.emplace_back(vpT);
	}
}
void Particle::SetSize(const byte cbSize)
{
	for (auto &vp : vpPix)
	{
		vp.pPix.SetSize(cbSize);
	}
}
void Particle::SetInitPos(const Point * const cppPos, const short csMax, const short csMin)
{
	for (auto &vp : vpPix)
	{
		vp.pIniPos = Point(cppPos->x + (rand() % ((csMax << 1) + 1) + csMin), cppPos->y + (rand() % ((csMax << 1) + 1) + csMin));
		vp.pPos = vp.pIniPos;
		vp.pPix.SetPos(&vp.pPos);
	}
}
void Particle::SetLife(const byte cbLifeMax)
{
	bLifeMax = cbLifeMax;
	for (auto &vp : vpPix)
	{
		vp.bLifeCount = byte(rand() % bLifeMax);
	}
}
void Particle::SetSpd(const float cfSpd, const short csMax, const short csMin)
{
	for (auto &vp : vpPix)
	{
		vp.fSpd = cfSpd + (rand() % ((csMax << 1) + 1) + csMin);
	}
}
void Particle::SetAngle(const float cfAngle, const short csMax, const short csMin)
{
	const fix cfAng = DtoR(ModAngle(cfAngle));
	for (auto &vp : vpPix)
	{
		vp.fAngle = cfAng;
		vp.fRandX = DtoR(float(rand() % ((csMax << 1) + 1) + csMin));
		vp.fRandY = DtoR(float(rand() % ((csMax << 1) + 1) + csMin));
	}
}
void Particle::SetColor(const COLORREF ccColor, const char ccMax, const char ccMin)
{
	for (auto &vp : vpPix)
	{
		vp.cColor = ccColor;
		const char cRand = char(rand() % ((ccMax)+1) + ccMin);
		const byte bR = Max(Min(GetRValue(ccColor) + cRand, 255), 0);
		const byte bG = Max(Min(GetGValue(ccColor) + cRand, 255), 0);
		const byte bB = Max(Min(GetBValue(ccColor) + cRand, 255), 0);
		const COLORREF cCol = RGB(bR, bG, bB);
		vp.pPix.SetColor(cCol);
	}
}
void Particle::Play()
{
	if (!bUpdateFlag) bUpdateFlag = true;
}
void Particle::Stop()
{
	if (bUpdateFlag) bUpdateFlag = false;
}

Rep *Rep::rpTop = nullptr;
size_t Rep::sDataSize = 0;
Rep *Rep::rpOut = nullptr;
bool Rep::Push(const double dData)
{
	Rep rTmp;
	rTmp.dData = (dData == DBL_MAX) ? dData - 1.0 : dData;
	if (rpTop)
	{
		auto rpIt = rpTop;
		while (rpIt->rpNext)
		{
			rpIt = rpIt->rpNext;
		}
		rpIt->rpNext = (Rep *)malloc(sizeof(Rep) * 1);
		if (!rpIt->rpNext) return 1;
		rTmp.rpPrev = rpIt;
		*rpIt->rpNext = rTmp;
		++sDataSize;
		return 0;
	}
	rpTop = (Rep *)malloc(sizeof(Rep) * 1);
	if (!rpTop) return 1;
	*rpTop = rTmp;
	sDataSize = 1;
	return 0;
}
const double Rep::Output()
{
	if (!rpOut) return DBL_MAX;
	const double dRet = rpOut->dData;
	rpOut = rpOut->rpNext;
	return dRet;
}
bool Rep::SetPosition(const u_int uiIdx)
{
	if (uiIdx < 0) return 1;
	rpOut = rpTop;
	for (u_int ui = 0; ui < uiIdx; ++ui)
	{
		if (!rpOut->rpNext) return 1;
		rpOut = rpOut->rpNext;
	}
	return 0;
}
const Rep * const Rep::GetDataList()
{
	return rpTop;
}
bool Rep::SaveFile(const char * const ccpFileName)
{
	FILE *fpFile = nullptr;
	fopen_s(&fpFile, ccpFileName, "wb");
	if (!fpFile) return 1;
	auto rpIt = rpTop;
	while (rpIt)
	{
		fprintf_s(fpFile, "%f\n", rpIt->dData);
		rpIt = rpIt->rpNext;
	}
	fclose(fpFile);
	return 0;
}
bool Rep::LoadFile(const char * const ccpFileName)
{
	FILE *fpFile = nullptr;
	fopen_s(&fpFile, ccpFileName, "rb");
	if (!fpFile) return 1;
	if (sDataSize) Clear();
	double dTmp = 0;
	while (fscanf_s(fpFile, "%lf", &dTmp) != EOF)
	{
		if (Push(dTmp))
		{
			rpOut = rpTop;
			fclose(fpFile);
			return 1;
		}
	}
	rpOut = rpTop;
	fclose(fpFile);
	return 0;
}
bool Rep::Clear()
{
	if (!rpTop) return 1;
	auto rpIt = rpTop;
	while (rpIt)
	{
		auto rpNext = rpIt->rpNext;
		free(rpIt);
		rpIt = rpNext;
	}
	rpTop = nullptr;
	sDataSize = 0;
	return 0;
}
Rep::Rep()
	:
	dData(0.0),
	rpNext(nullptr),
	rpPrev(nullptr)
{

}
const Rep * const Rep::GetNext() const
{
	return this->rpNext;
}
const Rep * const Rep::GetPrev() const
{
	return this->rpPrev;
}
const double Rep::GetData() const
{
	return this->dData;
}