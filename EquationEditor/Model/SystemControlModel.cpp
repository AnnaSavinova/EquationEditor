﻿#include "Model/SystemControlModel.h"
#include "Model/EditControlModel.h"

CSystemControlModel::CSystemControlModel( const CRect& rect, std::weak_ptr<IBaseExprModel> parent ) :
	IBaseExprModel(rect, parent)
{
	this->rect.Set( 0, 0, 0, rect.GetHeight() ); // нас интересует только высота, остальное исправится сразу же после инвалидации дерева
	// this->params.polygon.push_back( CLine( rect.Left( ), rect.GetHeight( ) / 2, rect.Right( ), rect.GetHeight( ) / 2 ) );

	depth = parent.lock()->GetDepth() + 1;
}

int CSystemControlModel::CalcHeight() const
{
  int height = 0;
  for (auto child : children) {
    height += child->GetRect().GetHeight();
  }
  height += MAX(0, (children.size() - 1)) * 5; // для промежутка между rect детей
  
  return height;
}

void CSystemControlModel::Resize()
{
  int width = 0;  
  for (auto child : GetChildren()) {
    width = MAX(child->GetRect().GetWidth(), width);
  }

  int height = CalcHeight();

	rect.Right() = rect.Left() + width;
	rect.Bottom() = rect.Top() + height;
}

std::wstring CSystemControlModel::Serialize() {
	// TODO
  return L"";
}

void CSystemControlModel::PlaceChildren()
{
	CRect newRect;
  int currentTop = rect.Top();

  for (int i = 0; i < children.size(); ++i) {
    CRect oldRect = children[i]->GetRect();
    newRect.Top() = currentTop;
    currentTop += oldRect.GetHeight() + 5;
    newRect.Bottom() = newRect.Top() + oldRect.GetHeight();
    newRect.Left() = rect.Left() + 10;
    newRect.Right() = newRect.Left() + oldRect.GetWidth();
    children[i]->SetRect(newRect);
  }

	updatePolygons();
}

int CSystemControlModel::GetMiddle( ) const
{
	return CalcHeight() / 2;
}

void CSystemControlModel::InitializeChildren( std::shared_ptr<IBaseExprModel> initChild /*= 0 */ )
{
	CRect childRect = CRect( 0, 0, 0, rect.GetHeight( ) );
	if( initChild ) {
		children.push_back( initChild );
		children[0]->SetParent( shared_from_this() );
    children[0]->UpdateDepth();
	} else {
		children.push_back( std::make_shared<CExprControlModel>( childRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) ) );
    children[0]->InitializeChildren();
	}

  children.push_back( std::make_shared<CExprControlModel>( childRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) ) );
  children[1]->InitializeChildren();

	Resize();
	PlaceChildren();
}

std::list<std::shared_ptr<IBaseExprModel>> CSystemControlModel::GetChildren() const 
{
	return std::list<std::shared_ptr<IBaseExprModel>> ( children.begin(), children.end() );
}

void CSystemControlModel::SetRect( const CRect& rect ) 
{
	this->rect = rect;
	updatePolygons();
}

ViewType CSystemControlModel::GetType() const 
{
	return SYSTEM;
}

void CSystemControlModel::MoveBy( int dx, int dy ) 
{
	rect.MoveBy( dx, dy );
	updatePolygons();
}

void CSystemControlModel::MoveCaretLeft( const IBaseExprModel* from, CCaret& caret, bool isInSelectionMode ) 
{
	if (isInSelectionMode)
		params.isSelected = true;
	// Если пришли из родителя - идем в нижнего ребенка
  if (from == parent.lock().get()) {
    children[children.size() - 1]->MoveCaretLeft(this, caret, isInSelectionMode);
  } else {
    int childNum = -1;
    for (int i = 0; i < children.size(); ++i) {
      if (children[i].get() == from) {
        childNum = i;
      }
    }
    if (childNum > 0) {
      children[childNum - 1]->MoveCaretLeft(this, caret, isInSelectionMode);
    } else {
      // Иначе идем наверх
      parent.lock()->MoveCaretLeft(this, caret, isInSelectionMode);
    }
  }
}

void CSystemControlModel::MoveCaretRight( const IBaseExprModel* from, CCaret& caret, bool isInSelectionMode /*= false */ )
{
	if (isInSelectionMode)
		params.isSelected = true;
	// Если пришли из родителя - идем в верхнего ребенка
	if( from == parent.lock().get() ) {
    children[0]->MoveCaretRight( this, caret, isInSelectionMode );
  } else {
    int childNum = -1;
    for (int i = 0; i < children.size(); ++i) {
      if (children[i].get() == from) {
        childNum = i;
      }
    }
    if (childNum < children.size() - 1) {
      children[childNum + 1]->MoveCaretRight(this, caret, isInSelectionMode);
    } else {
      // Иначе идем наверх
      parent.lock()->MoveCaretRight(this, caret, isInSelectionMode);
    }
  }
}

bool CSystemControlModel::IsEmpty() const 
{
  for (auto child : children) {
    if (!child->IsEmpty()) {
      return false;
    }
  }
  return true;
}

void CSystemControlModel::updatePolygons()
{
	params.polygon.front().Set( rect.Left(), rect.Top() + GetMiddle(), rect.Right(), rect.Top() + GetMiddle() );
}

void CSystemControlModel::UpdateSelection()
{
	params.isSelected = false;
  for (auto child : children) {
    if (child->IsSelected()) {
      params.isSelected = true;
      return;
    }
  }
}

std::shared_ptr<IBaseExprModel> CSystemControlModel::CopySelected() const
{
	std::shared_ptr<CSystemControlModel> systemModel( new CSystemControlModel( rect, parent ) );

  for ( auto child : children ) {
    std::shared_ptr<IBaseExprModel> childModel = child->CopySelected();
    childModel->SetParent(systemModel);
    systemModel->children.push_back(childModel);
  }

	return systemModel;
}