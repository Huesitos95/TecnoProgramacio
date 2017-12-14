#include "AA1_A08_BST.hpp"

int main()
{
	BST BinaryTree;

	BinaryTree.Insert(10);
	BinaryTree.Insert(20);
	BinaryTree.Insert(30);
	BinaryTree.Insert(40);
	BinaryTree.Insert(15);
	BinaryTree.Insert(25);
	BinaryTree.Insert(35);
	BinaryTree.Insert(45);
	BinaryTree.Insert(50);
	BinaryTree.Insert(5);

	std::cout << "PreOrder" << std::endl;
	BinaryTree.PreOrder();
	std::cout << std::endl;

	std::cout << "InOrder" << std::endl;
	BinaryTree.InOrder();
	std::cout << std::endl;

	std::cout << "PostOrder" << std::endl;
	BinaryTree.PostOrder();
	std::cout << std::endl;

	int total = BinaryTree.GetNumberNodes();
	std::cout << total << std::endl;
	system("PAUSE");
}