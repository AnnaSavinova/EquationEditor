#pragma once
#include <Windows.h>

#include "EquationPresenter.h"

class CEquationEditorWindow : public IEditorView {
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

	void OnChar( WPARAM wParam );

	void OnDraw();

	void DrawText( HDC hdc, std::wstring text, RECT rect );

	void DrawPolygon( HDC hdc, std::list<CLine> polygon );

	void SetCaret( POINT caretPoint, int height );

	void Redraw();

	int GetCharWidth( wchar_t symbol );

	void OnLButtonDown( int xMousePos, int yMousePos );
protected:
    void OnDestroy();

private:
    HWND hwnd; // ����� ����
	std::list<CLine> paintedLines; // ������ ���� ������������ �����

    static const wchar_t* const className;

    static LRESULT __stdcall equationEditorWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	WNDPROC originEditControlProc;

    CEquationPresenter* presenter;
};