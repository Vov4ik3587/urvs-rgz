
#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include <stdio.h>

extern "C" __declspec(dllexport) int Information(char *InfoString)
{
	int keybord_type = GetKeyboardType(0); // ������� ��������� ���������� � ���� ����������
	switch (keybord_type)
	{
	case 0x4:
		strcpy(InfoString, "This is enhanced keyboard which has 101 or 102 keys and Numpad");
		break;
	case 0x7:
		strcpy(InfoString, "This is Japanese keybord");
		break;
	case 0x8:
		strcpy(InfoString, "This is Korean keyboard");
		break;
	case 0x51:
		strcpy(InfoString, "Unknown type or HID keyboard");
		break;
	default:
		strcpy(InfoString, "Something's gone wrong");
		break;
	}

	return 0;
}