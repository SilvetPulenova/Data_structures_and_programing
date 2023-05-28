#include<iostream>


template<typename T>
struct Node
{
	T data;
	Node<T>* left, * right;

	Node()
	{
		left = nullptr;
		right = nullptr;
	}
	Node(T data)
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
};
template<typename T>
int countN(Node<T>* root, int h) //намира броя на възлите в потдървета с височина h
{
	if (root == nullptr)
		return 0;
	if (h == 1)
	{
		return 0;
	}
	if (abs(countN(root->left, h - 1) - countN(root->right, h - 1)) <= 1)
	{
		return (1 + countN(root->left, h - 1) + countN(root->right, h - 1));
	}
}
template<typename T>
int PerfectlyTree(Node<T>* root, int h)
{
	int countNodes = 0;
	int countLeft = 0;
	int countRight = 0;
	int countIdealTrees = 0;

	//countNodes = countN(root, h);
	countLeft = countN(root->left, h);
	countRight = countN(root->right, h);
	countNodes = countLeft + countRight + 1;
	
	if (abs(countLeft - countRight) <= 1 && countNodes != 1)
	{
		std::cout << "Perfectly balanced tree" << std::endl;
		countIdealTrees++;
	}

	if (root == nullptr)
	{
		return 0;
	}

	PerfectlyTree(root->left, h);
	PerfectlyTree(root->right, h);

}

int main()
{
	//Създаване на примерно двоично наредено дърво
	Node<int>* root = new Node<int>(0);
	Node<int>* n1 = new Node<int>(1);
	Node<int>* n2 = new Node<int>(2);
	Node<int>* n3 = new Node<int>(3);
	Node<int>* n4 = new Node<int>(4);
	Node<int>* n5 = new Node<int>(5);
	Node<int>* n6 = new Node<int>(6);
	Node<int>* n7 = new Node<int>(7);
	Node<int>* n8 = new Node<int>(8);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n2->left = n4;
	n2->right = n5;
	n3->left = n6;
	n5->right = n7;
	n7->right = n8;

	PerfectlyTree(root, 3);

	return 0;
}