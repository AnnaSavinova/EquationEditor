#include "Model/SumControlModel.h"
#include "Model/EditControlModel.h"

CSumControlModel::CSumControlModel( const CRect& rect, std::weak_ptr<IBaseExprModel> parent ) :
	IBaseExprModel( rect, parent )
{
	this->rect.Set( 0, 0, 0, rect.GetHeight() ); // ��� ���������� ������ ������, ��������� ���������� ����� �� ����� ����������� ������

	depth = parent.lock()->GetDepth() + 1;
}


int CSumControlModel::GetSymbolHeight() const
{
	return symbolRect.GetHeight();
}

void CSumControlModel::setRealChildPresentSumOrProduct()
{
	realChildPresentSum = nullptr;
	realChildPresentProduct = nullptr;
	auto childList = sumChild->GetChildren();
	if( !childList.empty() ) {
		auto child = std::next( childList.begin() );
		if( child != childList.end() ) {
			auto type = (*child)->GetType();
			if( type == SUM ) {
				realChildPresentSum = std::dynamic_pointer_cast< CSumControlModel >(*child);
			} else if( type == PRODUCT ) {
				realChildPresentProduct = std::dynamic_pointer_cast< CProductControlModel >(*child);
			}
		}
	}
}

int CSumControlModel::getSumChildHeight() const
{
	if( realChildPresentSum != nullptr ) {
		return realChildPresentSum->GetSymbolHeight(); // ���������� ������ ����� �����
	} /* TODO product else if( ) {

	  } */
	return sumChild->GetRect().GetHeight(); // ����� ���������� ������ ���������
}

void CSumControlModel::updateSymbolRect()
{
	symbolRect.Top() = GetSymbolTop();
	symbolRect.Bottom() = symbolRect.Top() + getSumChildHeight();
	int indexMaxWidth = MAX( firstChild->GetRect().GetWidth(), secondChild->GetRect().GetWidth() );
	int sigmaWidth = MAX( MIN( indexMaxWidth, symbolRect.GetHeight() ), symbolRect.GetHeight() / 2 );
	symbolRect.Left() = MAX( rect.Left() + indexMaxWidth / 2 - sigmaWidth / 2, rect.Left() );
	symbolRect.Right() = symbolRect.Left() + sigmaWidth;
}

void CSumControlModel::Resize()
{
	setRealChildPresentSumOrProduct();
	int width = MAX( firstChild->GetRect().GetWidth(), secondChild->GetRect().GetWidth() ) + 5 + sumChild->GetRect().GetWidth();
	updateSymbolRect();
	int height = MAX( firstChild->GetRect().GetHeight() + secondChild->GetRect().GetHeight() + 10 + symbolRect.GetHeight(),
		sumChild->GetRect().GetHeight() );
	rect.Right() = rect.Left() + width;
	rect.Bottom() = rect.Top() + height;
}

int CSumControlModel::getSumChildRectTop() const
{
	if( realChildPresentSum != nullptr ) {
		return symbolRect.Top() - 5 - realChildPresentSum->GetChildren().front()->GetRect().GetHeight();
	} /* TODO product else if( ) {

	} */
	return symbolRect.Top();
}

int CSumControlModel::GetSymbolTop() const
{
	if( realChildPresentSum != nullptr ) {
		return MAX( symbolRect.Top(), rect.Top() + realChildPresentSum->GetChildren().front()->GetRect().GetHeight() + 5 );
	} /* TODO product else if( ) {
	
	} */
	return rect.Top() + firstChild->GetRect().GetHeight() + 5;
}

void CSumControlModel::PlaceChildren()
{
	CRect newRect;
	updateSymbolRect();
	int middleWidth = symbolRect.Left() + symbolRect.GetWidth() / 2;
	int middleHeight = rect.GetHeight() / 2;

	CRect oldRect = firstChild->GetRect();
	newRect.Bottom() = symbolRect.Top() - 5;
	newRect.Top() = newRect.Bottom() - oldRect.GetHeight();
	newRect.Left() = middleWidth - oldRect.GetWidth() / 2;
	newRect.Right() = middleWidth + oldRect.GetWidth() / 2;
	firstChild->SetRect( newRect );

	oldRect = secondChild->GetRect();
	newRect.Top() = symbolRect.Top() + symbolRect.GetHeight() + 5;
	newRect.Bottom() = newRect.Top() + oldRect.GetHeight();
	newRect.Left() = middleWidth - oldRect.GetWidth() / 2;
	newRect.Right() = middleWidth + oldRect.GetWidth() / 2;
	secondChild->SetRect( newRect );

	oldRect = sumChild->GetRect();
	newRect.Top() = getSumChildRectTop();
	newRect.Bottom() = newRect.Top() + oldRect.GetHeight();
	newRect.Left() = symbolRect.Right() + 5;
	newRect.Right() = newRect.Left() + oldRect.GetWidth();
	sumChild->SetRect( newRect );

	updatePolygons();
}

