#include "Model/DegrControlModel.h"
#include "Model/EditControlModel.h"

CDegrControlModel::CDegrControlModel() {
	rect.bottom = rect.top = rect.left = rect.right = 0;
	parent = nullptr;

	�hild = new CExprControlModel();
	�hild->SetParent(this);
	CEditControlModel* �hildEdit = new CEditControlModel();


	�hild->AddChild(�hildEdit);
	�hildEdit->SetParent(�hild);
}

IBaseExprModel* CDegrControlModel::GetParent() {
	return parent;
}

void CDegrControlModel::SetParent(IBaseExprModel* newParent) {
	parent = newParent;
}

std::list<IBaseExprModel*> CDegrControlModel::GetChildren() {
	return std::list<IBaseExprModel*> { �hild };
}

RECT CDegrControlModel::GetRect() {
	return rect;
}

void CDegrControlModel::SetRect(RECT newRect) {
	rect = newRect;
}

CDrawParams CDegrControlModel::GetDrawParams() {
	CDrawParams params;
	return params;
}
