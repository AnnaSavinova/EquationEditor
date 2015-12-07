#include <Windows.h>
#include "RibbonFramework.h"
#include "View\MainWindow.h"
#include "resource.h"
#include "Plotter/graphWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	FILE *stream;
	freopen_s(&stream, "output.txt", "w", stdout);
	HRESULT hr = CoInitialize(NULL);
	CMainWindow::RegisterClassW();
	CMainWindow wnd;
	wnd.Create();
	wnd.Show(nCmdShow);

	if (!GraphWindow::RegisterClass(hInstance)) {
		return 1;
	}

	HACCEL table = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	MSG message;
	BOOL getMessageResult = 0;
	while ((getMessageResult = ::GetMessage(&message, NULL, 0, 0)) != 0) {
		if (getMessageResult == -1) {
			return -1;
		}

		if (!::TranslateAccelerator(wnd.GetHandle(), table, &message)) {
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	fclose(stream);
	return 0;
}