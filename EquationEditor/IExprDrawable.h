#pragma once
#include <Windows.h>

// �������� �� ��������� ������ � ���������, ��������, ����� ��� ����� 
class IExprDrawable {
    virtual ~IExprDrawable() = 0;

    virtual void ResizeView(RECT rect) = 0;
};