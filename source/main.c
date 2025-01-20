#include <windows.h>
#include <stdlib.h>
#include "resource.h"

//// Definitions
HWND hText;
HWND hFont;

wchar_t szBuffer[2048];

/// end definitions

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch(uMsg){
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
		case WM_CREATE:
			LoadStringW(GetModuleHandleW(NULL), LOADING_WINPROC, szBuffer, sizeof(szBuffer) / sizeof(wchar_t));
			
			hText = CreateWindowExW(
				0,
				L"STATIC",
				szBuffer,
				WS_VISIBLE | WS_CHILD,	// DWstyles
				20, 20,
				210, 30,
				hwnd,NULL, NULL, NULL);
			
			break;
		default:
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"MainWnd";
	
	WNDCLASSW wc = { };
	
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	
	if(!RegisterClassW(&wc)) {
        	MessageBoxW(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        	return 0;
    	}

	LoadStringW(hInstance, TITLE_NOJOB, szBuffer, sizeof(szBuffer) / sizeof(wchar_t));
	
	HWND hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		szBuffer,	// TITLE
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, // window Position on the desktop
		300, 430,		// Window Size | X , Y
		NULL,
		NULL,
		hInstance,
		NULL
		);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	MSG msg = {};
	while(GetMessage(&msg, NULL, 0, 0) > 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


	
