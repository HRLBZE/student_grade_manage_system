#pragma once
#include"Student_data.h"
#include<vector>

struct TreeNode {
	Student_data data;
	TreeNode* left;
	TreeNode* right;
	int height;

	TreeNode(const Student_data& stu) : data(stu), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
	TreeNode* root;

	TreeNode* insert(TreeNode* node, const Student_data& data);
	TreeNode* deleteNode(TreeNode* root, int number);
	void inOrder(TreeNode* root, std::vector<Student_data>& sortedStudents);
	int height(TreeNode* node);
	void updateHeight(TreeNode* node);
	int getBalance(TreeNode* node);
	TreeNode* rightRotate(TreeNode* y);
	TreeNode* leftRotate(TreeNode* x);
	TreeNode* minValueNode(TreeNode* node);

public:
	AVLTree() : root(nullptr) {}
	void insert(const Student_data& data) {
		root = insert(root, data);
	}

	void remove(int number) {
		root = deleteNode(root, number);
	}

	std::vector<Student_data> sort() {
		std::vector<Student_data> sortedStudents;
		inOrder(root, sortedStudents);
		return sortedStudents;
	}
};
