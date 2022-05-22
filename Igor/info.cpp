#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) int Information(char *infoStr)
{
   SYSTEMTIME st;
   int res = 0, day;
   GetSystemTime(&st);  // �������� ��������� SYSTEMTIME
   day = st.wDay;  // �������� ������� ����
   __asm
   {
      mov ecx, 0
      c:
      mov eax, 4
         push ecx       // ��������� ecx ��� ���������� ������ cpuid
         cpuid
         pop ecx
         inc ecx
         and eax, 31    // ������� ������� 5 ��� eax � 2
         cmp eax, 2     // ���� �� �����, �� ����������� ecx ��� ������ ������ cpuid
         jne c          // ���� �����, �� ���������� ������� 12 ��� ebx
         and ebx, 4095
         mov res, ebx
   }
   sprintf(infoStr, "Current day: %d, L1 Instr. line size: %d bytes", day, res + 1); // �������� ������ ��� ������
   return 0;
}