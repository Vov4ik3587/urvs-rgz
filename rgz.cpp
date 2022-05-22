#include <windows.h>    
#include <string.h>
#include <stdio.h>

using namespace std;

LOGFONT lfcreator, lfres;
HFONT MyNameFont, ResultFont;
HWND startButton;  // Дескриптор кнопки
char Result[100];     // Сюда будет записан результат работы фукнции из библиотеки DLL
char MyName[35] = "Created by Vladimir Galstyan PM-93";

DWORD WINAPI ThreadFunc(void*)
{
    typedef int(*ImportFunction)(char*);
    ImportFunction DLLInfo;
    HINSTANCE hinstLib = LoadLibrary(TEXT("info.dll"));                 // загружаем библиотеку
    DLLInfo = (ImportFunction)GetProcAddress(hinstLib, "Information");  // получаем адрес экспортируемой функции
    DLLInfo(Result);                                                      // вызываем функцию
    FreeLibrary(hinstLib);                                              // освобождаем модуль загруженной DLL
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;  
    HDC hDC, hMDC;
    switch (msg)
    {
        case WM_CREATE:
        {
           DWORD IDThread;
           // Создаем поток и получаем его дескриптор
           HANDLE hThread = CreateThread(
              NULL,
              0,
              ThreadFunc,
              NULL,
              0,
              &IDThread);
           WaitForSingleObject(hThread, INFINITE); // Ждем завершение потока
           CloseHandle(hThread);                   // Закрываем поток
           break;
        }
        case WM_PAINT: // при необходимости отрисовать часть окна
           // Отрисовка приложения
           hDC = BeginPaint(hWnd, &ps);

           // Определяем характеристики шрифта
           lfcreator.lfHeight = 25;
           lfcreator.lfWeight = 600;

           lfres.lfHeight = 30;
           lfres.lfWidth = 10;
           lfres.lfWeight = 200;
           lfres.lfItalic = true;

           // Получаем шрифты
           MyNameFont = CreateFontIndirect(&lfcreator);
           ResultFont = CreateFontIndirect(&lfres);
           
           // Текст не меняет фон
           SetBkMode(hDC, TRANSPARENT);
           SelectObject(hDC, MyNameFont);                      
           TextOut(hDC, 200, 200, MyName, strlen(MyName));
           SelectObject(hDC, ResultFont);
           TextOut(hDC, 25, 80, Result, strlen(Result));
           
           EndPaint(hWnd, &ps); // Конец отрисовки
           break;
        case WM_DESTROY:            // Запрос на завершение работы
            PostQuitMessage(0);    
            break;
        default: return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR str, int nWinMode)
{
   MSG msg;
   WNDCLASS wcl;
   HWND hWnd;

   wcl.hInstance       =   hThisInst;
   wcl.lpszClassName   =   "RGZ";                             // название класса окна приложения
   wcl.lpfnWndProc     =   WindowProc;                              // указываем функцию-обработчик сообщений
   wcl.hIcon           =   LoadIcon(NULL, IDI_APPLICATION);        
   wcl.hCursor         =   LoadCursor(NULL, IDC_ARROW);           
   wcl.lpszMenuName    =   NULL;                                   
   wcl.cbClsExtra      =   0;
   wcl.style           =   CS_HREDRAW | CS_VREDRAW;
   wcl.cbWndExtra      =   0;
   wcl.hbrBackground   =   CreateSolidBrush(RGB(255, 255, 255));    // Выбираем цвет фона

   RegisterClass(&wcl); // Регистрация класса окна

   // Создаем главное окно
   hWnd = CreateWindow(
        "RGZ",
        "Keyboard",                                               // Заголовок окна
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // Стили окна
        // WS_OVERLAPPED - окно является перекрывающимся окном
        // WS_CAPTION - в окне есть строка заголовка
        // WS_MINIMIZEBOX - в окне есть кнопка свернуть.
      GetSystemMetrics(SM_CXSCREEN) / 2 - 250, GetSystemMetrics(SM_CYSCREEN) / 2 - 150, 800, 300, // Окно создается в центре экрана с заданными размерами
        NULL,                                                      
        NULL,                                                      
        hThisInst,                                                 
        NULL);                                                     
   
   ShowWindow(hWnd, nWinMode);
   UpdateWindow(hWnd);  
   // Обрабатываем сообщения
   while (GetMessage(&msg, NULL, 0, 0))
   {  
       TranslateMessage(&msg);           
       DispatchMessage(&msg);            
   }
   return msg.wParam;
}

