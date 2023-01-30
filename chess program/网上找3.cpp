//#include "stdafx.h"
#include "resource.h"
#include "define.h"
#include "box.h"
#include "moveGeneration.h"
#pragma comment(lib, "winmm.lib")
#include <Mmsystem.h>
#define MAX_LOADSTRING 100
#define BOXBMP_WIDTH 537 /* ����ͼbaiƬ��du�� */
#define BOXBMP_HEIGHT 537 /* ����ͼƬ�߶� */
#define SPACE 20 /* ����ͼƬ�ʹ��ڱ��ؼ�� */
#define UNIT_WIDTH 35 /* ÿ�����zhi��� */
#define UNIT_HEIGHT 35 /* ÿ�����߶� */
#define STONE_WIDTH 20 /* ���ӿ�� */
/* ���ڿ�� = ���߿հ�dao + ����ͼƬ��� + ���ڱ߿��� */
#define WIN_WIDTH 2*SPACE+BOXBMP_WIDTH+2*GetSystemMetrics(SM_CXDLGFRAME)
/* ���ڸ߶� = �������߶� + �������߿հ� + ����ͼƬ�߶� + ���ڱ߿�߶� */
#define WIN_HEIGHT GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYMENU)+2*SPACE\
+BOXBMP_HEIGHT+2*GetSystemMetrics(SM_CXDLGFRAME)
//////////////////////////////////////////////////////////////////////
// ȫ�ֱ���:
static HINSTANCE hInst; // ��ǰʵ��
static TCHAR szTitle[MAX_LOADSTRING]; // �������ı�
static TCHAR szWindowClass[MAX_LOADSTRING]; // ����������
//////////////////////////////////////////////////////////////////////
// �˴���ģ���а����ĺ�����ǰ������:
ATOM InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK About(HWND, UINT, WPARAM, LPARAM);
////////////////////////////////////////////////////////////////////// ��������
void DrawStone(HDC hdc, int column, int row, STONE_TYPE stone)
{
HPEN hpen;
HBRUSH hbrush;
switch (stone)
{
case BLACK_STONE: //����
hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
hbrush = CreateSolidBrush(RGB(0, 0, 0));
break;
case WHITE_STONE: //����
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
//////////////////////////////////////////////////////////// ��������
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
//���¿�ʼ
static STONE_TYPE NewGame(HWND hWnd, STONE_TYPE box[BOX_ROW][BOX_COL])
{
boxInit(box);//���
InvalidateRect(hWnd, NULL, FALSE);//�ػ�
return BLACK_STONE;
}
/**
* @brief ��������
* @param hWnd ���ھ��
* @param box ��ǰ����
* @param point ��ǰ���������������е�����
* @return TRUE ��Ϸ����, FALSE ��Ϸδ����
*/
static BOOL PlaceStone(HWND hWnd, STONE_TYPE box[BOX_ROW][BOX_COL], POINTS point, STONE_TYPE stone)
{
STONE_TYPE successStone = NONE_STONE;
boxSetStone(box, point.x, point.y, stone);
InvalidateRect(hWnd, NULL, FALSE);//�ػ�
PlaySound(MAKEINTRESOURCE(IDW_TADA), hInst, SND_RESOURCE|SND_SYNC);
successStone = boxIsOver(box, point.x, point.y);
if (WHITE_STONE == successStone)
{
MessageBox(hWnd, TEXT("���ӻ�ʤ!"), TEXT("��ʾ"), MB_OK|MB_ICONINFORMATION);
return TRUE;
}
else if (BLACK_STONE == successStone)
{
MessageBox(hWnd, TEXT("���ӻ�ʤ!"), TEXT("��ʾ"), MB_OK|MB_ICONINFORMATION);
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
// ��ʼ��ȫ���ַ���
LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
LoadString(hInstance, IDC_GOBANG, szWindowClass, MAX_LOADSTRING);
InitApplication(hInstance);
// ִ��Ӧ�ó����ʼ��:
if (!InitInstance (hInstance, nCmdShow))
{
return FALSE;
}
hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GOBANG));
// ����Ϣѭ��:
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
// ����: InitApplication()
//
// Ŀ��: ע�ᴰ���ࡣ
//
// ע��:
//
// ����ϣ��
// �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
// ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
// ����Ӧ�ó���Ϳ��Ի�ù�����
// ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
// ����: InitInstance(HINSTANCE, int)
//
// Ŀ��: ����ʵ�����������������
//
// ע��:
//
// �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
// ��������ʾ�����򴰿ڡ�
/////////////////////////////////////////////////////////�������
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
HWND hWnd;
hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
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
///////////////////////////////////////////// �����ڡ������Ϣ�������
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
// ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// Ŀ��: ���������ڵ���Ϣ��
//
// WM_COMMAND - ����Ӧ�ó���˵�
// WM_PAINT - ����������
// WM_DESTROY - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static STONE_TYPE box[BOX_ROW][BOX_COL];
static STONE_TYPE currentStone = BLACK_STONE;
static BOOL startFlag = FALSE;//���ñ�־��
static int mode = IDM_MODE_MAN2COMPUTER;
HMENU hMenu = NULL;
switch (message)
{
case WM_CREATE : // ��������
hMenu = GetMenu(hWnd);
CheckMenuItem(hMenu, mode, MF_CHECKED);
break;
case WM_COMMAND:
int wmId, wmEvent;
wmId = LOWORD(wParam);
wmEvent = HIWORD(wParam);
hMenu = GetMenu(hWnd);
// �����˵�ѡ��:
switch (wmId)
{
case IDM_ABOUT:
DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
break;
case IDM_EXIT:
PostMessage(hWnd,WM_CLOSE,0,0);
break;
case IDM_START://////////////////////////////////////////////////////////��ʼ����
currentStone = NewGame(hWnd, box);//���µ�������ɫ
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
case WM_LBUTTONUP: //�������
if (!startFlag) // û�е����ʼ
{
return 0;
}
POINTS point;
point = MAKEPOINTS(lParam);
//�ж�����Ƿ�������
if(point.x > 35 && point.x < 542 && point.y > 35 && point.y < 542)
{
//ͨ�������λ�ü�������ӷ���λ��
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
// �˻����ģ��ɼ�����������Ž��
if (mode == IDM_MODE_MAN2COMPUTER)
{
point = moveGeneration(box);
if (PlaceStone(hWnd, box, point, currentStone))
{
currentStone = NewGame(hWnd, box);
}
else
{
currentStone = BLACK_STONE; /* �˻����ģ���ִ���� */
}
}
}
else
{
MessageBox(hWnd, TEXT("�˴��ѷ���������"), TEXT("����"), MB_OK | MB_ICONWARNING);
}
}
break;
case WM_CLOSE:
if(MessageBox(hWnd, TEXT("ȷ��Ҫ�˳�������������Ϸ��?"), TEXT("��ʾ"), MB_YESNO | MB_ICONASTERISK)==IDYES)
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
