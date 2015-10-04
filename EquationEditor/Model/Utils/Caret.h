#pragma once
#include <memory>
#include "Model/Utils/Rect.h"

class CEditControlModel;
class IBaseExprModel;

class CCaret {
public:
	CCaret();

	int GetPointX() const;

	int GetPointY() const;

	int GetHeight() const;
	
	void SetCurEdit( std::shared_ptr<IBaseExprModel> curEdit );

	std::shared_ptr<CEditControlModel> GetCurEdit( ) const;

	int& Offset();
private:
	// ������� edit control, �� ������� ����� �������
	std::shared_ptr<CEditControlModel> curEdit;
	// ����� �������, �� ������� ����� �������
	int offset;
};