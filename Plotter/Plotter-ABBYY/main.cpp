#include <string>
#include "graphWindow.h"
#include <stdio.h>

int _stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR commandLine, int nCmdShow) {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	if (!GraphWindow::RegisterClass(hInstance)) {
		return 1;
	}

	// first  bool - is2D
	// second bool - isNeedToFillIf3D

	LPWSTR *szArgList;
	int argCount;

	szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
	GraphWindow mainWindow(700, 700, szArgList[1], false, false);
	//GraphWindow mainWindow( 700, 700, L"./ex.xml", false, false ); // UNCOMMENT THIS LINE FOR SIMPLE DEMONSTRATION!!!

	if( !mainWindow.Create( hInstance, nCmdShow ) ) {
		return 1;
	}
	mainWindow.Show();

	MSG message;
	BOOL getMessageResult = 0;
	while ((getMessageResult = ::GetMessage(&message, NULL, 0, 0)) != 0) {
		if (getMessageResult == -1) {
			return -1;
		}

		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return message.wParam;
}