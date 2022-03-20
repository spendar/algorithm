/*
 * @Author: Spendar
 * @Date: 2022-03-20 21:52:18
 * @LastEditTime: 2022-03-20 22:20:46
 * @LastEditors: Please set LastEditors
 * @Description: 单例模式懒汉版本
 * @FilePath: \algorithm\DesignPattern\Singleton\singleton.cpp
 */

class Singleton {
private:
    static Singleton* instance;
    Singleton() {};
    ~Singleton() {};
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
public:
    static Singleton* getInstance() {
        if(!instance) {
            instance = new Singleton();
        }
        return instance;
    }
};



/*
 * @Author: Spendar
 * @Date: 2022-03-20 21:52:18
 * @LastEditTime: 2022-03-20 22:03:55
 * @LastEditors: Spendar
 * @Description: 单例模式饿汉版本，利用静态局部变量的特性保证只被初始化一次
 * @FilePath: \algorithm\DesignPattern\Singleton\singleton.cpp
 */

class Singleton {
private:
    Singleton() {};
    ~Singleton() {};
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
public:
    static Singleton* getInstance() {
        static Singleton* instance = new Singleton();
        return instance;
    }
};
