#pragma once
#include "IControlView.h"
#include <vector>

// �����, ����������� �������������� ������ �� ������
class CEquationPresenter
{
public:
    CEquationPresenter();

    void AddControlView(IControlView* view, HWND parentViewHwnd);

    IControlView* FindControlView(HWND hwnd);
};