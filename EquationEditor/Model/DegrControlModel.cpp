#include "Model/DegrControlModel.h"
#include "Model/EditControlModel.h"

CDegrControlModel::CDegrControlModel() {
	rect.bottom = rect.top = rect.left = rect.right = 0;
	parent = nullptr;

	�hild = std::make_shared<CExprControlModel>( CExprControlModel( ) );
	�hild->SetParent( std::shared_ptr<IBaseExprModel>(this) );
	std::shared_ptr<CEditControlModel> �hildEdit( new CEditControlModel() );

	�hild->AddChild(�hildEdit);
	�hildEdit->SetParent(�hild);
}

std::list<std::shared_ptr<IBaseExprModel>> CDegrControlModel::GetChildren( ) {
	return std::list<std::shared_ptr<IBaseExprModel>> { �hild };
}

ViewType CDegrControlModel::GetType() {
	return DEGR;
}
