#include "avl-tree.h"
#include <iostream>

bool AVLTree::insert(DataType val)
{
    if (!BinarySearchTree::insert(val)) {
        return false;
    } else {
        nodeBalance(BinarySearchTree::getRootNode());
        return true;
    }
}

bool AVLTree::remove(DataType val)
{
    if (!BinarySearchTree::remove(val)) {
        return false;
    } else {
        nodeBalance(BinarySearchTree::getRootNode());
        return true;
    }
}

void AVLTree::rightRotation(Node* node)
{
    Node* temp = new Node(node -> val);
    temp -> left = node -> left -> right;
    temp -> right = node -> right;

    node -> right = temp;
    node -> val = node -> left -> val;
    node -> left = node -> left -> left;
}

void AVLTree::leftRotation(Node* node)
{
    Node* temp = new Node(node -> val);
    temp -> right = node -> right -> left;
    temp -> left = node -> left;

    node -> left = temp;
    node -> val = node -> right -> val;
    node -> right = node -> right -> right;
}

int AVLTree::getNodeDepth(BinarySearchTree::Node *n) const
{
    if (n == nullptr) {
        return -1;
    } else {
        return std::max(getNodeDepth(n -> right), getNodeDepth(n -> left)) + 1;
    }
}

int AVLTree::treeBalanceNum(Node *node)
{
    int leftNum = getNodeDepth(node -> left);
    int rightNum = getNodeDepth(node -> right);
    return leftNum - rightNum;
}

void AVLTree::nodeBalance(BinarySearchTree::Node *node)
{
    if (node == nullptr) {
        return;
    }

    nodeBalance(node -> right);
    nodeBalance(node -> left);
    int balance_num = treeBalanceNum(node);

    if ((balance_num < -1) && (treeBalanceNum(node->right) > 0)) {
        rightRotation(node -> right);
        return leftRotation(node);
    } else if (balance_num < -1) {
        return leftRotation(node);
    } else if ((balance_num > 1) && (treeBalanceNum(node->left) < 0)) {
        leftRotation(node -> left);
        return rightRotation(node);
    } else if (balance_num > 1) {
        return rightRotation(node);
    }
}