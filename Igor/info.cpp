#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) int Information(char *infoStr)
{
   SYSTEMTIME st;
   int descs[4], fb = 255, tmp, find = 0;
   GetSystemTime(&st);  // получаем структуру SYSTEMTIME
   int day = st.wDay;  // получаем текущий день
   sprintf(infoStr, "Current day: %d", day); // собираем строку для вывода
   return 0;
}