#pragma once
#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>


template<class T>
class SafeQueue {
public:
    SafeQueue() {}

    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mutexQueue);
        tasksQueue.push(std::move(new_value));
        var.notify_one();
    }

    bool pop(T& value) {
        std::lock_guard<std::mutex> lk(mutexQueue);
        if (tasksQueue.empty())
            return false;
        value = std::move(tasksQueue.front());
        tasksQueue.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mutexQueue);
        return tasksQueue.empty();
    }

private:
    std::mutex mutexQueue;
    std::queue<T> tasksQueue;
    std::condition_variable var;
};
