#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>
#include "SafeQueue.h"

class ThreadPool {

private:

    std::atomic_bool done;
    SafeQueue<std::function<void()>> workQueue;
    std::vector<std::thread> threadsVector;

public:
    /*ThreadPool();*/
    ThreadPool(int cores);

    ~ThreadPool();

    void work();

    template<typename FunctionType>
    void submit(FunctionType f) {
        workQueue.push(std::function<void()>(f));
    }
};