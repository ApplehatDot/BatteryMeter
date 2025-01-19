#include <windows.h>
#include <stdlib.h>
#include "resource.h"

//// Definitions
HWND hText;

/// end definitions

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch(uMsg){
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
		case WM_CREATE:
			hText = CreateWindowExW(
				0,
				L"STATIC",
				L"Loading Window Procedures ...",
				60, 215,
				100, 30,
				hwnd,NULL, NULL, NULL);
			
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	if(!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	
	HWND hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		L"BatteryMeter - Status",	// TITLE
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


	