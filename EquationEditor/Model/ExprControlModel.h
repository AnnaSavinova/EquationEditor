#pragma once
#include "IBaseExprModel.h"

// ������ ������� ��� ������
class CExprControlModel : public IBaseExprModel {
public:
	CExprControlModel();
	~CExprControlModel() {}

	IBaseExprModel* GetParent();
	void SetParent( IBaseExprModel* parent );

	std::list<IBaseExprModel*> GetChildren();
	
	void AddChild( IBaseExprModel* child );

	RECT GetRect();

	void SetRect( RECT rect );

	CDrawParams GetDrawParams() { return CDrawParams(); }
private:
	RECT rect;

	IBaseExprModel* parent;
	std::list<IBaseExprModel*> children;
};