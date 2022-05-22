
#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include <stdio.h>

extern "C" __declspec(dllexport) int Information(char *InfoString)
{
	int keybord_type = GetKeyboardType(0); // Получаем тип клавиатуры
	switch (keybord_type)
	{
	case 0x4:
		sprintf(InfoString, "This is enhanced keyboard which has 101 or 102 keys and Numpad(code %d)", keybord_type);
		break;
	case 0x7:
		sprintf(InfoString, "This is Japanese keybord (code %d)", keybord_type);
		break;
	case 0x8:
		sprintf(InfoString, "This is Korean keyboard (code %d)", keybord_type);
		break;
	case 0x51:
		sprintf(InfoString, "Unknown type or HID keyboard (code %d)", keybord_type);
		break;
	default:
		sprintf(InfoString, "Something's gone wrong (code %d)", keybord_type);
		break;
	}

	return 0;
}