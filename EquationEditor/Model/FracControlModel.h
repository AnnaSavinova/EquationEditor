#pragma once
#include "IBaseExprModel.h"
#include "ExprControlModel.h"

// ������ ��� �����
class CFracControlModel : public IBaseExprModel {
public:
	CFracControlModel();
	~CFracControlModel() {}

	IBaseExprModel* GetParent();
	void SetParent( IBaseExprModel* parent );

	std::list<IBaseExprModel*> GetChildren();

	RECT GetRect();

	void SetRect( RECT rect );

	CDrawParams GetDrawParams();
private:
	RECT rect;

	IBaseExprModel* parent;
	// ������� �������
	CExprControlModel* firstChild;
	// ������ �������
	CExprControlModel* secondChild;
};