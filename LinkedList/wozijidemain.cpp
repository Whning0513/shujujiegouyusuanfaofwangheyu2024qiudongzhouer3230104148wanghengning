#include "LinkedList.h"
#include <iostream>

int main() {
    // 测试【取值】操作
    SingleLinkedList<int> list1{1, 2, 3, 4, 5};
    std::cout << "List1 initial state: ";
    list1.printList();
    std::cout << std::endl;

    int currentValue = list1.getCurrentVal();
    std::cout << "Current value: " << currentValue << std::endl;
    std::cout << std::endl;

    // 测试【定义值】操作
    list1.setCurrentVal(10); // 将第一个节点的值改为 10
    std::cout << "After setting current value to 10: ";
    list1.printList();
    std::cout << std::endl;

    // 测试【空链表判断】
    SingleLinkedList<int> emptyList;
    std::cout << "Is list1 empty? " << (list1.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Is emptyList empty? " << (emptyList.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // 测试【插入】操作
    list1.insert(20); // 在第一个节点后插入 20
    std::cout << "After inserting 20 after current position: ";
    list1.printList();
    std::cout << std::endl;

    emptyList.insert(5); // 向空链表中插入 5
    std::cout << "After inserting 5 into emptyList: ";
    emptyList.printList();
    std::cout << std::endl;

    // 测试【查找】操作
    bool found = list1.find(4); // 查找值为 4 的节点
    std::cout << "Found 4 in list1? " << (found ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    found = list1.find(100); // 查找不存在的值
    std::cout << "Found 100 in list1? " << (found ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // 测试【删除】操作
    list1.remove(); // 删除当前位置的下一个节点
    std::cout << "After removing node after current position: ";
    list1.printList();
    std::cout << std::endl;

    // 测试删除空链表中的元素
    emptyList.remove();
    std::cout << "After removing from emptyList: ";
    emptyList.printList();
    std::cout << std::endl;

    return 0;
}
