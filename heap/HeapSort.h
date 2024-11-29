/*whn 3230104148*/
#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <algorithm>  // std::swap 用于交换
#include <iostream>
//#include <chrono>

// 这个代码不是AI写的

template <typename T>
inline void fastSwap(T& a, T& b) { // 应该比内置函数swap更快
    a ^= b;
    b ^= a;
    a ^= b;
}

/**
 * @brief 维护堆的性质：从指定的索引开始，将子树调整为堆。
 * @tparam T 元素类型
 * @param vec 待调整的向量
 * @param n 向量大小
 * @param i 当前索引
 */
template <typename T>
void heapify(std::vector<T>& vec, size_t n, size_t i) {
    size_t largest = i;        // 假设当前节点是最大值
    size_t left = (i << 1) + 1; // 左子节点，i * 2 + 1，替换为左移操作
    size_t right = (i << 1) + 2; // 右子节点，i * 2 + 2，替换为左移操作

    // 如果左子节点比当前节点大
    if (left < n && vec[left] > vec[largest]) {
        largest = left;
    }

    // 如果右子节点比当前节点大
    if (right < n && vec[right] > vec[largest]) {
        largest = right;
    }

    // 如果最大节点不是当前节点，交换并继续调整堆
    if (largest != i) {
        fastSwap(vec[i], vec[largest]);
        heapify(vec, n, largest); // 递归调整下去
    }
}

/**
 * @brief 手动实现的堆排序函数
 * @tparam T 元素类型
 * @param vec 待排序的向量
 */
template <typename T>
void heapSort(std::vector<T>& vec) {
    size_t n = vec.size();

    // 构建最大堆：从最后一个非叶子节点开始调整堆
    for (size_t i = (n >> 1) - 1; i != SIZE_MAX; --i) {  // i = n/2 - 1，替换为右移操作
        heapify(vec, n, i);
    }

    // 排序过程：逐步将堆顶元素交换到数组末尾
    for (size_t i = n - 1; i > 0; --i) {
        fastSwap(vec[0], vec[i]);   // 将堆顶元素交换到当前范围末尾
        heapify(vec, i, 0);          // 重新调整堆
    }
}

#endif // HEAPSORT_H

// 声明：这个代码不是AI写的。