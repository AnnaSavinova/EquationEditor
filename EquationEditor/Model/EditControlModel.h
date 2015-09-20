#pragma once
#include "IBaseExprModel.h"
#include <string>
#include <vector>

// ������ ���������� ����
class CEditControlModel : public IBaseExprModel {
public:
	CEditControlModel();
	~CEditControlModel() {}

	IBaseExprModel* GetParent();
	void SetParent( IBaseExprModel* parent );

	std::list< IBaseExprModel* > GetChildren();

	RECT GetRect();
	void SetRect( RECT rect );

	CDrawParams GetDrawParams();

	void InsertSymbol( wchar_t symbol, int offset, int symbolWidth );
	
	// ������� ������
	// ���������� ������ ���������� �������
	int DeleteSymbol( int offset );

	// ��������� edit control �� ��� �� offset
	// ���������� ������ edit control
	CEditControlModel* SliceEditControl( int offset );

	std::vector<int> GetSymbolsWidths();
private:
	RECT rect;
	CDrawParams params;

	IBaseExprModel* parent;
	// ������ ������� �������
	std::vector<int> symbolsWidths;
};