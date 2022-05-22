#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) int Information(char *infoStr)
{
   SYSTEMTIME st;
   int res = 0, day;
   GetSystemTime(&st);  // получаем структуру SYSTEMTIME
   day = st.wDay;  // получаем текущий день
   __asm
   {
      mov ecx, 0
      c:
      mov eax, 4
         push ecx       // сохраняем ecx для следующего вызова cpuid
         cpuid
         pop ecx
         inc ecx
         and eax, 31    // сверяем младшие 5 бит eax с 2
         cmp eax, 2     // если не равны, то увеличиваем ecx для нового вызова cpuid
         jne c          // если равны, то записываем младшие 12 бит ebx
         and ebx, 4095
         mov res, ebx
   }
   sprintf(infoStr, "Current day: %d, L1 Instr. line size: %d bytes", day, res + 1); // собираем строку для вывода
   return 0;
}