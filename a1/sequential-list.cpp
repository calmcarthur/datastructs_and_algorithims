#include <cstdlib>
#include <iostream>
#include "sequential-list.h"

SequentialList::SequentialList(unsigned int cap)
{
    data_ = new DataType[cap];
    capacity_ = cap;
    size_ = 0;
}

SequentialList::~SequentialList()
{
    delete data_;
    data_ = NULL;
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

bool SequentialList::full() const
{
    if (size_ == capacity_) {
        return true;
    } else {
        return false;
    }
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if (empty()) {
        return data_[0];
    } else if (index >= size_) {
        return data_[size_ - 1];
    } else {
        return data_[index];
    }
}

unsigned int SequentialList::search(DataType val) const
{
    for (unsigned int index=0; index < size_; index++) {
        if (data_[index] == val) {
            return index;
        }
    }
    return size_;
}

void SequentialList::print() const
{
    for (unsigned int index=0; index < size_; index++) {
        std::cout << data_[index] << ", " << std::endl;
    }
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if (index > size_ || size_ == capacity_) {
        return false;
    }
    for (unsigned int i=size_; i > index; i--) {
            data_[i] = data_[i-1];
    }
    data_[index] = val;
    size_++;
    return true;
}

bool SequentialList::insert_front(DataType val)
{
    if (size_ == capacity_) {
        return false;
    }
    for (unsigned int index=size_; index > 0; index--) {
        data_[index] = data_[index-1];
    }
    data_[0] = val;
    size_++;
    return true;
}

bool SequentialList::insert_back(DataType val)
{
    if (size_ == capacity_) {
        return false;
    }
    data_[size_] = val;
    size_++;
    return true;
}

bool SequentialList::remove(unsigned int index)
{
    if (empty() || index >= size_) {
        return false;
    }
    for (unsigned int i=index; i < size_; i++) {
        data_[i] = data_[i+1];
    }
    size_--;
    return true;
}

bool SequentialList::remove_front()
{
    if (empty()) {
        return false;
    }
    for (unsigned int i=0; i < size_; i++) {
        data_[i] = data_[i+1];
    }
    size_--;
    return true;
}

bool SequentialList::remove_back()
{
    if (empty()) {
        return false;
    }
    size_--;
    return true;
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (empty() || index > size_) {
        return false;
    }
    data_[index] = val;
    return true;
}

