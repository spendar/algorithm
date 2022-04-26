/*
 * @Author: spendar
 * @Date: 2022-04-04 21:21:35
 * @LastEditTime: 2022-04-26 18:15:47
 * @LastEditors: Please set LastEditors
 * @Description: to implement a lru cache with expired time
 * @FilePath: \Cache\LruCache.h
 */
#include <unordered_map>
#include <list>  
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>



template<typename K, typename V>
class Node {
public:
    K key;
    V val;
    std::chrono::steady_clock::time_point timestamp;
    Node* pre;
    Node* next;
    Node(): pre(NULL), next(NULL) {}
    Node(K& key, V& val, std::chrono::steady_clock::time_point timestamp): key(key), val(val), timestamp(timestamp), pre(NULL), next(NULL) {} 
};

template<typename K, typename V>
class LruCache {
public:
    LruCache(int capacity, int ttl = 10000) : capacity_(capacity), ttl_(ttl), size_(0), isStop_(false) {
        head_ = new Node<K,V>();
        tail_ = new Node<K,V>();
        head_->next = tail_;
        tail_->pre = head_;
    }
    
    ~LruCache() {
        isStop_ = true;
        daemon_->join();
    }

    bool get(K key, V& data) {
        std::lock_guard<std::mutex> locker(mtx_);
        auto iter = m_.find(key);
        if(iter == m_.end()) {
            return false;
        } else {
            Node<K, V>* temp = iter->second;
            if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - temp->timestamp).count() > ttl_) {
                m_.erase(key);
                erase(temp);
                delete temp;
                size_--;
                return false;
            }
            erase(temp);
            add(temp);
            data = temp->val;
            return true;
        }
    }

    void put(K key, V val) {
        std::lock_guard<std::mutex> locker(mtx_);
        auto iter = m_.find(key);
        if(iter == m_.end()) {
            if(size_ >= capacity_) {
                Node<K,V>* temp = tail_->pre;
                erase(temp);
                delete temp;
                m_.erase(temp->key);
                size_--;
            }
            Node<K, V>* temp = new Node<K,V>(key, val, std::chrono::steady_clock::now());
            add(temp);
            m_[key] = temp;
            size_++;
        } else {
            Node<K, V>* temp = m_[key];
            erase(temp);
            temp->val = val;
            temp->timestamp = std::chrono::steady_clock::now();
            add(temp);
        }
    }

    int size() {
        std::lock_guard<std::mutex> locker(mtx_);
        return size_;
    }

    void print() {
        Node<K, V>* cur = head_->next;
        while(cur != tail_) {
            std::cout<<cur->key<<" ";
            cur = cur->next;
        }
        std::cout<<std::endl;
    }

    void clean() {
        while(!isStop_) {
            std::this_thread::sleep_for(std::chrono:: milliseconds (1000));
            {
                std::lock_guard<std::mutex> locker(mtx_);
                // 清理过期键值对
                Node<K, V>* cur = head_->next;
                while(cur != tail_) {
                    // std::cout<<cur->key<<" ";
                    Node<K, V>* temp = cur->next;
                    if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - cur->timestamp).count() > ttl_) {
                        erase(cur);
                        m_.erase(cur->key);
                        delete cur;
                        size_--;
                    }
                    cur = temp;
                }
                // std::cout<<std::endl;
            }
        }
    }

private:
    void erase(Node<K, V>* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void add(Node<K, V>* node) {
        head_->next->pre = node;
        node->next = head_->next;
        node->pre = head_;
        head_->next = node;
    }

private:
    int capacity_;
    int size_;
    bool isStop_;    
    int ttl_;
    std::mutex mtx_;
    std::unordered_map<K, Node<K, V>*> m_;
    Node<K, V>* head_;
    Node<K, V>* tail_;
    std::unique_ptr<std::thread> daemon_ = std::make_unique<std::thread>(&LruCache<K, V>::clean, this);
};