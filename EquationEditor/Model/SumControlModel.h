#pragma once
#include "Model/IBaseExprModel.h"
#include "Model/ExprControlModel.h"
#include "Model/ProductControlModel.h"	

// ������ ��� �����
// ������ �� ���� ���� ExprControl'�� - ������� � ������ �������
class CSumControlModel : public IBaseExprModel {
public:
	CSumControlModel( const CRect& rect, std::weak_ptr<IBaseExprModel> parent );

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

	int GetSymbolHeight() const;

	void UpdateSelection();

	int GetSymbolTop() const;
	
	std::shared_ptr<IBaseExprModel> CopySelected() const;
private:
	// ������� �������
	std::shared_ptr<IBaseExprModel> firstChild;
	// ������ �������
	std::shared_ptr<IBaseExprModel> secondChild;
	// �������, � �������� ��������� �����
	std::shared_ptr<IBaseExprModel> sumChild;

	std::shared_ptr< CSumControlModel > realChildPresentSum;
	std::shared_ptr< CProductControlModel > realChildPresentProduct;
	CRect symbolRect;

	void updatePolygons();
	void updateSymbolRect();
	int getIndexHeight(int rectHeight);
	int getSumChildHeight() const;
	int getSumChildRectTop() const;
	void setRealChildPresentSumOrProduct();
};