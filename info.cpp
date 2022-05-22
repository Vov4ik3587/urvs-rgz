#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) int Information(char *Infostr)
{
	int keybord_type = GetKeyboardType(0); // Получаем тип клавиатуры
	switch (keybord_type)
	{
	case 0x4:
		sprintf(Infostr, "This is enhanced keyboard which has 101 or 102 keys and Numpad(code %d)", keybord_type);
		break;
	case 0x7:
		sprintf(Infostr, "This is Japanese keybord (code %d)", keybord_type);
		break;
	case 0x8:
		sprintf(Infostr, "This is Korean keyboard (code %d)", keybord_type);
		break;
	case 0x51:
		sprintf(Infostr, "Unknown type or HID keyboard (code %d)", keybord_type);
		break;
	default:
		sprintf(Infostr, "Something's gone wrong (code %d)", keybord_type);
		break;
	}
	return 0;
}