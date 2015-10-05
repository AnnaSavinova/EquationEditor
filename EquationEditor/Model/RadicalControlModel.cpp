﻿#include "Model/RadicalControlModel.h"
#include "Model/EditControlModel.h"
#include "Model/Utils/GeneralFunct.h"


#include <string>

CRadicalControlModel::CRadicalControlModel(CRect rect, std::weak_ptr<IBaseExprModel> parent) :
	IBaseExprModel(rect, parent)
{
}

void CRadicalControlModel::Resize()
{
	int width = firstChild->GetRect().GetWidth() + secondChild->GetRect().GetWidth() + 15; //+15 для знака дроби
	int height = MAX(secondChild->GetRect().GetHeight(), firstChild->GetRect().GetHeight() + 0.5 * secondChild->GetRect().GetHeight()) + 15; 

	rect.Right() = rect.Left() + width;
	rect.Bottom() = rect.Top() + height;
}

void CRadicalControlModel::PlaceChildren()
{
	CRect newRect;

	CRect oldRect = firstChild->GetRect();
	newRect.Top() = rect.Top();
	newRect.Bottom() = rect.Bottom() - 0.5 * secondChild->GetRect().GetHeight();
	newRect.Left() = rect.Left();
	newRect.Right() = rect.Left() + oldRect.GetWidth();
	firstChild->SetRect(newRect);
	
	oldRect = secondChild->GetRect();
	newRect.Bottom() = rect.Bottom();
	newRect.Top() = rect.Bottom() - oldRect.GetHeight();//rect.Bottom() - oldRect.GetHeight();
	newRect.Left() = firstChild->GetRect().Right() + 15;
	newRect.Right() = newRect.Left() + oldRect.GetWidth();
	secondChild->SetRect(newRect);
}

int CRadicalControlModel::GetMiddle() const
{
	return rect.GetHeight() - secondChild->GetRect().GetHeight() + secondChild->GetMiddle();
}

void CRadicalControlModel::InitializeChildren()
{
	CRect firstChildRect = CRect( 0, 0, 0, 3 * getIndexHeight( rect.GetHeight() ) );
	firstChild = std::make_shared<CExprControlModel>( firstChildRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) );
	firstChild->InitializeChildren();

	CRect secondChildRect = CRect( 0, 0, 0, rect.GetHeight() );
	secondChild = std::make_shared<CExprControlModel>( secondChildRect, std::weak_ptr<IBaseExprModel>( shared_from_this() ) );
	secondChild->InitializeChildren();

	Resize();
	PlaceChildren();
}

std::list<std::shared_ptr<IBaseExprModel>> CRadicalControlModel::GetChildren() const 
{
	return std::list<std::shared_ptr<IBaseExprModel>> { firstChild, secondChild };
}

void CRadicalControlModel::SetRect(const CRect& rect) 
{
	this->rect = rect;
	this->params.polygon.clear();
	this->params.polygon.push_back( CLine(firstChild->GetRect().Right() + 15, rect.Top(), rect.Right(), rect.Top()) );
	this->params.polygon.push_back( CLine(firstChild->GetRect().Right() - 10, rect.Bottom() - 0.5 * rect.GetHeight(), firstChild->GetRect().Right(), rect.Bottom()) );
	this->params.polygon.push_back( CLine(firstChild->GetRect().Right(), rect.Bottom(), firstChild->GetRect().Right() + 15, rect.Top()) );
}

ViewType CRadicalControlModel::GetType() const 
{
	return RADICAL;
}

void CRadicalControlModel::MoveBy(int dx, int dy) 
{
	rect.MoveBy(dx, dy);
	for (CLine line : this->params.polygon) {
		line.MoveBy(dx, dy);
	}
}

void CRadicalControlModel::MoveCaretLeft(const IBaseExprModel* from, CCaret& caret) const 
{
	// Если пришли из индекса - идём в основание
	if( from == secondChild.get() ) {
		firstChild->MoveCaretLeft( this, caret );
	}
	//если пришли из родителя - идём в индекс
	else if( from == parent.lock().get() ) {
		secondChild->MoveCaretLeft( this, caret );
	}
	else {
		// Иначе идем наверх
		parent.lock()->MoveCaretLeft( this, caret );
	}
}

void CRadicalControlModel::MoveCaretRight(const IBaseExprModel* from, CCaret& caret) const 
{
	// Если пришли из родителя - идем в основание
	if( from == parent.lock().get() ) {
		firstChild->MoveCaretRight( this, caret );
	}
	//если из основания - в индекс
	else if( from == firstChild.get() ) {
		secondChild->MoveCaretRight( this, caret );
	}
	else {
		// Иначе идем наверх
		parent.lock()->MoveCaretRight( this, caret );
	}
}

// Высота выступающего над основанием показателя степени
int CRadicalControlModel::getIndexHeight( int rectHeight ) {
	return rectHeight / 4 > 3 ? rectHeight / 4 : 3;
}