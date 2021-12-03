#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
TCHAR* ClipBoardOutText();
int ClipBoardInpText(LPWSTR buf);

int WINAPI wWinMain(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR pCmdLine, int nCmdShow)
{
    LPSTR Data;
    TCHAR Alert[] = L"Вы нарушили что-то, скопировав текст:";
    TCHAR third[512];
    while (TRUE)
    {
        Data = ClipBoardOutText();
        if (*Data != 0)
        {
            swprintf(third, sizeof third, L"%s %s", Alert, Data);
            MessageBox(NULL, third, L"Внимание!", MB_OK);
            ClipBoardInpText("");
            Data = NULL;
        }
        Sleep(1000);
    }
}
TCHAR* ClipBoardOutText()
{
    TCHAR* mes = NULL;
    OpenClipboard(NULL);
    HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
    mes = (TCHAR*)GlobalLock(hClipboardData);
    GlobalUnlock(hClipboardData);
    CloseClipboard();
    EmptyClipboard();
    return mes;
}

int ClipBoardInpText(LPWSTR buf)
{
    DWORD len = wcslen(buf) + 1;
    HANDLE hMem;
    hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR)); //выделение памяти в глобальной области видимости
    memcpy(GlobalLock(hMem), buf, len * sizeof(LPWSTR));
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
    return 0;
}
