/*
	Minimal Drag and Drop Application for Windows
	Copright (C) Alexandre LHUILLIER - 2019
	
	===
	
	This application creates an application window and a console window.
	Whenever you drag a file or a set of files from the Windows explorer
	to the application window, the absolute paths of the dropped files
	are printed in the console window.
*/

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include "DropTarget.h"


HWND hwnd;
bool isRunning;
WNDCLASSEX windowClass;
DropTarget dropTarget;

LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
	{
		isRunning = true;
	}
	break;
	case WM_DESTROY:
	case WM_CLOSE:
	case WM_QUIT:
		isRunning = false;
		PostQuitMessage(0);
		return 0;
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool createWindow(HINSTANCE hInstance, int width, int height, int bpp)
{
	windowClass.cbSize          = sizeof(WNDCLASSEX);
	windowClass.style           = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc     = wndProc;
	windowClass.cbClsExtra      = 0;
	windowClass.cbWndExtra      = 0;
	windowClass.hInstance       = hInstance;
	windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground   = NULL;
	windowClass.lpszMenuName    = NULL;
	windowClass.lpszClassName   = L"DragnDropClass";
	windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&windowClass))
	{
		std::cout << "Couldn't register window class" << std::endl;
		return false;
	}

	DWORD      dwExStyle;
	DWORD      dwStyle;
	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;

	RECT windowRect;
	windowRect.left = 0;
	windowRect.right = width;
	windowRect.top = 0;
	windowRect.bottom = height;
	if(AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle) == 0)
	{
		std::cout << "Couldn't set the size of the window rectangle" << std::endl;
		return false;
	}

	hwnd = CreateWindowEx(0,
		windowClass.lpszClassName,
		L"Minimal Drag and Drop Application for Windows",
		dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL);

	if(!hwnd)
	{
		std::cout << "Couldn't create window" << std::endl;
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	HRESULT oleResult = OleInitialize(NULL);
	if(oleResult != S_OK)
	{
		std::cout << "Couldn't initialize Ole" << std::endl;
		return false;
	}
	RegisterDragDrop(hwnd, (IDropTarget*)&dropTarget);

	return true;
}

bool processEvents()
{
	MSG msg;

	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return isRunning;
}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{
	AllocConsole();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Minimal Drag and Drop Application for Windows: Output Console");
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

    if (!createWindow(hInstance, 800, 600, 32))
    {
		system("PAUSE");
        return 1;
    }

    while(processEvents())
    {
    }

    return 0;
}
