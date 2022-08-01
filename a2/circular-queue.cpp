#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
    capacity_ = 16;
    head_ = 0;
    tail_ = 0;
    size_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity;
    tail_ = 0;
    head_ = 0;
    size_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::~CircularQueue() {
    delete []items_;
}

bool CircularQueue::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

bool CircularQueue::full() const {
    if (size_ == capacity_) {
        return true;
    } else {
        return false;
    }
}

int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    if (size_ == capacity_) {
        return false;
    }
    items_[tail_] = value;
    size_++;
    if (tail_ == capacity_-1) {
        tail_ = 0;
    } else {
        tail_++;
    }
    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if (size_ == 0) {
        return EMPTY_QUEUE;
    }
    QueueItem return_item = items_[head_];
    size_--;
    if (head_ == capacity_-1) {
        head_ = 0;
    } else {
        head_++;
    }
    return return_item;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (size_ == 0) {
        return EMPTY_QUEUE;
    }
    return items_[head_];
}

void CircularQueue::print() const {
    if (size_ == 0) {
        std::cout << EMPTY_QUEUE << std::endl;
        return;
    }

    for (int i = 0; i < size_; i++) {
        std::cout << items_[i] << " ";
    }
    std::cout << std::endl;
}

