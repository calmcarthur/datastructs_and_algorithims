#include "doubly-linked-list.h"
#include <iostream>

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = nullptr;
    prev = nullptr;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_ -> next;
        delete temp;
    };
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

bool DoublyLinkedList::full() const
{
    return size_ == CAPACITY;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (empty() || index >= size_) {
        return tail_-> value;
    }

    return getNode(index) -> value;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    Node* currentNode = head_;
    unsigned int counter = 0;

    while (counter < size_) {
        if (currentNode -> value == value) {
            return counter;
        }
        counter++;
        currentNode = currentNode -> next;
    }

    return size_;
}

void DoublyLinkedList::print() const
{
    Node* currentNode = head_;
    unsigned int counter = 0;

    while (currentNode != nullptr) {
        std::cout << currentNode -> value << std::endl;
        currentNode = currentNode -> next;
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    Node* currentNode = head_;
    unsigned int counter = 0;

    while (counter != index) {
        currentNode = currentNode -> next;
        counter++;
    }

    return currentNode;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if (index > size_ || full()) {
        return false;
    }

    if (index == size_) {
        return insert_back(value);
    }
    if (index == 0) {
        return insert_front(value);
    }

    Node* currentNode = getNode(index);
    Node* newNode = new Node(value);

    newNode -> prev = currentNode -> prev;
    newNode -> next = currentNode;

    currentNode -> prev -> next = newNode;
    currentNode -> prev = newNode;

    size_++;
    return true;
}

bool DoublyLinkedList::insert_front(DataType value)
{
    if (full()) {
        return false;
    }

    Node* newNode = new Node(value);

    if (size_ == 0) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        newNode -> next = head_;
        head_ -> prev = newNode;

        head_ = newNode;
    }

    size_++;
    return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
    if (full()) {
        return false;
    }

    Node* newNode = new Node(value);

    if (size_ == 0) {
        return insert_front(value);
    } else {
        newNode -> prev = tail_;
        tail_ -> next = newNode;

        tail_ = newNode;
    }

    size_++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if (empty() || index >= size_) {
        return false;
    }

    if (index == 0) {
        return remove_front();
    }
    if (index == size_ - 1) {
        return remove_back();
    }

    Node* currentNode = getNode(index);

    currentNode -> prev -> next = currentNode -> next;
    currentNode -> next -> prev = currentNode -> prev;

    delete currentNode;

    size_--;
    return true;
}

bool DoublyLinkedList::remove_front()
{
    if (empty()) {
        return false;
    }

    head_ = head_ -> next;

    if (head_ != nullptr) {
        head_ -> prev = nullptr;
    } else {
        tail_ = nullptr;
    }

    size_--;
    return true;
}

bool DoublyLinkedList::remove_back()
{
    if (empty()) {
        return false;
    }

    tail_ = tail_ -> prev;

    if (tail_ != nullptr) {
        tail_ -> next = nullptr;
    } else {
        head_ = nullptr;
    }

    size_--;
    return true;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if (index > size_) {
        return false;
    }

    Node* currentNode = getNode(index);
    currentNode -> value = value;

    return true;
}
