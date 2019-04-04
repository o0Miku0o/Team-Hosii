#include "MyApp.h"
#include "FixedPoint.h"
//グローバル領域ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー//

//ウィンドウのハンドル,オフスクリーンのハンドル
static HWND g_hWnd;

//外部ファイルの関数のプロトタイプ宣言
void Init();
void Finalize();
bool Update();
void Render();

//ウィンドウプロシージャ関数
//(ウィンドウズからのメッセージに応じて処理をする)
LRESULT CALLBACK WinProc(HWND hWnd_, UINT message_, WPARAM wParam_, LPARAM lParam_)
{
	switch (message_)
	{
		//描画処理
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		//描画開始
		hDC = BeginPaint(hWnd_, &ps);
		//オフスクリーンをオンスクリーンに描画
		Rec::DrawBackToFront(hDC);
		//描画終了
		EndPaint(hWnd_, &ps);
		break;
	}
	case MM_WOM_DONE:
	{
		WSound::LoopProc(wParam_, lParam_);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam_)
		{
		case VK_ESCAPE:
			//WM_QUITメッセージを発行
			PostQuitMessage(0);
			break;
		}
		break;
	}
	case WM_CLOSE:
	case WM_DESTROY:
	{
		//WM_QUITメッセージを発行
		PostQuitMessage(0);
		break;
	}
	//上記以外のメッセージはWindowsに任せる
	default:
	{
		return DefWindowProc(hWnd_, message_, wParam_, lParam_);
	}
	}
	return 0;
}

//アプリケーションの初期化
bool ApplicationInitialize(HINSTANCE hThisInst_, int nWinMode_)
{
	WNDCLASSEX winclass;
	//ウィンドウクラスを定義する
	// このインスタンスへのハンドル
	winclass.hInstance = hThisInst_;
	// ウィンドウクラス名
	winclass.lpszClassName = WINCLASS;
	// ウィンドウ関数
	winclass.lpfnWndProc = WinProc;
	// ウィンドウスタイル（デフォルト）
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	// WNDCLASSEX構造体のサイズを設定
	winclass.cbSize = sizeof(WNDCLASSEX);
	// ラージアイコン
	winclass.hIcon = LoadIcon(hThisInst_, IDI_APPLICATION);
	// スモールアイコン
	winclass.hIconSm = LoadIcon(hThisInst_, IDI_WINLOGO);
	// カーソルスタイル
	winclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// メニュー（なしに設定）
	winclass.lpszMenuName = nullptr;
	// エクストラ
	winclass.cbClsExtra = 0;
	// 必要な情報
	winclass.cbWndExtra = 0;
	// ウィンドウの背景
	winclass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	//ウィンドウクラスを登録する
	if (!RegisterClassEx(&winclass))
		return 0;
	//デスクトップのサイズを取得
	RECT dsktoprect;
	GetWindowRect(GetDesktopWindow(), &dsktoprect);

	//ウィンドウを生成
	g_hWnd = CreateWindow(
		// ウィンドウクラスの名前
		WINCLASS,
		// ウィンドウタイトル
		WINNAME,
		// ウィンドウスタイル
		/**/WS_VISIBLE | WS_POPUP/*/WS_SYSMENU/**/,
		// ウィンドウの左角Ｘ座標
		0,
		// ウィンドウの左角Ｙ座標
		0,
		// ウィンドウの幅
		1920,
		// ウィンドウの高さ
		1080,
		// 親ウィンドウ
		NULL,
		// メニュー
		NULL,
		// このプログラムのインスタンスのハンドル
		hThisInst_,
		// 追加引数
		NULL
	);
	// ウィンドウを表示する
	ShowWindow(g_hWnd, nWinMode_);
	UpdateWindow(g_hWnd);
	return 0;
}

