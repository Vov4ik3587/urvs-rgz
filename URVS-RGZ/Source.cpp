#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
DWORD WINAPI ThreadFunc(void*) { // �������, ������� ��������� �������� (���������� ��� ����������).
	/*TCHAR string[256];
	DWORD size = 256;
	GetComputerName(string, &size);
	printf("%s\n", 0);*/
	//int GetKeyboardType(0);
	int keyboard_type = GetKeyboardType(0);
	cout << "Type:" << keyboard_type << "\n";
	return 0;
}

int main() {
	HANDLE hThread; // ���������� ������.
	DWORD IDThread; // ������������� ������. 

	hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &IDThread); // �������� ������. 
	if (hThread == NULL) {
		printf("Error! Failed to create new thread.\n");
		ExitProcess(3);
	}
	else {
		WaitForSingleObject(hThread, INFINITE); // �������� ���������� ������.                      
		int trying_to_Close = CloseHandle(hThread);    // �������� ����������� ������. 
		if (!trying_to_Close) {
			printf("Error! Failed to close hThread.\n");
			ExitProcess(3);
		}
	}
	return 0;
}