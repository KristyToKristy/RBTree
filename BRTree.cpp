#include<iostream>
using namespace std;
enum Color
{
	BLACK,
	RED
};
template<class K,class V>
struct RBTreeNode
{
	RBTreeNode(const K& key,const V&value,const Color col = RED)
	:_left(NULL)
	,_right(NULL)
	,_parent(NULL)
	,_col(col)
	,_key(key)
	,_value(value)
	{}
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Color _col;
	K _key;
	V _value;	
};
template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value, BLACK);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}
		cur = new Node(key, value, BLACK);
		if (parent->_key <key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//调色
		while (cur != _root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = parent->_right;
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				//当叔叔节点为黑色，且S为F的右孩子，处理步骤;1 以父节点进行左旋 2将父节点变黑祖父节点变红，3然后进行右旋
				else
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);
					}
					RotateR(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
				}
			}
			else  //往右子树插
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	bool IsBalanceTree()
	{
		return _IsBalance(_root);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if(subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent = subR;
		if (parent->_parent == NULL)
		{
			_root = parent;
		}
		else
		{
			if (parent->_key < parent->_parent->_key)
			{
				parent->_parent->_left = parent;
			}
			else
			{
				parent->_parent->_right = parent;
			}
		}
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if(subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;
		parent = subL;
		if (parent->_parent == NULL)
		{
			_root = parent;
		}
		else
		{
			if (parent->_key < parent->_parent->_key)
			{
				parent->_parent->_left = parent;
			}
			else
			{
				parent->_parent->_right = parent;
			}
		}
	}
	void _InOrder(Node*& root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		return (left > right)? left : right;
	}
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		 
		int bf = abs(left - right);
		if (bf > 1)
		{
			return false;
		}
		return _IsBalance(root->_left) && _IsBalance(root->_right);
	}
protected:
	Node* _root;
};
void TestRBTree()
{
	RBTree<int, int> t1;
	int a[10] = { 5, 2, 9, 6, 7, 3, 40, 1, 8 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
		t1.InOrder();
	}
	cout << "IsBalanceTree:" << t1.IsBalanceTree() << endl;
}
int main()
{
	TestRBTree();
	system("pause");
	return 0;
}
