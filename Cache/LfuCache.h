/*
 * @Author: spendar
 * @Date: 2022-04-04 21:21:35
 * @LastEditTime: 2022-04-26 17:04:17
 * @LastEditors: Please set LastEditors
 * @Description: to implement a lfu cache with expired time
 * @FilePath: \Cache\LruCache.h
 */
#include <unordered_map>
#include <list>  
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>



template<typename K, typename V>
class Node {
public:
    K key;
    V val;
    int click;
    std::chrono::steady_clock::time_point timestamp;
    Node* pre;
    Node* next;
    Node(): pre(NULL), next(NULL) {}
    Node(K& key, V& val, std::chrono::steady_clock::time_point timestamp): key(key), val(val), click(1), timestamp(timestamp), pre(NULL), next(NULL) {} 
};

template<typename K, typename V>
class LfuCache {
public:
    LfuCache(int capacity, int ttl = 10000) : capacity_(capacity), ttl_(ttl), size_(0), minClick_(0), isStop_(false) {}
    
    ~LfuCache() {
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
                return false;
            }
            erase(temp);
            temp->click++;
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
                Node<K,V>* temp = tails_[minClick_]->pre;
                erase(temp);
                m_.erase(temp->key);
                delete temp;
                size_--;
            }
            Node<K, V>* temp = new Node<K,V>(key, val, std::chrono::steady_clock::now());
            add(temp);
            m_[key] = temp;
            size_++;
            minClick_ = 1;
        } else {
            Node<K, V>* temp = m_[key];
            erase(temp);
            temp->val = val;
            temp->timestamp = std::chrono::steady_clock::now();
            temp->click++;
            add(temp);
        }
    }

    int size() {
        std::lock_guard<std::mutex> locker(mtx_);
        return size_;
    }

    void print() {
        for(auto& kv : m_) {
            std::cout<<kv.first<<" ";
        }
        std::cout<<std::endl;
    }

    void clean() {
        while(!isStop_) {
            std::this_thread::sleep_for(std::chrono:: milliseconds (3000));
            {
                std::lock_guard<std::mutex> locker(mtx_);
                minClick_ = 0;
                // 清理过期键值对
                std::vector<int> keys;
                for(auto iter = m_.begin(); iter != m_.end(); iter++) {
                    Node<K,V>* temp = (*iter).second;
                    if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - temp->timestamp).count() > ttl_) {
                        erase(temp);
                        keys.push_back((*iter).first);
                        size_--;
                    } else {
                        if(!minClick_) {
                            minClick_ = temp->click;
                        } else {
                            minClick_ = std::min(minClick_, temp->click);
                        }
                    }
                }
                for(auto key : keys) {
                    m_.erase(key);
                }
            }
        }
    }

private:
    void erase(Node<K, V>* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
        if(!node->pre->pre && !node->next->next) {
            heads_.erase(node->click);
            tails_.erase(node->click);
            if(node->click == minClick_) {
                minClick_ = node->click + 1;
            }
        }
    }

    void add(Node<K, V>* node) {
        int click = node->click;
        if(!heads_.count(click)) {
            heads_[click] = new Node<K, V>();
            tails_[click] = new Node<K, V>();
            heads_[click]->next = tails_[click];
            tails_[click]->pre = heads_[click];
        }
        node->next = heads_[click]->next;
        heads_[click]->next->pre = node;
        node->pre = heads_[click];
        heads_[click]->next = node;
    }

private:
    int capacity_;
    int size_;
    bool isStop_;    
    int ttl_;
    int minClick_;
    std::mutex mtx_;
    std::unordered_map<K, Node<K, V>*> m_;
    std::unordered_map<int, Node<K, V>*> heads_;
    std::unordered_map<int, Node<K, V>*> tails_;
    std::unique_ptr<std::thread> daemon_ = std::make_unique<std::thread>(&LfuCache<K, V>::clean, this);
};
