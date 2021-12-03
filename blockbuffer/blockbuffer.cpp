#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
TCHAR* ClipBoardOutText();
int ClipBoardInpText(LPWSTR buf);

int WINAPI wWinMain(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR pCmdLine, int nCmdShow)
{
    LPWSTR Data;
    TCHAR Alert[] = L"Вы нарушили что-то, скопировав текст:";
    TCHAR third[10240];
    LPWSTR NewData = calloc(sizeof(WCHAR), 40960);
    LPWSTR NnData = calloc(sizeof(WCHAR), 40960);
    while (TRUE)
    {
        Data = ClipBoardOutText();
        if (*Data != 0)
        {
            
            //*NewData = " ";
            while (*Data != '\0')
            {
                switch (*Data)
                {
                case '0':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Ноль");
                    break;
                case '1':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Один");
                    break;
                case '2':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Два");
                    break;
                case '3':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Три");
                    break;
                case '4':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Четыре");
                    break;
                case '5':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Пять");
                    break;
                case '6':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Шесть");
                    break;
                case '7':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Семь");
                    break;
                case '8':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Восемь");
                    break;
                case '9':
                    wsprintf(NnData, L"%s[%s]", NewData, L"Девять");
                    break;
                default:
                    wsprintf(NnData, L"%s%c", NewData, *Data);
                    break;
                }
                Data++;
                NewData = NnData;
            }

            swprintf(third, sizeof third, L"%s %s", Alert, NewData);
            MessageBox(NULL, third, L"Внимание!", MB_OK);
            ClipBoardInpText("");
            Data = NULL;
            *NewData = '\0';
            *NnData = '\0';
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
