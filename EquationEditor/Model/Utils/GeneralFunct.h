#pragma once
#include "Model/EditControlModel.h"
#include "Model/ExprControlModel.h"

//����������� �������� ��� ��������� CExprControlModel � ��������� CExprControlModel � ��������������� CEditControlModel
void linkChildWithParent(std::shared_ptr<CExprControlModel> child, IBaseExprModel* parent);