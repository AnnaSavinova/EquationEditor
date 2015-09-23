#pragma once
#include "Model/IBaseExprModel.h"
#include "Model/ExprControlModel.h"

// ������� ������. dasha
// ������ ��� �������
class CDegrControlModel : public IBaseExprModel {
public:
	CDegrControlModel();
	~CDegrControlModel() {}

	std::list<std::shared_ptr<IBaseExprModel>> GetChildren();

	ViewType GetType();
private:
	RECT rect;

	std::shared_ptr<IBaseExprModel> parent;

	// ����������
	std::shared_ptr<CExprControlModel> �hild;
};