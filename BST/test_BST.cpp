/*3230104148whn*/
#include <iostream>
#include <chrono>
#include <ctime>
#include "BST.h"  // 假设 BinarySearchTree 类定义在这个头文件中
#include <random>

void generateRandomTree(BinarySearchTree<int> &bst, int numElements) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, numElements * 2); // 确保数据唯一

    for (int i = 0; i < numElements; ++i) {
        bst.insert(dis(gen));
    }
}

void testBinarySearchTree() {//学在浙大给的我没动过
    BinarySearchTree<int> bst;

    // 测试插入功能
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    // 测试打印树结构
    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    // 测试查找最小和最大元素
    std::cout << "Minimum element: " << bst.findMin() << std::endl;
    std::cout << "Maximum element: " << bst.findMax() << std::endl;

    // 测试 contains 功能
    std::cout << "Contains 7? " << (bst.contains(7) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 20? " << (bst.contains(20) ? "Yes" : "No") << std::endl;

    // 测试删除功能
    bst.remove(7);
    std::cout << "Tree after removing 7:" << std::endl;
    bst.printTree();

    bst.remove(10);
    std::cout << "Tree after removing 10:" << std::endl;
    bst.printTree();

    // 测试清空树
    bst.makeEmpty();
    std::cout << "Tree after making empty:" << std::endl;
    bst.printTree();

    // 测试是否为空
    std::cout << "Is tree empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl;

    // 测试拷贝构造函数和赋值运算符
    BinarySearchTree<int> bst2;
    bst2.insert(1);
    bst2.insert(3);
    bst2.insert(2);

    BinarySearchTree<int> bst3(bst2);
    std::cout << "Copied Tree (bst3):" << std::endl;
    bst3.printTree();

    BinarySearchTree<int> bst4;
    bst4 = bst2;
    std::cout << "Assigned Tree (bst4):" << std::endl;
    bst4.printTree();

    // 测试移动构造函数和移动赋值运算符
    BinarySearchTree<int> bst5(std::move(bst2));
    std::cout << "Moved Tree (bst5):" << std::endl;
    bst5.printTree();

    BinarySearchTree<int> bst6;
    bst6 = std::move(bst5);
    std::cout << "Move Assigned Tree (bst6):" << std::endl;
    bst6.printTree();

    BinarySearchTree<int> bst7;
    //bst7.findMax();  // 测试异常处理
}

void testRemovePerformance() {
    BinarySearchTree<int> bstOld;
    BinarySearchTree<int> bstNew;

    int N=10000000;

    // 使用平衡插入生成两棵较为平衡的树
    generateRandomTree(bstOld,N);
    generateRandomTree(bstNew,N);

    printf("Insertion done\n");

    // ===================== old_remove 耗时测试和性能测试 =====================
    // 耗时测试
    auto startOldTime = std::chrono::high_resolution_clock::now();
    // 性能测试
    std::clock_t startOldClock = std::clock();

    for (int i = 0; i < N-1; ++i) {
        bstOld.old_remove(i);
    }

    auto endOldTime = std::chrono::high_resolution_clock::now();
    std::clock_t endOldClock = std::clock();

    // 计算耗时和CPU时间
    std::chrono::duration<double> durationOldTime = endOldTime - startOldTime;
    double durationOldClock = double(endOldClock - startOldClock) / CLOCKS_PER_SEC;

    std::cout << "old_remove time: " << durationOldTime.count() << " sec" << std::endl;
    std::cout << "old_remove CPU time: " << durationOldClock << " sec" << std::endl;

    // ===================== 优化后的 remove 耗时测试和性能测试 =====================
    // 耗时测试
    auto startNewTime = std::chrono::high_resolution_clock::now();
    // 性能测试
    std::clock_t startNewClock = std::clock();

    for (int i = 0; i < N-1; ++i) {
        bstNew.remove(i);
    }

    auto endNewTime = std::chrono::high_resolution_clock::now();
    std::clock_t endNewClock = std::clock();

    // 计算耗时和CPU时间
    std::chrono::duration<double> durationNewTime = endNewTime - startNewTime;
    double durationNewClock = double(endNewClock - startNewClock) / CLOCKS_PER_SEC;

    std::cout << "new remove time: " << durationNewTime.count() << " sec" << std::endl;
    std::cout << "new remove CPU time: " << durationNewClock << " sec" << std::endl;
}

int main() {
    testBinarySearchTree();  // 之前的测试函数
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n\n");
     testRemovePerformance(); // 新增的性能和耗时测试函数
    return 0;
}
