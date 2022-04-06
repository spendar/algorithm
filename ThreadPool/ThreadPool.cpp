#include "ThreadPool.h"

ThreadPool::ThreadWorker::ThreadWorker(ThreadPool* pool, const int id) {
    this->m_pool = pool;
    this->m_id = id;
}

void ThreadPool::ThreadWorker::operator()() {
    std::function<void()> func;
    bool dequeued; //标记是否成功从队列中去除元素
    while(!m_pool->m_shutdown) {
        std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
        if(m_pool->m_queue.empty()) {
            m_pool->m_conditional_lock.wait(lock);
        }
        dequeued = m_pool->m_queue.dequeue(func);
        if(dequeued) {
            func();
        }
    }
}

ThreadPool::ThreadPool(const int n_thread) {
    m_threads.resize(n_thread);
    m_shutdown = false;
}

void ThreadPool::init() {
    for(int i = 0; i < m_threads.size(); i++) {
        m_threads[i] = std::thread(ThreadWorker(this, i));
    }
}

void ThreadPool::shutdown() {
    m_shutdown = true;
    m_conditional_lock.notify_all();
    for(int i = 0; i < m_threads.size(); i++) {
        if(m_threads[i].joinable()) {
            m_threads[i].join();
        }
    }
}

template<typename F, typename...Args>
auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    std::function<decltype(f(args...)())> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>(func);
    std::function<void()> wrapper_func = []() {
        (*tast_ptr)();
    }
    m_queue.enqueue(wrapper_func);
    m_conditional_lock.notify_one();
    return task_ptr->get_future();
}
