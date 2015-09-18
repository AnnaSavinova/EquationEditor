#pragma once
#include "IBaseExprModel.h"
#include "ExprControlModel.h"
#include "EditControlModel.h"

enum ViewType { TEXT, EXPR, FRAC };

// ��������� ���� ���������
class IEditorView {
public:
	virtual ~IEditorView() = 0;

	// ���������� ����� � ������������ ��������������
	virtual void DrawText( HDC hdc, std::wstring text, RECT rect ) = 0;

	// ���������� �������
	virtual void DrawPolygon( HDC hdc, std::list<CLine> polygon ) = 0;

	// ���������� ��������� �������
	virtual void SetCaret( POINT caretPoint, int height ) = 0;

	// ��������� ����������� ����
	virtual void Redraw() = 0;

	virtual int GetCharWidth( wchar_t symbol ) = 0;
};

inline IEditorView::~IEditorView() {}

struct CCaret {
	// ������� edit control, �� ������� ����� �������
	CEditControlModel* curEdit;
	// ���������� ������� �� ������
	POINT caretPoint;
	// ����� �������, �� ������� ����� �������
	int offset;

	CCaret() : offset( 0 ) {
		caretPoint.x = 0;
		caretPoint.y = 0;
		curEdit = nullptr;
	}
};

// �����, ����������� �������������� ������ �� ������
class CEquationPresenter {
public:
	CEquationPresenter( IEditorView* view );

	void AddControlView( ViewType viewType );

	void InsertSymbol( wchar_t symbol );

	void DeleteSymbol();

	void Draw( HDC hdc );

	void FindCaretPos( int x, int y );
private:
    CExprControlModel* root;
	CCaret caret;
	IEditorView* view;

	//void addFrac( IControlView* view, CExprControlModel* parent, RECT focusedViewRect );
	void setRect( IBaseExprModel* model, RECT rect );
	// void updateGraph(IControlModel* startVert);
};