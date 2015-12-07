#pragma once
#include <Windows.h>
#include <gdiplus.h>

#include "GP.h"

struct CTriangle {
	Gdiplus::PointF poly[3];
};

class GraphWindow {
public:
	GraphWindow( int width, int height );

	static bool RegisterClass(HINSTANCE hInstance);

	bool Create(HINSTANCE hInstance, int nCmdShow, HWND _editorHandle);

	void Show();

	HWND GetHandle();

	void SetParameters(const std::wstring& formula, bool is2D = false, bool _isFillPolygonsIf3D = false);

	void SetPosition(double newX, double newY, double newZ);

protected:
	void OnKeyDown( WPARAM wParam );
	void OnMouseWheel( WPARAM wParam );
	void OnMouseMove( WPARAM wParam, int x, int y );
	void OnLButtonDown( int xMousePos, int yMousePos );
	void OnLButtonUp( int xMousePos, int yMousePos );
	void OnImageSave();
	void OnSetPosition();

	void OnPaint();
	void OnSize(int width, int height);
	void OnClose();
	void OnDestroy();
	void OnCreate();
	int OnCommand( int loWord, int hiWord );

private:
	const static wchar_t* nameClassWindow;
	const static wchar_t* nameWindow;

	int prevMousePosX;
	int prevMousePosY;
	bool isInClickMode = false;

	double cameraX;
	double cameraY;
	double cameraZ;

	int windowWidth;
	int windowHeight;
	bool is2D;

	int cmdShow;
	HWND handle;
	HWND editorHandle;
	HWND setPositionDialogHandle;
	HMENU menu;

	Gdiplus::Image* plusButtonImage;
	Gdiplus::Image* plusPressedButtonImage;
	Gdiplus::Image* plusButton;
	Gdiplus::Rect plusRect;
	Gdiplus::Image* minusButtonImage;
	Gdiplus::Image* minusPressedButtonImage;
	Gdiplus::Image* minusButton;
	Gdiplus::Rect minusRect;

	GP graphInPoints;

	bool needToFillPolygons;

	void drawGraph(HDC dc);
	void drawAxis(HDC dc, int axisNum, RECT rec, const std::string axisName);
	void drawAxes(HDC dc);
	void drawCoordinates(HDC dc, int axisNum, double maxValue, int pointsCount = 6);

	// red for max and blue for min by default
	void fillWithGradient( HDC dc, std::vector< std::vector < std::vector< Gdiplus::PointF > > >& yPolygonPoints, 
		std::vector < std::vector< Gdiplus::PointF > >& zPolygonPoints,
		Gdiplus::Color maxColor = Gdiplus::Color(128, 255, 0, 0), Gdiplus::Color minColor = Gdiplus::Color(128, 0, 0, 255) );

	static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	void getMaxMinZAndRelativeGridKnots( double& min, double& max, int& xMin, int& yMin, int& xMax, int& yMax );
	void generatePointsOfMaxAndMinGradientColor( Gdiplus::Point &maxColorPoint, Gdiplus::Point &minColorPoint, 
												double& min, double& max, int& xMin, int& yMin, int& xMax, int& yMax );
	bool ScreenCapture( LPWSTR filename );
};

