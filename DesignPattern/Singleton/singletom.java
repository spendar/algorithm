/*
 * @Author: spendar
 * @Date: 2022-03-20 22:38:20
 * @LastEditTime: 2022-03-20 22:43:47
 * @LastEditors: Please set LastEditors
 * @Description: 单例模式饿汉版本
 * @FilePath: \algorithm\DesignPattern\Singleton\singletom.java
 */
public class Singleton {

    private static Singleton instance = new Singleton();

    private Singleton() {}

    public static Singleton getInstance() {
        return instance;
    }
}

/*
 * @Author: spendar
 * @Date: 2022-03-20 22:38:20
 * @LastEditTime: 2022-03-20 22:40:09
 * @LastEditors: spendar
 * @Description: 单例模式懒汉版本
 * @FilePath: \algorithm\DesignPattern\Singleton\singletom.java
 */
public class Singleton {

    private static Singleton instance = null;

    private Singleton() {}
    
    public static Singleton getInstance() {
        if(instance == null) {
            instance = new Singleton();
        }
        return instance;
    }
}

/*
 * @Author: spendar
 * @Date: 2022-03-20 22:38:20
 * @LastEditTime: 2022-03-20 22:40:09
 * @LastEditors: spendar
 * @Description: 单例模式懒汉版本
 * @FilePath: \algorithm\DesignPattern\Singleton\singletom.java
 */
public class Singleton {

    private static volatile Singleton instance = null;

    private Singleton() {}
    
    public static Singleton getInstance() {
        if(instance == null) {
            synchronized (Singleton.class) {
                if(instance == null) {
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }
}

