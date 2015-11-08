#include "Model/ParenthesesControlModel.h"

#include <string>

CParenthesesControlModel::CParenthesesControlModel( CRect rect, std::weak_ptr<IBaseExprModel> parent ) :
	IBracketsModel( rect, parent )
{
	depth = parent.lock()->GetDepth() + 1;
}

void CParenthesesControlModel::Resize()
{
	// ���� ����� �� ��������. ������� �������������� ���, �����, ��� ����������� �� �����������, ����� � ������ �� ������ ���� ���������� ����������
	int width = content->GetRect().GetWidth() + 10;
	int height = 2 * (MAX( content->GetMiddle(), content->GetRect().GetHeight() - content->GetMiddle() ) + 3);

	rect.Right() = rect.Left() + width;
	rect.Bottom() = rect.Top() + height;
}

std::wstring CParenthesesControlModel::Serialize() {
	if (!content->IsEmpty()) {
		return L"<mfenced>" + content->Serialize() + L"</mfenced>";
	}
	return L"";
}

ViewType CParenthesesControlModel::GetType( ) const
{
	return PARENTHESES;
}

void CParenthesesControlModel::updatePolygons()
{
	params.polygon.clear();
	// ����� ������
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Top() + 5, rect.Left() + 2, rect.Bottom() - 5 ) ); // ��������
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Top() + 5, rect.Left() + 5, rect.Top() + 2 ) ); // ����
	params.polygon.push_back( CLine( rect.Left() + 2, rect.Bottom() - 5, rect.Left() + 5, rect.Bottom() - 2 ) ); // ���
	// ������ ������
	params.polygon.push_back( CLine( rect.Right() - 2, rect.Top() + 5, rect.Right() - 2, rect.Bottom() - 5 ) ); // ��������
	params.polygon.push_back( CLine( rect.Right() - 2, rect.Top() + 5, rect.Right() - 5, rect.Top() + 2 ) ); // ����
	params.polygon.push_back( CLine( rect.Right() - 2, rect.Bottom() - 5, rect.Right() - 5, rect.Bottom() - 2 ) ); // ���
}

std::shared_ptr<IBaseExprModel> CParenthesesControlModel::CopySelected() const
{
	// ���� �� ������ ������ �������� - ���������� ��� ��������� � ������,
	// ����� ���������� ������ ���������� �����
	if( content->IsSelected() ) {
		std::shared_ptr<CParenthesesControlModel> parModel( new CParenthesesControlModel( rect, parent ) );
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
