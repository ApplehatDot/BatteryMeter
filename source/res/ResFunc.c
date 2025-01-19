/*	Resource [file] functions - make life eazier
		Github: ApplehatDot
 */

#include <wchar.h>
#include <windows.h>

// Unsure for now - Check the functionality later.
wchar_t GetResourceStringW(HINSTANCE hInst, int strID, size_t BuffSize){
	static wchar_t Buffer[BuffSize];
	
	LoadStringW(hInst, strID, Buffer, sizeof(Buffer) / sizeof(wchar_t));
	return Buffer;
}

// Same as with Wide-char one - Check the functionality later.
char GetResourceStringA(HINSTANCE hInst, int strID, size_t BuffSize){
	static char Buffer[BuffSize];
	
	LoadStringA(hInst, strID, Buffer, sizeof(Buffer) / sizeof(Buffer[0]));
	return Buffer;
}