int CSumControlModel::GetMiddle() const
{
	return (firstChild->GetRect().GetHeight() + (rect.GetHeight() - secondChild->GetRect().GetHeight())) / 2;
}

void CSumControlModel::InitializeChildren( std::shared_ptr<IBaseExprModel> initChild )
{
	CRect indexRect = CRect( 0, 0, 0, getIndexHeight( rect.GetHeight() ) );
	CRect sumRect = CRect( 0, 0, 0, rect.GetHeight() );

	if( initChild ) {
		sumChild = initChild;
		sumChild->SetParent( shared_from_this() );
		sumChild->UpdateDepth();
	} else {
		sumChild = std::make_shared<CExprControlModel>( sumRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) );
		sumChild->InitializeChildren();
	}

	firstChild = std::make_shared<CExprControlModel>( indexRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) );
	firstChild->InitializeChildren();

	secondChild = std::make_shared<CExprControlModel>( indexRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) );
	secondChild->InitializeChildren();

	Resize();
	PlaceChildren();
}

std::list<std::shared_ptr<IBaseExprModel>> CSumControlModel::GetChildren() const
{
	return std::list < std::shared_ptr<IBaseExprModel> > { firstChild, secondChild, sumChild };
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
	if( isInSelectionMode )
		params.isSelected = true;
	// ���� ������ �� �������� - ���� � ������� �������
	if( from == parent.lock().get() ) {
		secondChild->MoveCaretLeft( this, caret, isInSelectionMode );
	} else if( from == secondChild.get() ) {
		firstChild->MoveCaretLeft( this, caret, isInSelectionMode );
	} else if( from == firstChild.get() ) {
		sumChild->MoveCaretLeft( this, caret, isInSelectionMode );
	} else {
		// ����� ���� ������
		parent.lock()->MoveCaretLeft( this, caret, isInSelectionMode );
	}
}

void CSumControlModel::MoveCaretRight( const IBaseExprModel* from, CCaret& caret, bool isInSelectionMode /*= false */ )
{
	if( isInSelectionMode )
		params.isSelected = true;
	// ���� ������ �� �������� - ���� � �������� �������
	if( from == parent.lock().get() ) {
		firstChild->MoveCaretRight( this, caret, isInSelectionMode );
	} else if( from == firstChild.get() ) {
		// ���� ������ �� �������� - ���� � �������
		secondChild->MoveCaretRight( this, caret, isInSelectionMode );
	} else if( from == secondChild.get() ) {
		sumChild->MoveCaretRight( this, caret, isInSelectionMode );
	} else {
		// ����� ���� ������
		parent.lock()->MoveCaretRight( this, caret, isInSelectionMode );
	}
}

bool CSumControlModel::IsEmpty() const
{
	return firstChild->IsEmpty() && secondChild->IsEmpty() && sumChild->IsEmpty();
}

// ������ ��������
int CSumControlModel::getIndexHeight( int rectHeight )
{
	return max( rectHeight * 3 / 4, CEditControlModel::MINIMAL_HEIGHT );
}

void CSumControlModel::updatePolygons()
{
	params.polygon.clear();
	int sigmaCenterX = (symbolRect.Left() + symbolRect.Right()) / 2;
	int sigmaCenterY = (symbolRect.Top() + symbolRect.Bottom()) / 2;

	params.polygon.push_back( CLine( symbolRect.Left(), symbolRect.Top(), symbolRect.Right(), symbolRect.Top() ) ); // ������� �����������
	params.polygon.push_back( CLine( symbolRect.Left(), symbolRect.Top(), sigmaCenterX, sigmaCenterY ) ); // ��������� ������ � �����
	params.polygon.push_back( CLine( sigmaCenterX, sigmaCenterY, symbolRect.Left(), symbolRect.Bottom() ) ); // ��������� �� ������ ����
	params.polygon.push_back( CLine( symbolRect.Left(), symbolRect.Bottom(), symbolRect.Right(), symbolRect.Bottom() ) ); // ������ �����������
}

void CSumControlModel::UpdateSelection()
{
	if( !(firstChild->IsSelected()) || !(secondChild->IsSelected()) || !(sumChild->IsSelected()) )
		params.isSelected = false;
}

std::shared_ptr<IBaseExprModel> CSumControlModel::CopySelected() const
{
	std::shared_ptr<CSumControlModel> sumModel( new CSumControlModel( rect, parent ) );
	std::shared_ptr<IBaseExprModel> firstModel = firstChild->CopySelected();
	std::shared_ptr<IBaseExprModel> secondModel = secondChild->CopySelected();
	std::shared_ptr<IBaseExprModel> sumChildModel = sumChild->CopySelected();

	sumModel->firstChild = firstModel;
	sumModel->firstChild->SetParent( sumModel );

	sumModel->secondChild = secondModel;
	sumModel->secondChild->SetParent( sumModel );

	sumModel->sumChild = sumChildModel;
	sumModel->sumChild->SetParent( sumModel );
	return sumModel;
}
