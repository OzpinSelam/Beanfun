#include<iostream>
#include<Windows.h>
#include<detours.h>
#include"Resource.h"
#include<commctrl.h>

#include"LRCommonLibrary.h"

//extern "C" __declspec(dllexport) int LRInject(char* filepath, char* dllpath, UINT CodePage)
//int main(int argc,char* argv[])
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
extern "C" _declspec(dllexport) int LRInject(char* application, char* workpath, char* commandline, char* dllpath, UINT CodePage)
{
	LRProfile beta;
	beta.CodePage = CodePage;
	beta.HookIME = false;
	strcpy(beta.DllPath, dllpath);
	LRConfigFileMap filemap;
	filemap.WrtieConfigFileMap(&beta);
	
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
    //std::cout << beta.CodePage;
	
	DetourCreateProcessWithDllExA(application, commandline, NULL,
		NULL, FALSE, CREATE_DEFAULT_ERROR_MODE, NULL, workpath,
		&si, &pi, dllpath, NULL);
    
	WaitForSingleObject(pi.hProcess, INFINITE);
    Sleep(5000);
	filemap.FreeConfigFileMap();
	return 0;
}