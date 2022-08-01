#include "dynamic-stack.h"
#include <iostream>

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
    init_capacity_ = 16;
    capacity_ = 16;
    size_ = 0;
    items_ = new StackItem[init_capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity){
    init_capacity_ = capacity;
    capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[init_capacity_];
}

DynamicStack::~DynamicStack() {
    delete []items_;
}

bool DynamicStack::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

int DynamicStack::size() const {
    return size_;
}

void DynamicStack::push(StackItem value) {
    if (size_ == capacity_) {
        capacity_ *= 2;
        StackItem* temp = new StackItem[capacity_];
        for (int i = 0; i < size_; i++) {
            temp[i] = items_[i];
        }
        StackItem* old_items = items_;
        items_ = temp;
        delete [] old_items;
    }
    items_[size_] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {
    if (size_ == 0) {
        return EMPTY_STACK;
    }
    size_--;
    if ((size_ <= capacity_/4) && (capacity_/2 >= init_capacity_)) {
        capacity_ /= 2;
        StackItem* temp = new StackItem[capacity_];
        for (int i = 0; i < size_; i++) {
            temp[i] = items_[i];
        }
        StackItem* old_items = items_;
        items_ = temp;
        delete [] old_items;
    }
    return items_[size_];
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (size_ == 0) {
        return EMPTY_STACK;
    }
    return items_[size_-1];
}

void DynamicStack::print() const {
    if (size_ == 0) {
        std::cout << EMPTY_STACK << std::endl;
        return;
    }

    for (int i = size_-1; i >= 0; i--) {
        std::cout << items_[i] << " ";
    }
    std::cout << std::endl;
}