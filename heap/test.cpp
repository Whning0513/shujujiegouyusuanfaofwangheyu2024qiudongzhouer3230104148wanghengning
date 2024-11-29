/*whn 3230104148*/
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "HeapSort.h"
#define SeqChangdu 1000000
#include <iomanip>  // 用于设置输出宽度

using namespace std;
using namespace chrono;

// 这个代码不是AI写的

/**
 * @brief 检查排序结果是否正确（是否按升序排列）
 * @tparam T 元素类型
 * @param vec 待检查的向量
 * @return 如果排序正确返回 true，否则返回 false
 */
template <typename T>
bool check(const std::vector<T>& vec) {
    size_t n = vec.size();
    for (size_t i = 1; i < n; ++i) {  // 只检查顺序
        if (vec[i - 1] > vec[i]) {
            return false;  // 如果前一个元素大于后一个元素，则排序不正确
        }
    }
    return true;
}

/**
 * @brief 打印堆的内容
 * @param vec 待打印的堆
 * @tparam T 元素类型
 */
template <typename T>
void printHeap(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

/**
 * @brief 生成测试序列
 * @param n 序列长度
 * @param type 序列类型：random/ordered/reverse/repetitive
 * @return 生成的向量
 */
vector<int> generateSequence(size_t n, const string& type) {
    vector<int> seq(n);
    if (type == "random") {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, SeqChangdu);
        for (size_t i = 0; i < n; ++i) {
            seq[i] = dis(gen);
        }
    } else if (type == "ordered") {
        for (size_t i = 0; i < n; ++i) {
            seq[i] = i;
        }
    } else if (type == "reverse") {
        for (size_t i = 0; i < n; ++i) {
            seq[i] = n - i;
        }
    } else if (type == "repetitive") {
        for (size_t i = 0; i < n; ++i) {
            seq[i] = i % 4097; // 重复元素
        }
    }
    return seq;
}

/**
 * @brief 测试排序性能
 * @param type 测试序列类型
 * @param successCount 成功次数的引用
 * @param results 用于保存每个测试的结果
 */
void testSort(const string& type, int& successCount, vector<string>& results) {
    const size_t n = SeqChangdu;  // 序列长度为 1000000
    vector<int> seq = generateSequence(n, type);
    vector<int> seq_copy = seq; // 用于 std::sort_heap

    // 打印堆（仅当n <= 10时）
    if (n <= 100 && type == "random") {
        cout << "After std::sort_heap: ";
        printHeap(seq);
    }

    // ******  测试自定义堆排序  ******
    auto start1 = high_resolution_clock::now();
    heapSort(seq);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1);

    bool customSuccess = check(seq);  // 检查自定义堆排序是否成功
    //printf(customSuccess ? "1" : "0");

    // 打印堆（仅当n <= 10时）
    if (n <= 100 && type == "random") {
        cout << "After std::sort_heap: ";
        printHeap(seq);
    }

    // 打印堆（仅当n <= 10时）
    if (n <= 100 && type == "random") {
        cout << "After std::sort_heap: ";
        printHeap(seq_copy);
    }

    // ******  测试 std::sort_heap  ******
    std::make_heap(seq_copy.begin(), seq_copy.end()); // 使用最大堆
    auto start2 = high_resolution_clock::now();
    std::sort_heap(seq_copy.begin(), seq_copy.end()); // 对最大堆排序
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2);

    bool stdSuccess = check(seq_copy);  // 检查 std::sort_heap 是否成功
    //printf(stdSuccess ? "1" : "0");

    // 打印堆（仅当n <= 10时）
    if (n <= 100 && type == "random") {
        cout << "After std::sort_heap: ";
        printHeap(seq_copy);
    }

    // 如果排序成功，则计数增加
    if (customSuccess) successCount++;
    if (stdSuccess) successCount++;

    // 将结果添加到results中
    results.push_back(type + "\t\t"
                      + to_string(duration1.count()) + " ms\t"
                      + to_string(duration2.count()) + " ms");
}

/**
 * @brief 打印表格
 * @param results 排序结果
 */
void printTable(const vector<string>& results) {
    //cout << "" << endl;
    cout << "+---------------------------+--------------------+--------------------+" << endl;
    cout << "| Sequence Type             | My HeapSort        | std::sort_heap     |" << endl;
    cout << "+---------------------------+--------------------+--------------------+" << endl;
    
    for (const auto& result : results) {
        // 格式化每列
        cout << "| " 
             << left << setw(25) << setfill(' ') << result.substr(0, result.find("\t")) << " |" 
             << left << setw(17) << setfill(' ') << result.substr(result.find("\t") + 1, result.find_last_of("\t") - result.find("\t") - 1) << " |   " 
             << left << setw(17) << setfill(' ') << result.substr(result.find_last_of("\t") + 1) 
             << "|" << endl;
        cout << "+---------------------------+--------------------+--------------------+" << endl;
    }
}

int main() {
    int successCount = 0;  // 用于统计成功的次数
    vector<string> results;  // 用于保存每个测试的结果
    printf("start test please wait\n");
    // 执行测试
    testSort("random", successCount, results);
    testSort("ordered", successCount, results);
    testSort("reverse", successCount, results);
    testSort("repetitive", successCount, results);

    // 打印结果表格
    printTable(results);

    // 输出成功次数
    cout << "Total success for 'check()' count: " << successCount << endl;

    return 0;
}
