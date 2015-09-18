#pragma once
#include "IBaseExprModel.h"
#include <string>

// ������ ���������� ����
class CEditControlModel : public IBaseExprModel {
public:
	CEditControlModel();
	~CEditControlModel() {}

	IBaseExprModel* GetParent();
	void SetParent( IBaseExprModel* parent );

	std::list< IBaseExprModel* > GetChilds();

	RECT GetRect();
	void SetRect( RECT rect );

	CDrawParams GetDrawParams();

	void InsertSymbol( wchar_t symbol, int offset, int symbolWidth );
	
	void DeleteSymbol( int offset, int symbolWidth );
private:
	RECT rect;
	CDrawParams params;

	IBaseExprModel* parent;
	// �������������� ������ ���� ��������
	std::list<RECT> symbolsRects;
};