#include "binary-search-tree.h"
#include <iostream>
#include <queue>

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    right = nullptr;
    left = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if (n == nullptr) {
        return 0;
    } else {
        return std::max(getNodeDepth(n ->left), getNodeDepth(n ->right)) + 1;
    }
}

BinarySearchTree::BinarySearchTree()
{
    size_ = 0;
    root_ = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
    if (root_ == nullptr) {
        return;
    }

    std::queue<Node *> temp_queue;
    Node* currentNode;
    temp_queue.push(root_);

    while (true) {
        currentNode = temp_queue.front();

        if (currentNode -> left == nullptr && currentNode -> right == nullptr) {
            temp_queue.pop();
            delete currentNode;
        } else if (currentNode -> right == nullptr) {
            temp_queue.push(currentNode -> left);
            temp_queue.pop();
            delete currentNode;
        } else if (currentNode -> left == nullptr) {
            temp_queue.push(currentNode -> right);
            temp_queue.pop();
            delete currentNode;
        } else {
            temp_queue.push(currentNode -> left);
            temp_queue.push(currentNode -> right);
            temp_queue.pop();
            delete currentNode;
        }

        if (temp_queue.empty()) {
            break;
        }
    }
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
    Node* currentNode = root_;
    while(currentNode -> right != nullptr) {
        currentNode = currentNode -> right;
    }
    return currentNode -> val;
}

BinarySearchTree::DataType BinarySearchTree::min() const
{
    Node* currentNode = root_;
    while(currentNode -> left != nullptr) {
        currentNode = currentNode -> left;
    }
    return currentNode -> val;
}

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_) - 1;
}

void BinarySearchTree::print() const
{
    if (size_ == 0) {
        return;
    }

    std::queue<Node *> temp_queue;
    Node* currentNode;
    temp_queue.push(root_);
    std::cout << root_ -> val << " ";

    while (true) {
        currentNode = temp_queue.front();

        if (currentNode -> left == nullptr && currentNode -> right == nullptr) {
            temp_queue.pop();
        } else if (currentNode -> right == nullptr) {
            std::cout << currentNode -> left -> val << " ";
            temp_queue.push(currentNode -> left);
            temp_queue.pop();
        } else if (currentNode -> left == nullptr) {
            std::cout << currentNode -> right -> val << " ";
            temp_queue.push(currentNode -> right);
            temp_queue.pop();
        } else {
            std::cout << currentNode -> left -> val << " ";
            std::cout << currentNode -> right -> val << " ";

            temp_queue.push(currentNode -> left);
            temp_queue.push(currentNode -> right);
            temp_queue.pop();
        }

        if (temp_queue.empty()) {
            break;
        }
    }
    std::cout<<std::endl;
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* currentNode = root_;

    while(currentNode != nullptr) {

        if (currentNode -> val == val) {
            return true;
        }

        if (currentNode -> val > val) {
            currentNode = currentNode ->left;
        } else {
            currentNode = currentNode ->right;
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    Node *new_node = new Node(val);

    if (size_ == 0) {
        root_ = new_node;
        size_++;
        return true;
    }

    if (exists(val)) {
        return false;
    }

    Node* currentNode = root_;

    while (true) {
        if (currentNode -> val > val) {
            if (currentNode -> left == nullptr) {
                break;
            }
            currentNode = currentNode -> left;
        } else {
            if (currentNode -> right == nullptr) {
                break;
            }
            currentNode = currentNode -> right;
        }
    }

    if (currentNode -> val > val) {
        currentNode -> left = new_node;
    } else {
        currentNode -> right = new_node;
    }

    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val)
{
    if (!exists(val)) {
        return false;
    }

    Node* currentNode = root_;
    Node** parentAddress;
    Node* child_node;
    Node* new_node;

    if (val == root_ -> val) {
        if (root_ -> right != nullptr && root_ -> left != nullptr) {

            int minimum;
            Node* root_sub = root_ -> right;

            while(root_sub -> left != nullptr) {
                root_sub = root_sub -> left;
            }

            minimum = root_sub -> val;
            this -> remove(minimum);
            root_ -> val = minimum;
        } else if (root_ -> left != nullptr) {
            new_node = root_ -> left;
            delete root_;
            root_ = new_node;
        } else if (root_ -> right != nullptr) {
            new_node = root_ -> right;
            delete root_;
            root_ = new_node;
        } else {
            delete root_;
            root_ = nullptr;
        }
        size_--;
        return true;
    }


    while(true) {
        if (currentNode -> left != nullptr && currentNode -> right != nullptr) {
            if (currentNode -> left -> val == val || currentNode -> right -> val == val) {
                break;
            } else if (currentNode -> val > val) {
                currentNode = currentNode -> left;
            } else {
                currentNode = currentNode -> right;
            }
        } else if (currentNode -> left != nullptr) {
            if (currentNode -> left -> val == val) {
                break;
            } else {
                currentNode = currentNode -> left;
            }
        } else if (currentNode -> right != nullptr) {
            if (currentNode -> right -> val == val) {
                break;
            } else {
                currentNode = currentNode -> right;
            }
        }
    }

    if (currentNode -> right != nullptr) {
        if (currentNode -> right -> val == val) {
            parentAddress = &currentNode -> right;
            child_node = currentNode -> right;
        } else {
            parentAddress = &currentNode -> left;
            child_node = currentNode -> left;
        }
    } else {
        parentAddress = &currentNode -> left;
        child_node = currentNode -> left;
    }

    if (child_node -> right != nullptr && child_node -> left != nullptr) {
        int minimum;
        Node* kid_subnode = child_node -> right;

        while(kid_subnode -> left != nullptr) {
            kid_subnode = kid_subnode -> left;
        }

        minimum = kid_subnode -> val;
        this -> remove(minimum);
        child_node -> val = minimum;
    } else if (child_node -> left != nullptr) {
        new_node = child_node -> left;
        delete child_node;
        child_node = nullptr;
        *parentAddress = new_node;
    } else if (child_node -> right != nullptr) {
        new_node = child_node -> right;
        delete child_node;
        child_node = nullptr;
        *parentAddress = new_node;
    } else{
        delete child_node;
        child_node = nullptr;
        *parentAddress = nullptr;
    }
    size_--;
    return true;
}