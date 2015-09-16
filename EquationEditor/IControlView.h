#pragma once
#include <Windows.h>

enum ViewType { EDIT_CONTROL, EXPR };

// ������, ������������ �� ������, ��������, edit control ��� �����
class IControlView {
public:
	virtual ~IControlView() = 0;

    // ���������� ��������� ������� � ����������� ������
    // ����� � edit control ������������ �� ������ rect'�
    virtual void SetRect(RECT rect) = 0;

    // ���������� ��������� � ������� HWND
    virtual HWND GetHWND() = 0;

    // ���������� ��� ������
    virtual ViewType GetType() = 0;
};

inline IControlView::~IControlView() {}