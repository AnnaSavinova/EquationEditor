#include <functional>

#include <Model/IBaseExprModel.h>

// �����, ������� ������� � ������� ������ � ��������� ��� ��� ����������� ��������
// ������ �������� ����� ��� �������� ������
class CTreeDfsProcessor
{
	IBaseExprModel* _startingNode;
	std::function<void( IBaseExprModel*)> _afterEnter;
	std::function<void( IBaseExprModel*, IBaseExprModel*)> _beforeEachChild;
	std::function<bool( IBaseExprModel*, IBaseExprModel* )> _condition;
	std::function<void( IBaseExprModel*, IBaseExprModel* )> _afterEachChild;
	std::function<void( IBaseExprModel* )> _beforeExit;

	void dfsFunction( IBaseExprModel* currentNode ) const;

public:
	// ��� ������ process ��������� �������� ����� � ������� � startingNode
	// ��� ����� � ������� node ���������� afterEnter(node)
	// ����� ����������� ������ � ������ node, ������� child, ����������� beforeEachChild(node, child)
	// ���� condition(node, child) = false, �� ����� � child �� ����������
	// ����� ������ �� child ����������� afterEachChild(node, child)
	// ����� ������� �� ������� ����������� beforeExit(node)
	CTreeDfsProcessor(
		IBaseExprModel* startingNode = nullptr, 
		const std::function<void( IBaseExprModel* )>& afterEnter = std::function<void( IBaseExprModel* )>( [](IBaseExprModel* arg1){} ),
		const std::function<void( IBaseExprModel*, IBaseExprModel* )>& beforeEachChild = std::function<void( IBaseExprModel*, IBaseExprModel* )>( []( IBaseExprModel* arg1, IBaseExprModel* arg2 ){} ),
		const std::function<bool( IBaseExprModel*, IBaseExprModel* )>& condition = std::function<bool( IBaseExprModel*, IBaseExprModel* )>( []( IBaseExprModel* arg1, IBaseExprModel* arg2 ){return true;} ),
	const std::function<void( IBaseExprModel*, IBaseExprModel* )>& afterEachChild = std::function<void( IBaseExprModel*, IBaseExprModel* )>( []( IBaseExprModel* arg1, IBaseExprModel* arg2 ){} ),
	const std::function<void( IBaseExprModel* )>& beforeExit = std::function<void( IBaseExprModel* )>( []( IBaseExprModel* arg1 ){} ) );

	void SetStartingNode( IBaseExprModel* startingNode );
	void SetEnterProcessFunc( const std::function<void( IBaseExprModel* )>& afterEnter );
	void SetBeforeChildProcessFunc( const std::function<void( IBaseExprModel*, IBaseExprModel* )>& beforeEachChild );
	void SetCondition( const std::function<bool( IBaseExprModel*, IBaseExprModel* )>& condition );
	void SetAfterChildProcessFunc( const std::function<void( IBaseExprModel*, IBaseExprModel* )>& afterEachChild );
	void SetExitProcessFunc( const std::function<void( IBaseExprModel* )>& beforeExit );

	// ������� ���� ����� ������� ������� � ������, ��� ������� predicate = true
	// ����� ��� ���� �� ����������� �������, ��� ������� hint = false
	IBaseExprModel* Find(
		const std::function<bool( IBaseExprModel* )>& predicate,
		const std::function<bool( IBaseExprModel*, IBaseExprModel* )>& hint = std::function<bool( IBaseExprModel*, IBaseExprModel* )>( []( IBaseExprModel* arg1, IBaseExprModel* arg2 ){return true;} ) ) const;

	void Process() const;
};