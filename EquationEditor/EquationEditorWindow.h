#pragma once
#include <Windows.h>
#include "EquationPresenter.h"
#include "EditControlView.h"

class CEquationEditorWindow {
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
protected:
    void OnDestroy();

private:
    HWND hwnd; // ����� ����

    static const wchar_t* const className;

    static LRESULT __stdcall equationEditorWindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

    CEquationPresenter presenter;
};