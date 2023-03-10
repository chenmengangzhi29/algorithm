#include <cstddef>
// 单例模式定义： 
// 保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。
// 必须保证：（1）该类不能被复制。（2）该类不能被公开的创造。 
// 对于C++来说，它的构造函数，拷贝构造函数和赋值函数都不能被公开调用。

//单例模式通常有两种模式，分别为懒汉式单例和饿汉式单例。
// 两种模式实现方式分别如下：
//（1）懒汉式模式： a.静态指针 + 用到时初始化 b.局部静态变量
//（2）饿汉式模式： a.直接定义静态对象 b.静态指针 + 类外初始化时new空间实现

//（1）懒汉实现一： 静态指针 + 用到时初始化
// <线程不安全>
template <typename T>
class Singleton
{
public:
static T& geInstance(){
    if(!value_){
        value_ = new T();
    }
    return *value_;
}
private:
    Singleton();    
    ~Singleton();
    static T* value_;
};
template<typename T>
T* Singleton<T>::value_ = NULL;