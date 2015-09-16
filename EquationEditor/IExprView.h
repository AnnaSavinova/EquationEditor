#pragma once
#include <Windows.h>

// �������� �� ��������� ������ � ���������, ��������, ����� ��� ����� 
class IExprView {
    virtual ~IExprView() = 0;

    virtual void ResizeView(RECT rect) = 0;
};

inline IExprView::~IExprView() {}