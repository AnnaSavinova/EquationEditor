#pragma once
#include "Model/IBaseExprModel.h"
#include "Model/ExprControlModel.h"

class CSumControlModel;

// ������ ��� ������������
// ������ �� ���� ���� ExprControl'�� - ������� � ������ �������
class CProductControlModel : public IBaseExprModel {
public:
	CProductControlModel( const CRect& rect, std::weak_ptr<IBaseExprModel> parent );

	std::list<std::shared_ptr<IBaseExprModel>> GetChildren() const;

	// ���������� ������� ������
	void InitializeChildren( std::shared_ptr<IBaseExprModel> initChild = 0 );

	void SetRect( const CRect& rect );

	void Resize();

	void PlaceChildren();

	int GetMiddle() const;

	ViewType GetType() const;

	void MoveBy( int dx, int dy );

	void MoveCaretLeft( const IBaseExprModel* from, CCaret& caret, bool isInSelectionMode = false );
	void MoveCaretRight( const IBaseExprModel* from, CCaret& caret, bool isInSelectionMode = false );

	bool IsEmpty() const;
	void UpdateSelection();

	int GetSymbolHeight() const;
	int GetSymbolTop() const;

	std::shared_ptr<IBaseExprModel> CopySelected() const;
private:
	// ������� �������
	std::shared_ptr<IBaseExprModel> firstChild;
	// ������ �������
	std::shared_ptr<IBaseExprModel> secondChild;
	// ������� ��� �������������
	std::shared_ptr<IBaseExprModel> productChild;

	std::shared_ptr< CSumControlModel > realChildPresentSum;
	std::shared_ptr< CProductControlModel > realChildPresentProduct;
	CRect symbolRect;

	int getIndexHeight( int rectHeight );

	void updatePolygons();
	void updateSymbolRect();
	int getSumChildHeight() const;
	int getSumChildRectTop() const;
	void setRealChildPresentSumOrProduct();
};