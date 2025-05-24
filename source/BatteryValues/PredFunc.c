/*
 *	Pred(efined)Func(tions).c - Set of predefined functions made eazier
 * 	to use in code 
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// ------------- WINAPI BATTERY FUNCTIONS ----------

bool ACLineStatus(SYSTEM_POWER_STATUS sps){
	wchar_t* FUNCNAME = L"ACLineStatus";
	if(GetSystemPowerStatus(&sps)){
		return sps.ACLineStatus;
	} else if(GetSystemPowerStatus(&sps) == 255){	// if Battery is unknown
		wprintf(L"Battery status '%ls' is unknown (returned 255)\n", FUNCNAME);
	} else {
		wprintf(L"Failed to get status: '%ls'.\n", FUNCNAME);
	}
}

LRESULT SetSystemThemeFont(HWND hwnd){
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	return SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
}

// --------------- STRING & OTHER FUNCTIONS -------------

wchar_t* FetchStringW(HINSTANCE hInstance, int strID) {
	wchar_t* FUNCNAME = L"FetchStringW";
	static wchar_t Buffer[3072];
	
	if(LoadStringW(hInstance, strID, Buffer, sizeof(Buffer) / sizeof(wchar_t)) > 0){
		return Buffer;
	} else {
		wprintf(L"%ls failed to Fetch", FUNCNAME);
	}
}

