// Measure.c - Measure Battery condition 'til the 


/*	TODO LIST:
 [] - add menu for start/stop-ing the measurement
 [] - Implement logic for making average battery condition from 3-step measures:
		[] - Battery condition score as %
		[] - Adding tips for maintaining batteries
		[] - imagine getting winNT/2000 UPS service working :PP

*/

#include <windows.h>

HMENU
HINSTANCE hInstance;
HWND hTimerCounter, hDescription;
HMENU hStartMeasure;

LRESULT CALLBACK MeasureProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg){
		case WM_CREATE:
			CreateWindowExW(		// 		why is there a whole empty thing?
				0,					// it's a lazy BG fix, too lazy to search internet for now
				L"STATIC",			// it uses the system theme BG - so it dosen't look weird
				L"",				// 			- Applehat 				06.05.2025 14:48
				WS_VISIBLE | WS_CHILD,
				0, 0,
				300, 300,
				hwnd,NULL, NULL, NULL);
		
			hDescription = CreateWindowExW(
				0,
				L"STATIC",
				FetchStringW(hInstance, MEASURE_DESCR1),
				WS_VISIBLE | WS_CHILD,
				10, 10, 275, 100,
				hwnd,
				NULL,
				hInstance,
				NULL
				);
				
			SetSystemThemeFont(hDescription);
		
			SetTimer(hwnd, 1, 1000, NULL);
		break;
		
		case WM_CLOSE:
			ShowWindow(hwnd, SW_HIDE);
			return 0;
		
		case WM_TIMER:		
			// nothing yet
			
		break;

		

	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void MeasureDialog(HINSTANCE hInstance, HWND hwndParent){
	WNDCLASSW wc = {0};
	
	wc.lpfnWndProc = MeasureProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Measure";
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	
	RegisterClassW(&wc);
	
	HWND hwnd = CreateWindowExW(
		0,
		L"Measure",
		FetchStringW(hInstance, MEASURE_TITLE),
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

