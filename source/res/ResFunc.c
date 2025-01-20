/*	Resource [file] functions - make life eazier
		Github: ApplehatDot
 */

#include <wchar.h>
#include <windows.h>

// Checked the syntax - check when testing

wchar_t* GetResourceStringW(HINSTANCE hInst, int strID){
    static wchar_t Buffer[2048];
    if(LoadStringW(hInst, strID, Buffer, sizeof(Buffer) / sizeof(wchar_t)) == 0) {
        MessageBoxW(NULL, L"Failed to load string resource", L"Error", MB_ICONERROR);
    }
    return Buffer;
}

char* GetResourceStringA(HINSTANCE hInst, int strID){
    static char Buffer[2048];
    if(LoadStringA(hInst, strID, Buffer, sizeof(Buffer) / sizeof(Buffer[0])) == 0) {
        MessageBoxA(NULL, "Failed to load string resource", "Error", MB_ICONERROR);
    }
    return Buffer;
}
