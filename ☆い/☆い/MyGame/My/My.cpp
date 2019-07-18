#include "My.h"

std::shared_ptr<KB> KB::instance;

HWND MS::hWnd;
std::shared_ptr<MS> MS::instance;

const Vector2 Vector2::zero = Vector2(0.f, 0.f);
const Vector2 Vector2::left = Vector2(-1.f, 0.f);
const Vector2 Vector2::right = Vector2(1.f, 0.f);
const Vector2 Vector2::up = Vector2(0.f, -1.f);
const Vector2 Vector2::down = Vector2(0.f, 1.f);

WSound *WSound::pwsTop;

std::vector<std::shared_ptr<JoyPad>> JoyPad::vpPadList;

std::mutex Rec::mutex;
HDC Rec::off;
HBITMAP Rec::hoffbmp;
HDC Rec::hAlphaDc;
BLENDFUNCTION Rec::bBlendFunc;
HBITMAP Rec::hAlphaBmp;
Frec Rec::Win;
Frec Rec::frZoom;
Point Rec::Cam;
Point Rec::pAdjust;
POINT Rec::pDrawPoint[5];

Rep *Rep::rpTop;
size_t Rep::sDataSize;
Rep *Rep::rpOut;