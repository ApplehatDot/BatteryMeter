/** BugCHK Window 
	By Applehat. */

#include <windows.h>
#include "Bugres.h"

HICON hIcon;
HWND Descrpt;
HWND hButton;
HWND hText;
#define CUSTOM_COLOR RGB(240, 240, 240) // #F0F0F0

void addtexts(HWND hwnd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HBRUSH hBrush;
	
    switch(msg) {
		case WM_CREATE:
			// add icon
            hIcon = LoadIcon(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDI_BUGCHK));
            CreateWindowEx(0, "STATIC", NULL, SS_ICON | WS_CHILD | WS_VISIBLE,
                20, 15, 149, 149, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
				
            SendMessage(GetDlgItem(hwnd, 0), STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
			
            hBrush = CreateSolidBrush(CUSTOM_COLOR);	// Coloring the window background
			
			addtexts(hwnd);
            break;
        case WM_CTLCOLORSTATIC:
            SetBkColor((HDC)wParam, CUSTOM_COLOR);
            return (INT_PTR)hBrush;
        case WM_ERASEBKGND:
            {
                HDC hdc = (HDC)wParam;
                RECT rect;
                GetClientRect(hwnd, &rect);
                FillRect(hdc, &rect, hBrush);
                return 1;
            }										// its done. the paint dried.
        case WM_COMMAND:
            if (LOWORD(wParam) == 100) {
                DestroyWindow(hwnd);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
extern "C" __declspec(dllexport) void BugCHK(HINSTANCE hInstance, HWND hwndParent, wchar_t *descript) {
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;


    // window class structure
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = hIcon;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "BugWind";
    wc.hIconSm       = hIcon;

    // register class
    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

    }

    // creating a window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "BugWind",
        "BugCheck",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 320,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    SetWindowTextW(hText, descript);	// change the text to one specified in the call

    // Główna pętla komunikatów
    while(GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

}


void addtexts(HWND hwnd){
	char buffer[256];

    LoadStringW(GetModuleHandle(NULL), DESCR, buffer, sizeof(buffer));

    HWND Descrpt = CreateWindowExW(0, L"STATIC", buffer, WS_CHILD | WS_VISIBLE,
        60, 23, 320, 120, hwnd, NULL, GetModuleHandle(NULL), NULL);
		
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	
	HWND hButton = CreateWindowEx(0, "BUTTON", "OK/Close", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        280, 240, 100, 30, hwnd, (HMENU)100, GetModuleHandle(NULL), NULL);
		
	
	hText = CreateWindowExW(
		0,
		L"EDIT", 
		L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Quis ipsum suspendisse ultrices gravida. Risus commodo viverra maecenas accumsan lacus vel facilisis.",	//descript
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		20, 60, 
		360, 170,
		hwnd, NULL, NULL, NULL);
    
    SendMessage(Descrpt, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
}
