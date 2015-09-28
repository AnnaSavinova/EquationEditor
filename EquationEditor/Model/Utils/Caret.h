#include "Model/EditControlModel.h"
#include <memory>

class CCaret {
public:
	CCaret();

	int GetPointX();

	int GetPointY();

	int GetHeight();
	
	void SetCurEdit( std::shared_ptr<CEditControlModel> curEdit );

	std::shared_ptr<CEditControlModel> GetCurEdit();

	int& Offset();
private:
	// ������� edit control, �� ������� ����� �������
	std::shared_ptr<CEditControlModel> curEdit;
	// ����� �������, �� ������� ����� �������
	int offset;
};