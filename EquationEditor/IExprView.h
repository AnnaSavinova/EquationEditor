#pragma once
#include <Windows.h>

// �������� �� ��������� ������ � ���������, ��������, ����� ��� ����� 
class IExprView {
    virtual void ResizeView(RECT rect) = 0;
};