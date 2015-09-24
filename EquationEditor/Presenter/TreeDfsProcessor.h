#include <functional>

#include <Model/IBaseExprModel.h>

// �����, ������� ������� � ������� ������ � ��������� ��� ��� ����������� ��������
// ������ �������� ����� ��� �������� ������
class CTreeDfsProcessor
{
	typedef std::shared_ptr<IBaseExprModel> Node;

	Node _startingNode;
	std::function<void( Node)> _afterEnter;
	std::function<void( Node, Node)> _beforeEachChild;
	std::function<bool( Node, Node )> _condition;
	std::function<void( Node, Node )> _afterEachChild;
	std::function<void( Node )> _beforeExit;

	void dfsFunction( Node currentNode ) const;

public:
	// ��� ������ process ��������� �������� ����� � ������� � startingNode
	// ��� ����� � ������� node ���������� afterEnter(node)
	// ����� ����������� ������ � ������ node, ������� child, ����������� beforeEachChild(node, child)
	// ���� condition(node, child) = false, �� ����� � child �� ����������
	// ����� ������ �� child ����������� afterEachChild(node, child)
	// ����� ������� �� ������� ����������� beforeExit(node)
	CTreeDfsProcessor(
		Node startingNode = nullptr, 
		const std::function<void( Node )>& afterEnter = std::function<void( Node )>( [](Node arg1){} ),
		const std::function<void( Node, Node )>& beforeEachChild = std::function<void( Node, Node )>( []( Node arg1, Node arg2 ){} ),
		const std::function<bool( Node, Node )>& condition = std::function<bool( Node, Node )>( []( Node arg1, Node arg2 ){return true;} ),
	const std::function<void( Node, Node )>& afterEachChild = std::function<void( Node, Node )>( []( Node arg1, Node arg2 ){} ),
	const std::function<void( Node )>& beforeExit = std::function<void( Node )>( []( Node arg1 ){} ) );

	void SetStartingNode( Node startingNode );
	void SetEnterProcessFunc( const std::function<void( Node )>& afterEnter );
	void SetBeforeChildProcessFunc( const std::function<void( Node, Node )>& beforeEachChild );
	void SetCondition( const std::function<bool( Node, Node )>& condition );
	void SetAfterChildProcessFunc( const std::function<void( Node, Node )>& afterEachChild );
	void SetExitProcessFunc( const std::function<void( Node )>& beforeExit );

	// ������� ���� ����� ������� ������� � ������, ��� ������� predicate = true
	// ����� ��� ���� �� ����������� �������, ��� ������� hint = false
	Node Find(
		const std::function<bool( Node )>& predicate,
		const std::function<bool( Node, Node )>& hint = std::function<bool( Node, Node )>( []( Node arg1, Node arg2 ){return true;} ) ) const;

	void Process() const;
};