//指定時間処理を待つ関数
//(コンピュータの処理速度の違いで処理が速くなりすぎないようにする)
/**
bool WaitProcess(double *setsec_, const double waitsec_)
{
	if ((double)timeGetTime() - waitsec_ >= *setsec_)
	{
		*setsec_ = (double)timeGetTime();
		return 1;
	}
	return 0;
}
/*/
//指定時間処理を待つ関数
//(コンピュータの処理速度の違いで処理が速くなりすぎないようにする)
bool WaitProcess(long * const setsec_, const long waitsec_)
{
	if (SubFixedPoint(FixedPoint(timeGetTime()), waitsec_) >= FixedPoint(*setsec_))
	{
		*setsec_ = timeGetTime();
		return 1;
	}
	return 0;
}

//ウィンドウズのメイン関数
//(アプリケーションのエントリーポイント)
int WINAPI WinMain(HINSTANCE hThisInst_, HINSTANCE hPrevInst_, LPSTR lpszArgs_, int nWinMode_)
{
	MSG msg;
	//表示するウィンドウの定義、登録、表示
	if (ApplicationInitialize(hThisInst_, nWinMode_))
		return 0;
	/**/
	while (ShowCursor(false) != -1);
	/**/
	KB kb;
	//マウスの初期化
	MS ms(g_hWnd);
	//矩形クラスを初期化
	Rec::Init(g_hWnd);
	//DirectSoundの初期化
	DSound::Init();
	/*JoyPadの初期化*/
	JoyPad::Init(2000);
	/*JoyPad１*/
	JoyPad joy1;
	/*JoyPad２*/
	JoyPad joy2;
	//乱数の初期化
	srand(/**(unsigned int)time(nullptr)/*/0/**/);
	//ゲームの初期化処理
	Init();
	//アプリケーションまたはデバイスドライバの
	//最小タイマ分解能を、ミリ秒単位で指定
	timeBeginPeriod(1);
	//処理前の現在時間を取得する
	long tmptime1 = timeGetTime();
	long tmptime2 = timeGetTime();
	constexpr long cedFps = FixedPoint(1000.0 / 60.0);

	//メインメッセージループ
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//メッセージがWM_QUITならループを抜ける
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (WaitProcess(&tmptime1, cedFps))
		{
			//キーボード入力を取得
			KB::GetKeyState();
			//マウス入力を取得
			MS::GetMouseState();
			//JoyPadの情報を取得
			JoyPad::GetStateAll();
			//ゲームの更新処理
			if (Update()) PostQuitMessage(0);

			//描画前にオフスクリーンを黒く塗りつぶす（リセット？）
			Rec::ResetOff(BLACKNESS);
			//ゲームの描画処理
			Render();

#ifdef _DEBUG
			std::string tex = "fps[" + std::to_string(int(1000. / FixedToDouble(SubFixedPoint(FixedPoint(timeGetTime()), FixedPoint(tmptime2))))) + "]";
			DrawTex(/**Rec::win.r - 45/*/200.f/**/, 0, 45, 20, tex.c_str());
			/**/
			tex = "MS[" + std::to_string((int)ms.PosX()) + "][" + std::to_string((int)ms.PosY()) + "]";
			DrawTex(Rec::win.r - 145, 0, 100, 20, tex.c_str());
			/**/
#endif

			//サウンドの終了時の処理
			DSound::EndSound();
			tmptime2 = timeGetTime();
		}
		//領域無効化
		InvalidateRect(g_hWnd, nullptr, false);
		//ウィンドウの更新を反映させる
		UpdateWindow(g_hWnd);
	}
	//終了処理
	Finalize();
	//アプリケーションまたはデバイスドライバの
	//最小タイマ分解能を元に戻す
	timeEndPeriod(1);
	//矩形クラスのバッファを破棄
	Rec::Release();
	//DirectSoundの終了処理
	DSound::Finalize();
	//ウィンドウハンドルを破棄
	DeleteObject(g_hWnd);
	//終了
	return msg.wParam;
}