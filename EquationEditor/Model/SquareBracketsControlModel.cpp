#include "SquareBracketsControlModel.h"

CSquareBracketsControlModel::CSquareBracketsControlModel( CRect rect, std::weak_ptr<IBaseExprModel> parent ) :
	IBracketsModel( rect, parent )
{
	depth = parent.lock()->GetDepth() + 1;
}

void CSquareBracketsControlModel::Resize()
{
	// ���� ����� �� ��������. ������� �������������� ���, �����, ��� ����������� �� �����������, ����� � ������ �� ������ ���� ���������� ����������
	int width = content->GetRect().GetWidth() + 10;
	int height = 2 * (MAX( content->GetMiddle(), content->GetRect().GetHeight() - content->GetMiddle() ) + 3);

	rect.Right() = rect.Left() + width;
	rect.Bottom() = rect.Top() + height;
}

std::wstring CSquareBracketsControlModel::Serialize()
{
	if( !content->IsEmpty() ) {
		return L"<mfenced open=\"[\" close=\"]\">" + content->Serialize() + L"</mfenced>";
	}
	return L"";
}

ViewType CSquareBracketsControlModel::GetType() const
{
	return SQUAREBRACKETS;
}

void CSquareBracketsControlModel::updatePolygons()
{
	params.polygon.clear();
	// ����� ������
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Top() + 2, rect.Left() + 2, rect.Bottom() - 2 ) ); // ��������
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Top() + 2, rect.Left() + 5, rect.Top() + 2 ) ); // ����
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Bottom() - 2, rect.Left() + 5, rect.Bottom() - 2 ) ); // ���
	// ������ ������
	params.polygon.push_back( CLine( rect.Right() - 2, rect.Top() + 2, rect.Right() - 2, rect.Bottom() - 2 ) ); // ��������
	params.polygon.push_back( CLine( rect.Right() - 2, rect.Top() + 2, rect.Right() - 5, rect.Top() + 2 ) ); // ����
	params.polygon.push_back( CLine( rect.Right() - 2, rect.Bottom() - 2, rect.Right() - 5, rect.Bottom() - 2 ) ); // ���
}

std::shared_ptr<IBaseExprModel> CSquareBracketsControlModel::CopySelected() const
{
	// ���� �� ������ ������ �������� - ���������� ��� ��������� � ������,
	// ����� ���������� ������ ���������� �����
	if( content->IsSelected() ) {
		std::shared_ptr<CSquareBracketsControlModel> parModel( new CSquareBracketsControlModel( rect, parent ) );
		std::shared_ptr<IBaseExprModel> contentModel = content->CopySelected();
		if( contentModel != 0 && !contentModel->IsEmpty() ) {
			parModel->content = contentModel;
			parModel->content->SetParent( parModel );
			return parModel;
		} else {
			return 0;
		}
	} else {
		return content->CopySelected();
	}
}

