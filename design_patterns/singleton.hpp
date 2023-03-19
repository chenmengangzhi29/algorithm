// 单例模式定义： 
// 保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。
// 必须保证：（1）该类不能被复制。（2）该类不能被公开的创造。 
// 对于C++来说，它的构造函数，拷贝构造函数和赋值函数都不能被公开调用。

//单例模式通常有两种模式，分别为懒汉式单例和饿汉式单例。
// 两种模式实现方式分别如下：
//（1）懒汉式模式： a.静态指针 + 用到时初始化 b.局部静态变量
//（2）饿汉式模式： a.直接定义静态对象 b.静态指针 + 类外初始化时new空间实现

//（1）懒汉实现一： 静态指针 + 用到时初始化
// <线程不安全><newc出来的没释放>
#include <cstddef>
class Singleton
{
public:
static Singleton& geInstance(){
    if(!value_){
        value_ = new Singleton();
    }
    return *value_;
}
private:
    Singleton(){};
    static Singleton* value_;
};
Singleton* Singleton::value_ = NULL;

// (2)懒汉实现二：局部静态指针
//<线程不安全><多个单例对象的析构顺序有依赖时，可能会出现程序崩溃>
#include <cstddef>
class Singleton
{
public:
static Singleton& geInstance(){
    static Singleton instance;
    return instance;
}
private:
    Singleton(){};
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
};

// (3)饿汉实现一：直接定义静态对象
// 优点：线程安全，实现简单
// 缺点：存在多个单例对象且这几个单例对象相互依赖时可能会程序崩溃，因为静态
//       成员变量初始化顺序和析构顺序是未定义的。
//       在程序开始就创建类的实例，如果Singleton对象产生很昂贵，而本身很少使//       用，资源利用率比较低。
// 使用条件：当肯定不会有构造和析构依赖关系的情况。
//			想避免频繁加锁时的性能消耗
#include <cstddef>
class Singleton
{
public:
static Singleton& geInstance(){
    return instance_;
}
private:
    Singleton(){};
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    static Singleton instance_;
};
Singleton Singleton::instance_;
//函数调用
Singleton& instance = Singleton::geInstance();

// （4）饿汉实现二：静态指针+类外初始化时new空间实现
// <线程安全>
#include <cstddef>
class Singleton
{
public:
static Singleton* geInstance(){
    return instance_;
}
private:
    Singleton(){};
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    static Singleton* instance_;
};
Singleton* Singleton::instance_ = new Singleton;
//函数调用
Singleton* instance = Singleton::geInstance();
