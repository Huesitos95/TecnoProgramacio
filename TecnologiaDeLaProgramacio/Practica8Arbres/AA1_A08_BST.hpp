#pragma once
#include <iostream>

class Node {

public:
	int key;
	Node *left;
	Node *right;
	Node() :key(-1), left(nullptr), right(nullptr) {};
	Node(int akey):key(akey), left(nullptr), right(nullptr) {}; 
};

class BST
{
public:	
	
	BST();
	~BST();
	Node* Search(int key);
	void Insert(int key);
	void PreOrder();
	void InOrder();
	void PostOrder();
	bool Exist(int key);
	int GetNumberNodes();
	int Height();

private:
	Node *root;
	Node* Search(Node* node, int key);
	void Insert(Node** node, int key);
	void PreOrder(Node *node);
	void InOrder(Node *node);
	void PostOrder(Node *node);
	int GetNumberNodes(Node *nodo);
	int GetNumberNodesl();
	void PreOrderl();
	

	int Height(Node * node);

};

BST::BST() {root = nullptr;};

BST::~BST() {
//TODO

	if (root == nullptr)
	{
		if (root->left != nullptr)
		{
			
		}
		else {
			delete root->left;
		}
		if (root->right != nullptr)
		{
			
		}
		else {
			delete root->right;
		}
	}
};

Node*  BST::Search(int key) {
	return Search(root, key);
};


Node * BST::Search(Node* node, int key) {

	// Base Cases: root is null or key is present at root
	if (node == nullptr) { return node; };
	if (node->key == key) { return node; };

	// Key is greater than root's key
	if (node->key < key) { return Search(node->right, key); }

	// Key is smaller than root's key
	return Search(node->left, key);
};

void BST::Insert(int key) {
	return Insert(&root, key);
};

void BST::Insert(Node** node, int key) {
	if (*node == nullptr)
		*node = new Node(key);
	else
	{
		//key is smaller than key in current node
		if (key < (*node)->key)
			Insert(&((*node)->left ), key);
		else
		{   //key is greater than key in current node
			if (key > (*node)->key)
				Insert(&((*node)->right), key);
		    //key duplicate ignored
		
		}
	}
} 



void BST::PreOrder()
{	
	PreOrder(root);
}

void BST::InOrder()
{
	InOrder(root);
}

void BST::PostOrder()
{
	PostOrder(root);
}


void BST::PreOrder(Node *node)
{
	if (node != nullptr)
	{
		std::cout << node->key << " ";
		PreOrder(node->left);
		PreOrder(node->right);
	}
}

void BST::InOrder(Node *node)
{
	if (node != nullptr)
	{
		InOrder(node->left);
		std::cout << node->key << " ";
		InOrder(node->right);

	}
}

void BST::PostOrder(Node *node)
{
	if (node != nullptr)
	{

		PostOrder(node->left);
		PostOrder(node->right);
		std::cout << node->key << " ";

	}
}

inline int BST::GetNumberNodes()
{
	int cont;
	cont += GetNumberNodes(root->left) + GetNumberNodes(root->right);
	return cont;
}

inline int BST::GetNumberNodes(Node *nodo) // Desde un nodo
{
	int contador;
	//Recursiva
	if (nodo != NULL)
	{
		
		contador++;// Sumamos el nodo en el que estamos
		GetNumberNodes(nodo->left); // Sumamos los nodos izq
		GetNumberNodes(nodo->right); // Sumamos los nodos der
	}
	return contador;
}

inline int BST::GetNumberNodesl()
{
	// NO Recursiva
	return 0;
}

inline void BST::PreOrderl()
{

}

inline int BST::Height()
{
	if (Height(root->left) > Height(root->right))
	{
		return Height(root->left);
	}
		return Height(root->right);
}

inline int BST::Height(Node * node)
{
	int cont;
	if (node != NULL)
	{
		if (node->left != NULL || node->right != NULL)
		{
			cont++;
			Height(node->left);
			Height(node->right);
		}
	}
	else{
		return 0;
	}

}

bool BST::Exist(int key) {

	return !(Search(key) == nullptr);
	
};
