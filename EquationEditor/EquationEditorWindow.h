#pragma once
#include <Windows.h>

#include "EquationPresenter.h"

#include "EditControlView.h"

#include "FracDrawable.h"

struct CPoint {
	int x;
	int y;

	CPoint( int cx, int cy ) : x(cx), y(cy) {}
};

class CEquationEditorWindow : public CFracDrawable {
public:
    CEquationEditorWindow();

    // ���������������� ����� ����
    // ���� true, �� ���������������� �������
    static bool RegisterClassW();

    // ������� ��������� ����
    // ���� true, �� ������� �������
    bool Create();
    // �������� ����
    void Show(int cmdShow);
    // �������� edit'�
    void OnCreate();
    // ����������� �� ��������� ������� ����
    void OnSize(int cxSize, int cySize);

	void OnChar();

	void OnDrawFrac( RECT rect );

	void OnDraw();
protected:
    void OnDestroy();

private:
    HWND hwnd; // ����� ����
	std::list<CPoint> paintedPoints;

    static const wchar_t* const className;

    static LRESULT __stdcall equationEditorWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK editControlProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	WNDPROC originEditControlProc;

    CEquationPresenter presenter;
};