#include "Model/SumControlModel.h"
#include "Model/EditControlModel.h"

CSumControlModel::CSumControlModel( const CRect& rect, std::weak_ptr<IBaseExprModel> parent ) :
IBaseExprModel( rect, parent )
{
	//this->rect.Set( 0, 0, 0, rect.GetHeight() ); // ��� ���������� ������ ������, ��������� ���������� ����� �� ����� ����������� ������
	//this->params.polygon.push_back( CLine( rect.Left(), rect.GetHeight() / 2, rect.Right(), rect.GetHeight() / 2 ) );

	depth = parent.lock()->GetDepth() + 1;
}

void CSumControlModel::Resize()
{
	int width = MAX( firstChild->GetRect().GetWidth(), secondChild->GetRect().GetWidth() );
	int height = firstChild->GetRect().GetHeight() + secondChild->GetRect().GetHeight() + 5;

	rect.Right() = rect.Left() + width;
	rect.Bottom() = rect.Top() + height;
}

void CSumControlModel::PlaceChildren()
{
	CRect newRect;
	int middle = ( rect.Right() + rect.Left() ) / 2;

	CRect oldRect = firstChild->GetRect();
	newRect.Top() = rect.Top();
	newRect.Bottom() = rect.Top() + oldRect.GetHeight();
	newRect.Left() = middle - oldRect.GetWidth() / 2;
	newRect.Right() = middle + oldRect.GetWidth() / 2;
	firstChild->SetRect( newRect );

	oldRect = secondChild->GetRect();
	newRect.Bottom() = rect.Bottom();
	newRect.Top() = rect.Bottom() - oldRect.GetHeight();
	newRect.Left() = middle - oldRect.GetWidth() / 2;
	newRect.Right() = middle + oldRect.GetWidth() / 2;
	secondChild->SetRect( newRect );

	updatePolygons();
}

int CSumControlModel::GetMiddle() const
{
	return ( firstChild->GetRect().GetHeight() + ( rect.GetHeight() - secondChild->GetRect().GetHeight() ) ) / 2;
}

void CSumControlModel::InitializeChildren( std::shared_ptr<IBaseExprModel> initChild )
{
	CRect childRect = CRect( 0, 0, 0, rect.GetHeight() );
	if ( initChild ) {
		firstChild = initChild;
		firstChild->SetParent( shared_from_this() );
		firstChild->UpdateDepth();
	}
	else {
		firstChild = std::make_shared<CExprControlModel>( childRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) );
		firstChild->InitializeChildren();
	}

	secondChild = std::make_shared<CExprControlModel>( childRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) );
	secondChild->InitializeChildren();

	Resize();
	PlaceChildren();
}

std::list<std::shared_ptr<IBaseExprModel>> CSumControlModel::GetChildren() const
{
	return std::list < std::shared_ptr<IBaseExprModel> > { firstChild, secondChild };
}

void CSumControlModel::SetRect( const CRect& rect )
{
	this->rect = rect;
	updatePolygons();
}

ViewType CSumControlModel::GetType() const
{
	return SUM;
}

void CSumControlModel::MoveBy( int dx, int dy )
{
	rect.MoveBy( dx, dy );
	updatePolygons();
}

void CSumControlModel::MoveCaretLeft( const IBaseExprModel* from, CCaret& caret, bool isInSelectionMode /*= false */ )
{
	// ���� ������ �� �������� - ���� � ������� �������
	if ( from == parent.lock().get() ) {
		secondChild->MoveCaretLeft( this, caret, isInSelectionMode );
	}
	else if ( from == secondChild.get() ) {
		firstChild->MoveCaretLeft( this, caret, isInSelectionMode );
	}
	else {
		// ����� ���� ������
		parent.lock()->MoveCaretLeft( this, caret, isInSelectionMode );
	}
}

void CSumControlModel::MoveCaretRight( const IBaseExprModel* from, CCaret& caret, bool isInSelectionMode /*= false */ )
{
	// ���� ������ �� �������� - ���� � �������� �������
	if ( from == parent.lock().get() ) {
		firstChild->MoveCaretRight( this, caret, isInSelectionMode );
	}
	else if ( from == firstChild.get() ) {
		// ���� ������ �� �������� - ���� � �������
		secondChild->MoveCaretRight( this, caret, isInSelectionMode );
	}
	else {
		// ����� ���� ������
		parent.lock()->MoveCaretRight( this, caret, isInSelectionMode );
	}
}

bool CSumControlModel::IsEmpty() const
{
	return firstChild->IsEmpty() && secondChild->IsEmpty();
}

void CSumControlModel::updatePolygons()
{
	params.polygon.clear();
	
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Top() + 5, rect.Left() + 2, rect.Bottom() - 5 ) ); // ����� �����
	params.polygon.push_back( CLine( rect.Left() + 5, rect.Top() + 5, rect.Left() + 5, rect.Bottom() - 5 ) ); // ������ �����
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Top() + 5, rect.Left() + 5, rect.Top() + 5 ) ); // ������� �����������
}

void CSumControlModel::UpdateSelection()
{
	params.isSelected = firstChild->IsSelected() && secondChild->IsSelected();
}

std::shared_ptr<IBaseExprModel> CSumControlModel::CopySelected() const
{
	std::shared_ptr<CSumControlModel> sumModel( new CSumControlModel( rect, parent ) );
	std::shared_ptr<IBaseExprModel> firstModel = firstChild->CopySelected();
	std::shared_ptr<IBaseExprModel> secondModel = secondChild->CopySelected();

	sumModel->firstChild = firstModel;
	sumModel->firstChild->SetParent( sumModel );

	sumModel->secondChild = secondModel;
	sumModel->secondChild->SetParent( sumModel );
	return sumModel;
}
