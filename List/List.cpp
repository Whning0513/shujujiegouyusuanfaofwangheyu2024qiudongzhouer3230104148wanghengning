#include <iostream>
#include "List.h"

void testList() {
    printf("-----ceshi List<int>\n");
    // 测试 int 类型列表
    List<int> intList;

    // 测试空列表
    std::cout << "Initial size (should be 0): " << intList.size() << std::endl;
    std::cout << "Is empty (should be true): " << intList.empty() << std::endl;

    // 测试 push_back 和 push_front
    intList.push_back(1);
    intList.push_back(2);
    intList.push_front(3);
    std::cout << "After adding elements (size should be 3): " << intList.size() << std::endl;
    intList.print();  // 打印列表  312
    intList.push_back(4);
    intList.push_back(5);
    intList.push_front(6);
    std::cout << "After adding elements (size should be 6): " << intList.size() << std::endl;
    intList.print();  // 打印列表  631245

    // 测试 front 和 back
    std::cout << "Front (should be 6): " << intList.front() << std::endl;
    std::cout << "Back (should be 5): " << intList.back() << std::endl;

    // 测试迭代器
    std::cout << "Elements in the list: ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    
    // 测试 pop_front 和 pop_back
    intList.pop_front();
    std::cout << "After pop_front (size should be 5): " << intList.size() << std::endl;
    intList.print(); 
    intList.pop_back();
    std::cout << "After pop_back (size should be 4): " << intList.size() << std::endl;
    intList.print();  

    // 测试 clear
    intList.clear();
    std::cout << "After clear (size should be 0): " << intList.size() << std::endl;

    // 测试非法操作：访问空列表的 front 和 back
    try {
        std::cout << "Trying to access front of empty list: " << intList.front() << std::endl;
    } catch (...) {
        std::cout << "Caught exception when accessing front of empty list." << std::endl;
    }

    try {
        std::cout << "Trying to access back of empty list: " << intList.back() << std::endl;
    } catch (...) {
        std::cout << "Caught exception when accessing back of empty list." << std::endl;
    }

    // 测试拷贝构造
    intList.push_back(1);
    intList.push_back(2);
    List<int> copiedIntList(intList);
    std::cout << "Copied list size (should be 2): " << copiedIntList.size() << std::endl;

    // 测试移动构造
    List<int> movedIntList(std::move(copiedIntList));
    std::cout << "Moved list size (should be 2): " << movedIntList.size() << std::endl;
    std::cout << "Copied list size after move (should be 0): " << copiedIntList.size() << std::endl;

    // 测试赋值运算符
    List<int> assignedIntList;
    assignedIntList = movedIntList;
    std::cout << "Assigned list size (should be 2): " << assignedIntList.size() << std::endl;

    // 测试插入
    auto it = assignedIntList.begin();
    assignedIntList.insert(it, 3);
    std::cout << "After insert (size should be 3): " << assignedIntList.size() << std::endl;
    assignedIntList.print();  // 打印列表

    // 测试删除
    assignedIntList.erase(it);
    std::cout << "After erase (size should be 2): " << assignedIntList.size() << std::endl;
    assignedIntList.print();  // 打印列表
    if(assignedIntList.begin()==assignedIntList.end()){
        std::cout << "begin == end\n";
    }
    if(assignedIntList.begin()!=assignedIntList.end()){
        std::cout << "begin != end\n";
    }
    // 测试范围删除
    assignedIntList.push_back(4);
    assignedIntList.push_back(5);
    auto start = assignedIntList.begin();
    auto end = assignedIntList.end();
    assignedIntList.erase(start, end);
    std::cout << "After range erase (size should be 0): " << assignedIntList.size() << std::endl;
    
    // 再次清理并测试链表在所有边界情况下的表现
    intList.clear();
    std::cout << "Final size of intList (should be 0): " << intList.size() << std::endl;

    printf("-------ceshi List<float>\n");
    // 测试 float 类型列表
    List<float> floatList = {1.1f, 2.2f, 3.3f};  // 使用初始化列表构造

    std::cout << "Float list size (should be 3): " << floatList.size() << std::endl;
    floatList.print();  // 打印列表

    // 测试 float 列表的其他功能
    floatList.push_back(4.4f);
    floatList.push_front(0.0f);
    std::cout << "After adding float elements (size should be 5): " << floatList.size() << std::endl;
    floatList.print();  // 打印列表

    // 测试 front 和 back
    std::cout << "Front of float list (should be 0.0): " << floatList.front() << std::endl;
    std::cout << "Back of float list (should be 4.4): " << floatList.back() << std::endl;

    // 测试 pop_front 和 pop_back
    floatList.pop_front();
    std::cout << "After pop_front (size should be 4): " << floatList.size() << std::endl;
    floatList.pop_back();
    std::cout << "After pop_back (size should be 3): " << floatList.size() << std::endl;

    // 测试 float 列表的插入和删除
    auto floatIt = floatList.begin();
    floatList.insert(floatIt, 5.5f);
    std::cout << "After insert float (size should be 4): " << floatList.size() << std::endl;
    floatList.print();  // 打印列表

    floatList.erase(floatIt);
    std::cout << "After erase float (size should be 3): " << floatList.size() << std::endl;
    floatList.print();  // 打印列表

    // 清理
    floatList.clear();
    std::cout << "Final size of floatList (should be 0): " << floatList.size() << std::endl;

    printf("----- Testing List<char> -----\n");
    
    // 创建字符链表并插入字母
    List<char> charList; 
    std::string letters = "wanghengning";
    for (char ch : letters) {
        charList.push_back(ch);
    }

    // 测试自赋值
    List<char> assignedCharList;
    assignedCharList = charList;  // 自赋值
    std::cout << "Assigned list size (should be 12): " << assignedCharList.size() << std::endl;
    charList.print();
    
    // 测试范围删除
    auto charStart = charList.begin();
    auto charEnd = charList.end();
    charList.erase(charStart, charEnd);  // 清空列表
    std::cout << "After range erase (should be 0): " << charList.size() << std::endl;
    charList.print();

    // 测试是否为空
    std::cout << "Is charList empty (should be true): " << charList.empty() << std::endl;

    // 再次添加字母，直到只剩一个
    charList.push_back('w');
    charList.push_back('a');
    charList.push_back('n');
    charList.pop_back();  // 删除最后一个字母
    std::cout << "After popping back, size (should be 2): " << charList.size() << std::endl;
    charList.print();

    // 测试是否为空
    std::cout << "Is charList empty (should be false): " << charList.empty() << std::endl;

    // 测试 pop_back
    charList.pop_back();  // 删除最后一个字母
    std::cout << "After pop_back, size (should be 0): " << charList.size() << std::endl;
    charList.print();

    // 测试异常情况
    try {
        std::cout << "Trying to access front of empty list: " << charList.front() << std::endl;
    } catch (...) {
        std::cout << "Caught exception when accessing front of empty list." << std::endl;
    }

    try {
        std::cout << "Trying to access back of empty list: " << charList.back() << std::endl;
    } catch (...) {
        std::cout << "Caught exception when accessing back of empty list." << std::endl;
    }

    // 测试拷贝构造和移动构造
    List<char> copiedCharList(charList);  // 拷贝构造
    std::cout << "Copied list size (should be 0): " << copiedCharList.size() << std::endl;

    List<char> movedCharList(std::move(copiedCharList));  // 移动构造
    std::cout << "Moved list size (should be 0): " << movedCharList.size() << std::endl;
    std::cout << "Copied list size after move (should be 0): " << copiedCharList.size() << std::endl;

    // 再次添加字母用于移动构造的测试
    charList.push_back('h');
    charList.push_back('e');
    charList.push_back('l');
    charList.push_back('l');
    charList.push_back('o');
    charList.print();
    List<char> anotherMovedCharList(std::move(charList));  // 再次测试移动构造
    std::cout << "Another moved list size (should be 5): " << anotherMovedCharList.size() << std::endl;
    std::cout << "Original list size after move (should be 0): " << charList.size() << std::endl;
    anotherMovedCharList.print();

    printf("-----ceshi List<List>\n");
    List<List<int>> outerList;  // 外层链表，存放内层链表

    // 创建并初始化第一个内层链表
    List<int> innerList1;
    innerList1.push_back(1);
    innerList1.push_back(2);
    outerList.push_back(innerList1);  // 将内层链表加入外层链表

    // 创建并初始化第二个内层链表
    List<int> innerList2;
    innerList2.push_back(4);
    innerList2.push_back(5);
    outerList.push_back(innerList2);

    // 嵌套地访问里面的内容
    (*outerList.begin()).push_back(3);
    
    // 打印外层链表的大小和内容
    std::cout << "Outer list size (should be 2): " << outerList.size() << std::endl;
    for (const auto& inner : outerList) {
        inner.print();  // 打印每个内层链表
    }

    // 测试插入到外层链表
    List<int> innerList3;
    innerList3.push_back(6);
    outerList.insert(outerList.begin(), innerList3);
    std::cout << "After inserting a new inner list, outer list size (should be 3): " << outerList.size() << std::endl;

    // 打印更新后的外层链表
    for (const auto& inner : outerList) {
        inner.print();  // 打印每个内层链表
    }

    // 测试在内层链表中增添元素
    outerList.front().push_back(7);  // 在第一个内层链表中添加元素
    std::cout << "After adding to the first inner list: " << std::endl;

    // 打印更新后的外层链表
    for (const auto& inner : outerList) {
        inner.print();  // 打印每个内层链表
    }

    // 拷贝内层链表到另一个内层链表
    outerList.back() = outerList.front();
    printf("run outerList.back() = outerList.front();\n");
    for (const auto& inner : outerList) {
        inner.print();  // 打印每个内层链表
    }

    // 测试删除外层链表的元素
    outerList.pop_back();
    std::cout << "After popping back, outer list size (should be 2): " << outerList.size() << std::endl;

    // 打印最终的外层链表
    for (const auto& inner : outerList) {
        inner.print();  // 打印每个内层链表
    }

    // 清理
    outerList.clear();
    std::cout << "Final size of outerList (should be 0): " << outerList.size() << std::endl;
}

int main() {
    printf("start testing\n");
    testList();
    printf("suceessfuly test\n");
    return 0;
}
