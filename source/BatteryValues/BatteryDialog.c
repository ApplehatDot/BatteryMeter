// System Battery Values Dialog

#include <windows.h>


/*
	*1 - usage of PredFunc.c despite no definition in here:
		____________________________
		|	#include "PredFunc.c"  |
		|__________________________|
		
	the main definition uses no header files - cuz i found out
	it's way eazier and cleaner by doing this. This or any file dosen't 
	need the definition
*/

HINSTANCE hInstance;
HWND hGroupBox;
HWND hACLINE;

SYSTEM_POWER_STATUS sps;

void ShowBatteryValuesDialog(HINSTANCE hInstance, HWND hwndParent);
LRESULT CALLBACK BatDiagProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ShowBatteryValuesDialog(HINSTANCE hInstance, HWND hwndParent){
	WNDCLASSW wc = {0};
	
    wc.lpfnWndProc = BatDiagProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"BatteryValues";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL; // Should be system background ... ignore

	
	RegisterClassW(&wc);
	
	HWND hwnd = CreateWindowExW(
		0,
		L"BatteryValues",
		FetchStringW(hInstance, WINDOW_TITLE),	// <--- *1
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		300, 300,
		hwndParent,
		NULL,
		hInstance,
		NULL);
	
	
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

LRESULT CALLBACK BatDiagProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
		case WM_CREATE:
			CreateWindowExW(		// 		why is there a whole empty thing?
				0,					// it's a lazy BG fix, too lazy to search internet for now
				L"STATIC",			// it uses the system theme BG - so it dosen't look weird
				L"",				// 			- Applehat 				03.05.2025 20:17 
				WS_VISIBLE | WS_CHILD,	// DWstyles
				0, 0,
				300, 300,
				hwnd,NULL, NULL, NULL);
			
			hGroupBox = CreateWindowExW(
				0,
				L"BUTTON",
				FetchStringW(hInstance, BATTERY_VALUES),
				WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
				10, 10, 275, 240,
				hwnd,
				NULL,
				hInstance,
				NULL
				);
				
				
			hACLINE = CreateWindowExW(	
				0,	
				L"STATIC",	
				FetchStringW(hInstance, FETCHING_VALUES),				
				WS_VISIBLE | WS_CHILD,	// DWstyles
				20, 30,
				240, 200,
				hwnd,NULL, NULL, NULL);
				
			SetSystemThemeFont(hGroupBox);
			SetSystemThemeFont(hACLINE);
			
			SetTimer(hwnd, 1, 1000, NULL);
		break;
		
		case WM_CLOSE:
			ShowWindow(hwnd, SW_HIDE);
			return 0;
			
		case WM_TIMER:
            // Aktualizacja stanu AC
            if (GetSystemPowerStatus(&sps)) {
                wchar_t tempbuff[100];
                swprintf(tempbuff, FetchStringW(hInstance, AC_CONN_STAT), sps.ACLineStatus == 0 ? L"Disconnected" : L"Connected");
                SetWindowTextW(hACLINE, tempbuff); // Ustawienie nowego tekstu w STATIC
            } else {
				MessageBoxW(hwnd, FetchStringW(hInstance, ERR_FAILED_TO_FETCH_PWRSTAT), L"Error", MB_ICONERROR | MB_OK);
			}
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}