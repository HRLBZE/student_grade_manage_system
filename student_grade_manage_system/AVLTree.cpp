#include "AVLTree.h"
#include<iostream>


int AVLTree::height(TreeNode* node) {
	return node ? node->height : 0;
}

void AVLTree::updateHeight(TreeNode* node) {
	node->height = (std::max)(height(node->left), height(node->right)) + 1;
}

int AVLTree::getBalance(TreeNode* node) {
	return node ? height(node->left) - height(node->right) : 0;
}

TreeNode* AVLTree::rightRotate(TreeNode* y) {
	TreeNode* x = y->left;
	TreeNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	updateHeight(y);
	updateHeight(x);

	return x;
}

TreeNode* AVLTree::leftRotate(TreeNode* x) {
	TreeNode* y = x->right;
	TreeNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	updateHeight(x);
	updateHeight(y);

	return y;
}

TreeNode* AVLTree::insert(TreeNode* node, const Student_data& data) {
	if (!node) return new TreeNode(data);

	if (data.number < node->data.number)
		node->left = insert(node->left, data);
	else if (data.number > node->data.number)
		node->right = insert(node->right, data);
	else
		return node;

	updateHeight(node);

	int balance = getBalance(node);

	if (balance > 1 && data.number < node->left->data.number)
		return rightRotate(node);

	if (balance < -1 && data.number > node->right->data.number)
		return leftRotate(node);

	if (balance > 1 && data.number > node->left->data.number) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && data.number < node->right->data.number) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

TreeNode* AVLTree::minValueNode(TreeNode* node) {
	TreeNode* current = node;
	while (current->left)
		current = current->left;
	return current;
}

TreeNode* AVLTree::deleteNode(TreeNode* root, int number) {
	if (!root) return root;

	if (number < root->data.number)
		root->left = deleteNode(root->left, number);
	else if (number > root->data.number)
		root->right = deleteNode(root->right, number);
	else {
		if (!root->left || !root->right) {
			TreeNode* temp = root->left ? root->left : root->right;

			if (!temp) {
				temp = root;
				root = nullptr;
			}
			else
				*root = *temp;

			delete temp;
		}
		else {
			TreeNode* temp = minValueNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data.number);
		}
	}

	if (!root) return root;

	updateHeight(root);

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void AVLTree::inOrder(TreeNode* root, std::vector<Student_data>& sortedStudents) {
	if (!root) return;

	inOrder(root->left, sortedStudents);
	sortedStudents.push_back(root->data);
	inOrder(root->right, sortedStudents);
}
