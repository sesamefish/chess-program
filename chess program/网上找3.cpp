//#include "stdafx.h"
#include "resource.h"
#include "define.h"
#include "box.h"
#include "moveGeneration.h"
#pragma comment(lib, "winmm.lib")
#include <Mmsystem.h>
#define MAX_LOADSTRING 100
#define BOXBMP_WIDTH 537 /* 棋盘图bai片宽du度 */
#define BOXBMP_HEIGHT 537 /* 棋盘图片高度 */
#define SPACE 20 /* 棋盘图片和窗口边沿间隔 */
#define UNIT_WIDTH 35 /* 每个棋格zhi宽度 */
#define UNIT_HEIGHT 35 /* 每个棋格高度 */
#define STONE_WIDTH 20 /* 棋子宽度 */
/* 窗口宽度 = 两边空白dao + 棋盘图片宽度 + 窗口边框宽度 */
#define WIN_WIDTH 2*SPACE+BOXBMP_WIDTH+2*GetSystemMetrics(SM_CXDLGFRAME)
/* 窗口高度 = 标题栏高度 + 上下两边空白 + 棋盘图片高度 + 窗口边框高度 */
#define WIN_HEIGHT GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYMENU)+2*SPACE\
+BOXBMP_HEIGHT+2*GetSystemMetrics(SM_CXDLGFRAME)
//////////////////////////////////////////////////////////////////////
// 全局变量:
static HINSTANCE hInst; // 当前实例
static TCHAR szTitle[MAX_LOADSTRING]; // 标题栏文本
static TCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名
//////////////////////////////////////////////////////////////////////
// 此代码模块中包含的函数的前向声明:
ATOM InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK About(HWND, UINT, WPARAM, LPARAM);
////////////////////////////////////////////////////////////////////// 绘制棋子
void DrawStone(HDC hdc, int column, int row, STONE_TYPE stone)
{
HPEN hpen;
HBRUSH hbrush;
switch (stone)
{
case BLACK_STONE: //黑子
hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
hbrush = CreateSolidBrush(RGB(0, 0, 0));
break;
case WHITE_STONE: //白子
hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
hbrush = CreateSolidBrush(RGB(255, 255, 255));
break;
default:
return;
}
SelectObject(hdc, hpen);
SelectObject(hdc, hbrush);
Ellipse(hdc, column*34.9+35, row*34.9+35, column*34.9+55, row*34.9+55);
DeleteObject(hpen);
DeleteObject(hbrush);
return;
}
//////////////////////////////////////////////////////////// 绘制棋盘
void DrawChessBox(HDC hdc, STONE_TYPE box[BOX_ROW][BOX_COL])
{
assert(NULL != box);
HBITMAP hBitmap;
HDC hdcSrc;
hBitmap = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_CHESSBOX));
hdcSrc = CreateCompatibleDC(hdc);
SelectObject(hdcSrc, hBitmap);
BitBlt(hdc, SPACE, SPACE, BOXBMP_WIDTH, BOXBMP_HEIGHT, hdcSrc, 0, 0, SRCCOPY);
DeleteObject(hBitmap);
for(int column=0; column<BOX_COL; column++)
{
for(int row=0; row<BOX_ROW; row++)
{
DrawStone(hdc, column, row, box[column][row]);
}
}
}
////////////////////////////////////////////////////////////////////
//重新开始
static STONE_TYPE NewGame(HWND hWnd, STONE_TYPE box[BOX_ROW][BOX_COL])
{
boxInit(box);//清空
InvalidateRect(hWnd, NULL, FALSE);//重绘
return BLACK_STONE;
}
/**
* @brief 放置棋子
* @param hWnd 窗口句柄
* @param box 当前棋盘
* @param point 当前所下棋子在棋盘中的坐标
* @return TRUE 游戏结束, FALSE 游戏未结束
*/
static BOOL PlaceStone(HWND hWnd, STONE_TYPE box[BOX_ROW][BOX_COL], POINTS point, STONE_TYPE stone)
{
STONE_TYPE successStone = NONE_STONE;
boxSetStone(box, point.x, point.y, stone);
InvalidateRect(hWnd, NULL, FALSE);//重绘
PlaySound(MAKEINTRESOURCE(IDW_TADA), hInst, SND_RESOURCE|SND_SYNC);
successStone = boxIsOver(box, point.x, point.y);
if (WHITE_STONE == successStone)
{
MessageBox(hWnd, TEXT("白子获胜!"), TEXT("提示"), MB_OK|MB_ICONINFORMATION);
return TRUE;
}
else if (BLACK_STONE == successStone)
{
MessageBox(hWnd, TEXT("黑子获胜!"), TEXT("提示"), MB_OK|MB_ICONINFORMATION);
return TRUE;
}
return FALSE;
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPTSTR lpCmdLine,
int nCmdShow)
{
UNREFERENCED_PARAMETER(hPrevInstance);
UNREFERENCED_PARAMETER(lpCmdLine);
MSG msg;
HACCEL hAccelTable;
// 初始化全局字符串
LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
LoadString(hInstance, IDC_GOBANG, szWindowClass, MAX_LOADSTRING);
InitApplication(hInstance);
// 执行应用程序初始化:
if (!InitInstance (hInstance, nCmdShow))
{
return FALSE;
}
hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GOBANG));
// 主消息循环:
while (GetMessage(&msg, NULL, 0, 0))
{
if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}
}
return (int) msg.wParam;
}
//
// 函数: InitApplication()
//
// 目的: 注册窗口类。
//
// 注释:
//
// 仅当希望
// 此代码与添加到 Windows 95 中的“RegisterClassEx”
// 函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
// 这样应用程序就可以获得关联的
// “格式正确的”小图标。
//
ATOM InitApplication(HINSTANCE hInstance)
{
WNDCLASSEX wcex;
wcex.cbSize = sizeof(WNDCLASSEX);
wcex.style = CS_HREDRAW | CS_VREDRAW;
wcex.lpfnWndProc = WndProc;
wcex.cbClsExtra = 0;
wcex.cbWndExtra = 0;
wcex.hInstance = hInstance;
wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIG));
wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GOBANG);
wcex.lpszClassName = szWindowClass;
wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
return RegisterClassEx(&wcex);
}
//
// 函数: InitInstance(HINSTANCE, int)
//
// 目的: 保存实例句柄并创建主窗口
//
// 注释:
//
// 在此函数中，我们在全局变量中保存实例句柄并
// 创建和显示主程序窗口。
/////////////////////////////////////////////////////////清空棋盘
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
HWND hWnd;
hInst = hInstance; // 将实例句柄存储在全局变量中
int nWidth, nHeight;
nWidth = WIN_WIDTH/*585*/;
nHeight = WIN_HEIGHT/*630*/;
hWnd = CreateWindow(szWindowClass, szTitle,
WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
(GetSystemMetrics(SM_CXSCREEN)-nWidth)/2, (GetSystemMetrics(SM_CYSCREEN)-nHeight)/2,
nWidth, nHeight,
NULL, NULL, hInstance, NULL);
if (!hWnd)
{
return FALSE;
}
ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);
return TRUE;
}
///////////////////////////////////////////// “关于”框的消息处理程序。
BOOL CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
UNREFERENCED_PARAMETER(lParam);
switch (message)
{
case WM_INITDIALOG:
return TRUE;
case WM_COMMAND:
if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
{
EndDialog(hDlg, LOWORD(wParam));
return TRUE;
}
break;
}
return (INT_PTR)FALSE;
}
///////////////////////////////////////////////////////////////////
//
// 函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// 目的: 处理主窗口的消息。
//
// WM_COMMAND - 处理应用程序菜单
// WM_PAINT - 绘制主窗口
// WM_DESTROY - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static STONE_TYPE box[BOX_ROW][BOX_COL];
static STONE_TYPE currentStone = BLACK_STONE;
static BOOL startFlag = FALSE;//设置标志符
static int mode = IDM_MODE_MAN2COMPUTER;
HMENU hMenu = NULL;
switch (message)
{
case WM_CREATE : // 创建窗口
hMenu = GetMenu(hWnd);
CheckMenuItem(hMenu, mode, MF_CHECKED);
break;
case WM_COMMAND:
int wmId, wmEvent;
wmId = LOWORD(wParam);
wmEvent = HIWORD(wParam);
hMenu = GetMenu(hWnd);
// 分析菜单选择:
switch (wmId)
{
case IDM_ABOUT:
DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
break;
case IDM_EXIT:
PostMessage(hWnd,WM_CLOSE,0,0);
break;
case IDM_START://////////////////////////////////////////////////////////开始下棋
currentStone = NewGame(hWnd, box);//先下的棋子颜色
startFlag = TRUE;
break;
case IDM_MODE_MAN2COMPUTER :
CheckMenuItem(hMenu, mode, MF_UNCHECKED);
mode = IDM_MODE_MAN2COMPUTER;
currentStone = NewGame(hWnd, box);
CheckMenuItem(hMenu, mode, MF_CHECKED);
break;
case IDM_MODE_MAN2MAN :
CheckMenuItem(hMenu, mode, MF_UNCHECKED);
mode = IDM_MODE_MAN2MAN;
currentStone = NewGame(hWnd, box);
CheckMenuItem(hMenu, mode, MF_CHECKED);
break;
}
break;
case WM_PAINT:
HDC hdc;
PAINTSTRUCT ps;
hdc = BeginPaint(hWnd, &ps);
DrawChessBox(hdc, box);
EndPaint(hWnd, &ps);
break;
case WM_LBUTTONUP: //鼠标提起
if (!startFlag) // 没有点击开始
{
return 0;
}
POINTS point;
point = MAKEPOINTS(lParam);
//判断鼠标是否点击棋盘
if(point.x > 35 && point.x < 542 && point.y > 35 && point.y < 542)
{
//通过鼠标点击位置计算出棋子放置位置
point.x = (point.x - 35) / 34;
point.y = (point.y - 35) / 34;
if(boxGetStone(box, point.x, point.y) == NONE_STONE)
{
if (PlaceStone(hWnd, box, point, currentStone))
{
currentStone = NewGame(hWnd, box);
}
else
{
switch (currentStone)
{
case BLACK_STONE :
currentStone = WHITE_STONE;
break;
case WHITE_STONE :
currentStone = BLACK_STONE;
break;
default :
break;
}
}
// 人机对弈，由计算机搜索最优结果
if (mode == IDM_MODE_MAN2COMPUTER)
{
point = moveGeneration(box);
if (PlaceStone(hWnd, box, point, currentStone))
{
currentStone = NewGame(hWnd, box);
}
else
{
currentStone = BLACK_STONE; /* 人机对弈，人执黑子 */
}
}
}
else
{
MessageBox(hWnd, TEXT("此处已放置了棋子"), TEXT("警告"), MB_OK | MB_ICONWARNING);
}
}
break;
case WM_CLOSE:
if(MessageBox(hWnd, TEXT("确认要退出快乐五子棋游戏吗?"), TEXT("提示"), MB_YESNO | MB_ICONASTERISK)==IDYES)
{
DestroyWindow(hWnd);
}
break;
case WM_DESTROY:
PostQuitMessage(0);
break;
default:
return DefWindowProc(hWnd, message, wParam, lParam);
}
return 0;
}
