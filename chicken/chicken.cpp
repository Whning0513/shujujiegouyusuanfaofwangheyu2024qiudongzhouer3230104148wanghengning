#include <iostream>
#include <cstring>

#include <iostream>
#include <cstring>

class Chicken
{
    private:
        int age = 24;
        char *name = nullptr;

    public:
        Chicken() {};
        Chicken(int _age) : age(_age) {};
        Chicken(int _age, const char *_name) : age(_age)
        {
            copyName(_name);
        }

        // 复制构造函数，深度拷贝
        Chicken(const Chicken &other)
        {
            age = other.age;
            copyName(other.name);
        }

        // 重新定义赋值运算符，支持深度拷贝和连续赋值
        Chicken& operator=(const Chicken &other)
        {
            if (this != &other)
            {
                age = other.age;
                delete[] name;  // 释放旧的内存
                copyName(other.name);  // 拷贝新的name
            }
            return *this;  // 返回当前对象的引用，支持连续赋值
        }

        // 名称拷贝函数，用于深度拷贝
        void copyName(const char *_name)
        {
            if (_name)
            {
                int len = strlen(_name) + 1;
                name = new char[len];
                strcpy(name, _name);
            }
            else
            {
                name = nullptr;
            }
        }

        // 析构函数，释放动态内存，防止内存泄漏
        ~Chicken()
        {
            delete[] name;
        }

        // 设置年龄
        void setAge(int _age)
        {
            age = _age;
        }

        // 设置名字，支持深度拷贝
        void setName(const char *_name)
        {
            delete[] name;  // 释放旧的内存
            copyName(_name);  // 深度拷贝新的name
        }

        // 获取名字，返回 const char* 防止修改
        const char* getName() const
        {
            return name;
        }

        // 获取年龄，返回 const int&，防止修改
        const int& getAge() const
        {
            return age;
        }
};

/* 以下是助教老师提供的main代码 */

int main(){
auto print = [](const Chicken &c){
std::cout << "Hi, everyone! My name is " << c.getName()
<< ", I am " << c.getAge() << " years old." << std::endl;
};
Chicken c(24, "Kunkun");
print(c);
Chicken d;
d = c;
print(d); // 测试【赋值运算符】是否正确，能正确输出给 20 分
Chicken a = c;
print(a); // 测试【赋值构造函数】是否正确，能正确输出给 20 分
c.setName("Xukun Cai");
print(c);
print(a);
print(d); // 测试是否为【深度复制】，本行与上两行能正确输出给 20 分
Chicken b;
b = d = c;
print(b);
print(d); // 测试【连续赋值】功能，本行与上一行能正确输出给 20 分
return 0;
}