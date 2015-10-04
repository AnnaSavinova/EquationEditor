﻿#include "Model/RadicalControlModel.h"
#include "Model/EditControlModel.h"
#include "Model/Utils/GeneralFunct.h"


#include <string>

CRadicalControlModel::CRadicalControlModel(CRect rect, std::weak_ptr<IBaseExprModel> parent) {
	this->parent = parent;
	this->rect = rect;

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
	newRect.Top() = rect.Top() + 10;//rect.Bottom() - oldRect.GetHeight();
	newRect.Left() = firstChild->GetRect().Right() + 15;
	newRect.Right() = newRect.Left() + oldRect.GetWidth();
	secondChild->SetRect(newRect);

}

int CRadicalControlModel::GetMiddle() const
{
	return (secondChild->GetRect().Bottom() + secondChild->GetRect().Top()) / 2 - rect.Top();

}

void CRadicalControlModel::InitializeChildren()
{
	CRect childRect = CRect(0, 0, 5, rect.GetHeight());
	firstChild = std::make_shared<CExprControlModel>(CExprControlModel(childRect, std::weak_ptr<IBaseExprModel>(shared_from_this())));
	firstChild->InitializeChildren();

	secondChild = std::make_shared<CExprControlModel>(CExprControlModel(childRect, std::weak_ptr<IBaseExprModel>(shared_from_this())));
	secondChild->InitializeChildren();

	CRect newRect = CRect(rect.Left(), rect.Top(), rect.Left()+ 2*childRect.GetWidth() + 15, rect.Top() + childRect.GetHeight());
	SetRect(newRect);
	PlaceChildren();
}

std::list<std::shared_ptr<IBaseExprModel>> CRadicalControlModel::GetChildren() const {
	return std::list<std::shared_ptr<IBaseExprModel>> { firstChild, secondChild };
}

void CRadicalControlModel::SetRect(CRect rect) {
	this->rect = rect;
	this->params.polygon.clear();
	this->params.polygon.push_back(CLine(firstChild->GetRect().Right() + 15, rect.Top(), rect.Right(), rect.Top()));
	this->params.polygon.push_back(CLine(firstChild->GetRect().Right() - 10, rect.Bottom() - 0.5 * rect.GetHeight(), firstChild->GetRect().Right(), rect.Bottom()));
	this->params.polygon.push_back(CLine(firstChild->GetRect().Right(), rect.Bottom(), firstChild->GetRect().Right() + 15, rect.Top()));
}

ViewType CRadicalControlModel::GetType() const {
	return SUBSCRIPT;
}

void CRadicalControlModel::MoveBy(int dx, int dy) {
	rect.MoveBy(dx, dy);
	for (CLine line : this->params.polygon) {
		line.MoveBy(dx, dy);
	}
}

void CRadicalControlModel::GoLeft(std::shared_ptr<const IBaseExprModel> from, CCaret& caret) const {
	// Если пришли из индекса - идём в основание
	if (from == secondChild) {
		firstChild->GoLeft(shared_from_this(), caret);
	}
	//если пришли из родителя - идём в индекс
	else if (from == parent.lock()) {
		secondChild->GoLeft(shared_from_this(), caret);
	}
	else {
		// Иначе идем наверх
		parent.lock()->GoLeft(shared_from_this(), caret);
	}
}

void CRadicalControlModel::GoRight(std::shared_ptr<const IBaseExprModel> from, CCaret& caret) const {
	// Если пришли из родителя - идем в основание
	if (from == parent.lock()) {
		firstChild->GoRight(shared_from_this(), caret);
	}
	//если из основания - в индекс
	else if (from == firstChild) {
		secondChild->GoRight(shared_from_this(), caret);
	}
	else {
		// Иначе идем наверх
		parent.lock()->GoRight(shared_from_this(), caret);
	}
}

