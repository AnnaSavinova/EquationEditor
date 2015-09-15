#pragma once
#include <Windows.h>

// ������, ������������ �� ������, ��������, edit control ��� �����
class IControlView {
public:
    // ���������� ��������� ������� � ����������� ������
    // ����� � edit control ������������ �� ������ rect'�
    virtual void SetRect(RECT rect) = 0;

    // ���������� ��������� � ������� HWND
    virtual HWND GetHWND() = 0;
};