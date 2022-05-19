#include <windows.h>
#include <string.h>
#include <stdio.h>

using namespace std;

LOGFONT lfcreator, lfres;
HFONT crFont, resFont;
HWND startButton; // дескриптор кнопки
char info[15];    // массив, куда будет передана информация в функции из DLL
char crStr[28] = "Created by Igor Larin PM-93";

DWORD WINAPI ThreadFunc(void *)
{
    typedef int (*ImportFunction)(char *);
    ImportFunction DLLInfo;
    HINSTANCE hinstLib = LoadLibrary(TEXT("info.dll"));                // загружаем динамическую библиотеку
    DLLInfo = (ImportFunction)GetProcAddress(hinstLib, "Information"); // получаем адрес экспортируемой функции
    DLLInfo(info);                                                     // вызываем функцию из динамической библиотеки
    FreeLibrary(hinstLib);                                             // освобождаем модуль загруженной DLL
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hDC, hMDC;
    switch (msg)
    {
    case WM_COMMAND: // при нажатии пользователем кнопки
        if (lParam == (LPARAM)startButton)
        {
            DWORD IDThread;
            // создаем поток и получаем его дескриптор
            HANDLE hThread = CreateThread(
                NULL,
                0,
                ThreadFunc,
                NULL,
                0,
                &IDThread);
            WaitForSingleObject(hThread, INFINITE); // бесконечно ожидаем завершение потока
            CloseHandle(hThread);                   // закрываем поток
            InvalidateRect(hWnd, NULL, true);       // очищаем окно
            UpdateWindow(hWnd);                     // обновляем окно, отправляется сообщение WM_PAINT
        }
        break;
    case WM_PAINT: // при необходимости отрисовать часть окна
        // начинаем отрисовку приложения
        hDC = BeginPaint(hWnd, &ps);

        // определяем атрибуты для шрифтов
        lfcreator.lfHeight = 25;
        lfcreator.lfWeight = 900;

        lfres.lfHeight = 30;
        lfres.lfWeight = 300;
        lfres.lfItalic = true;

        // получаем шрифты на основе атрибутов
        crFont = CreateFontIndirect(&lfcreator);
        resFont = CreateFontIndirect(&lfres);

        SetBkMode(hDC, TRANSPARENT); // не изменеяем фон текстом
        SelectObject(hDC, crFont);
        TextOut(hDC, 20, 10, crStr, strlen(crStr));
        SelectObject(hDC, resFont);
        TextOut(hDC, 155, 115, info, strlen(info));
        // заканчиваем отрисовку
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:        // при закрытии окна
        PostQuitMessage(0); // делается запрос на завершение работы
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR str, int nWinMode)
{
    MSG msg;
    WNDCLASS wcl;
    HWND hWnd;

    wcl.hInstance = hThisInst;
    wcl.lpszClassName = "RGZWINDOW"; // название класса окна приложения
    wcl.lpfnWndProc = WindowProc;    // указываем функцию-обработчик сообщений
    wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.lpszMenuName = NULL;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hbrBackground = CreateSolidBrush(RGB(255, 214, 111)); // цвет фона

    RegisterClass(&wcl); // регистрируем класс окна

    // создаем главное окно
    hWnd = CreateWindow(
        "RGZWINDOW",
        "Get your day",                                                                             // заголовок окна
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,                                   // стили окна
                                                                                                    // WS_OVERLAPPED - окно является перекрывающимся окном
                                                                                                    // WS_CAPTION - в окне есть строка заголовка
                                                                                                    // WS_MINIMIZEBOX - в окне есть кнопка свернуть. Кроме того, необходимо указать стиль WS_SYSMENU.
        GetSystemMetrics(SM_CXSCREEN) / 2 - 250, GetSystemMetrics(SM_CYSCREEN) / 2 - 150, 500, 300, // окно создается в центре экрана с заданными размерами
        NULL,
        NULL,
        hThisInst,
        NULL);

    ShowWindow(hWnd, nWinMode);
    UpdateWindow(hWnd);
    // создаем кнопку
    startButton = CreateWindow("Button", "Get it", WS_CHILD | WS_VISIBLE, 200, 215, 100, 30, hWnd, NULL, hThisInst, NULL);
    // обработчик сообщений
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
