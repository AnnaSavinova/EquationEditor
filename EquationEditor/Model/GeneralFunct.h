#pragma once
#include "EditControlModel.h"
#include "ExprControlModel.h"

//����������� �������� ��� ��������� CExprControlModel � ��������� CExprControlModel � ��������������� CEditControlModel
void linkChildWithParent(std::shared_ptr<CExprControlModel> child, IBaseExprModel* parent);