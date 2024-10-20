#include <iostream>
#include "List.h"

int main() {
    int i;
    std::cout << "  input bug id: ";
    std::cin >> i;

    switch (i) {
        case 1: { // 未初始化的指针
            List<int> myList;
            //std::cout << myList.pop_front() << std::endl; // 可能导致未定义行为
            break;
        }
        case 2: { // 边界检查失败的 front 和 back
            List<int> myList;
            std::cout << "Front: " << myList.front() << std::endl; // 可能导致崩溃
            std::cout << "Back: " << myList.back() << std::endl; // 可能导致崩溃
            break;
        }
        case 3: { // 拷贝构造函数中的悬空指针
            List<int> original;
            original.push_back(10);
            List<int> copy = original; // 拷贝构造
            original.pop_back(); // 原链表被修改
            std::cout << "Copy Front: " << copy.front() << std::endl; // 可能导致崩溃
            break;
        }
        case 4: { // 移动赋值后的内存泄漏
            List<int> list1;
            list1.push_back(1);
            List<int> list2;
            list2 = std::move(list1); // 移动赋值
            list1.pop_front(); // 可能导致未定义行为
            break;
        }
        case 5: { // 指针链接错误
            List<int> myList;
            myList.push_back(1);
            myList.push_back(2);
            auto it = myList.begin();
            myList.insert(it, 3); // 可能导致链表结构破坏
            std::cout << "Iterator: " << *it << std::endl; // 可能导致崩溃
            break;
        }
        case 6: { // 调用 erase 后使用迭代器
            List<int> myList;
            myList.push_back(1);
            myList.push_back(2);
            auto it = myList.begin();
            myList.erase(it); // 删除第一个元素
            std::cout << "Iterator after erase: " << *it << std::endl; // 可能导致未定义行为
            break;
        }
        case 7: { // 删除第2到倒数第二个元素
            List<int> myList;
            myList.push_back(1);
            myList.push_back(2);
            myList.push_back(3);

            auto it1 = myList.begin();
            ++it1; // 指向第二个元素
            auto it2 = myList.end();
            ++it2; // 指向第四个元素（实际上并没有这个元素）

            myList.erase(it1,it2);


            for (auto it = myList.begin(); it != myList.end(); ++it) {
            std::cout << *it << " ";
            }
            std::cout << std::endl;
            break;
        }
        case 8:{
            List<int> mylist;
            mylist.push_back(1);
            mylist.push_back(2);
            mylist.push_back(3);

            // 清空链表
            mylist.clear();

            // 尝试打印链表
            std::cout << "neirong:";
            mylist.print();
        }
        default:
            std::cout << "无效输入，请输入 1 到 6 之间的数字。" << std::endl;
            break;
    }

    return 0;
}
