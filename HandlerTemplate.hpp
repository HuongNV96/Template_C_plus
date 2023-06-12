#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <stdbool.h>

using namespace std::chrono_literals;

struct Event {
    int type;
    void * data;
    std::function<void(void*)> handle;
};

template <class T> class HandlerTemplate {
private :
    std::thread mLoop{[this](){this->run();}};
    std::queue<std::unique_ptr<T>> mQueue;
    std::mutex mLock;
    std::condition_variable mCond;
    std::atomic<bool> mExit{false};

    std::unique_ptr<T> getMessage() {
        const std::lock_guard<std::mutex> lock(mLock);
        if (mQueue.empty()) {
            return nullptr;
        }
        auto message = std::make_unique<T>(*mQueue.front().get());
        mQueue.pop();
        return message;
    }

    void run() {
        while(!mExit) {
            auto message = getMessage();
            if (message) {
                handle(message);
            } else {
                std::unique_lock<std::mutex> lock(mLock);
                mCond.wait_for(lock, 100ms);
            }
        }
    }

public :
    HandlerTemplate() = default;
    virtual ~HandlerTemplate() {
        mExit = true;
        if (mLoop.joinable()) {
            mLoop.join();
        }
    }

    void sendMessage(T & message) {
        const std::lock_guard<std::mutex> lock(mLock);
        mQueue.emplace(std::make_unique<T>(message));
        mCond.notify_one();
    }

    void sendMessage(T && message) {
        const std::lock_guard<std::mutex> lock(mLock);
        mQueue.emplace(std::make_unique<T>(message));
        mCond.notify_one();
    }

    virtual void handle(std::unique_ptr<T> & message) = 0;
};