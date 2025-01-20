/*	Resource [file] functions - make life eazier
		Github: ApplehatDot
 */

#include <wchar.h>
#include <windows.h>

// Checked the syntax - check when testing

wchar_t* GetResourceStringW(HINSTANCE hInst, int strID){
	static wchar_t Buffer[2048];
	
	LoadStringW(hInst, strID, Buffer, sizeof(Buffer) / sizeof(wchar_t));
	return Buffer;
}

// Checked the syntax - check when testing
char* GetResourceStringA(HINSTANCE hInst, int strID){
	static char Buffer[2048];
	
	LoadStringA(hInst, strID, Buffer, sizeof(Buffer) / sizeof(Buffer[0]));
	return Buffer;
}
