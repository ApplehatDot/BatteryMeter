#include <windows.h>
#include <stdlib.h>
#include "resource.h"
#include "EZfunc/PredFunc.c"
#include "Measure/Measure.c"

//// Definitions
HWND hWelcome;
HWND hFont;
HMENU hMenu;
HINSTANCE hInstance;

wchar_t szBuffer[2048];

/// end definitions
void AddMenu(HWND hwnd){
	hMenu = CreateMenu();
	HMENU hManagerMenu = CreateMenu();
	
	AppendMenuW(hManagerMenu,MF_STRING,MGR_BATMEASURE, FetchStringW(hInstance, MGR_BATMEASURE));
	AppendMenuW(hManagerMenu,MF_STRING, MGR_LASTMEASURE, FetchStringW(hInstance, MGR_LASTMEASURE));
	AppendMenuW(hManagerMenu,MF_SEPARATOR,0,0);
	AppendMenuW(hManagerMenu,MF_STRING, MGR_EXIT, FetchStringW(hInstance, MGR_EXIT));
	
	AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hManagerMenu, FetchStringW(hInstance, MANAGER_MENU));
	
	
	HMENU hBatteryMenu = CreateMenu();
	
	AppendMenuW(hBatteryMenu, MF_STRING, BAT_CSYSBAT, FetchStringW(hInstance, BAT_CSYSBAT));
	
	AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hBatteryMenu, FetchStringW(hInstance, BATTERY_MENU));
	
	SetMenu(hwnd, hMenu);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch(uMsg){
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
		case WM_CREATE:
			CreateWindowExW(			// 		why is there a whole empty thing?
				0,						// it's a lazy BG fix, too lazy to search internet for now
				L"STATIC",				// it uses the system theme BG - so it dosen't look weird
				L"",					// 			- Applehat 				03.05.2025 20:17 
				WS_VISIBLE | WS_CHILD,	// DWstyles
				0, 0,
				300, 430,
				hwnd,NULL, NULL, NULL);
				
			AddMenu(hwnd);
			
			hWelcome = CreateWindowExW(
				0,
				L"STATIC",
				FetchStringW(hInstance, WELCOME_MSG),	// from PredFunc.c
				WS_VISIBLE | WS_CHILD,	// DWstyles
				20, 20,
				210, 30,
				hwnd,NULL, NULL, NULL);
			
			SetSystemThemeFont(hWelcome);	// from PredFunc.c
			break;
		case WM_COMMAND:
			switch(wParam){
				case MGR_EXIT:
					if(MessageBoxW(hwnd, FetchStringW(hInstance, MGR_EXITDESC), L"Confirm", MB_ICONQUESTION | MB_YESNO) == IDYES){
						DestroyWindow(hwnd);
					}
					break;

				case MGR_BATMEASURE:
					MeasureDialog(hInstance, hwnd);
					break;
				case BAT_CSYSBAT:
					ShowBatteryValuesDialog(hInstance, hwnd);
					break;
			}
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
	
	HWND hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		FetchStringW(hInstance, TITLE_NOJOB),	// TITLE
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


	
