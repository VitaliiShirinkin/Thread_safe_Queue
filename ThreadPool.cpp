#include "ThreadPool.h"
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>

ThreadPool::ThreadPool(int cores) {
    done = false;
    size_t const thread_count = std::thread::hardware_concurrency();
    for (size_t i = 0; i < cores; ++i) {
        threadsVector.push_back(
            std::thread(&ThreadPool::work, std::move(this)));
    }
}

ThreadPool::~ThreadPool() {
    done = true;
    for (size_t i = 0; i < threadsVector.size(); ++i) {
        /*if (threadsVector[i].joinable())*/
            threadsVector[i].join();
    }
}


void ThreadPool:: work() {
    while (!done) {
        std::function<void()> task;
        if (workQueue.pop(task)) {
            task();
        }
        else {
            std::this_thread::yield();
        }
    }
}