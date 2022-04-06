#pragma once

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

#include "SafeQueue.h"

class ThreadPool {
private:

    class ThreadWorker {
        private:

            int m_id; //线程ID

            ThreadPool* m_pool; //所属线程池
        public:

            ThreadWorker(ThreadPool* pool, const int id);

            void operator()();
    };
    
    bool m_shutdown; //线程池关闭状态

    SafeQueue<std::function<void()>> m_queue; //任务队列

    std::vector<std::thread> m_threads; //工作线程队列

    std::mutex m_conditional_mutex; //线程休眠锁互斥变量

    std::condition_variable m_conditional_lock; //线程环境锁

public:

    ThreadPool(const int n_threads);

    ThreadPool(const ThreadPool& ) = delete;

    ThreadPool & operator=(const ThreadPool&) = delete;

    ThreadPool & operator=(ThreadPool &&) = delete;

    void init();

    template<typename F, typename...Args>
    auto submit(F&& f, Args&&...args);

    void shutdown();
    
};