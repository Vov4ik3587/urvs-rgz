#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) int Information(char *infoStr)
{
   SYSTEMTIME st;
   int descs[4], fb = 255, tmp, find = 0;
   GetSystemTime(&st);  // �������� ��������� SYSTEMTIME
   int day = st.wDay;  // �������� ������� ����
   sprintf(infoStr, "Current day: %d", day); // �������� ������ ��� ������
   return 0;
}