/*whn 3230104148 2024DS 11.21*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath> // 包含数学操作，例如四舍五入
#include "expression_evaluator.h" // 表达式求值器的头文件

// 帮助函数：将浮点数四舍五入到指定的小数位数
double roundToPrecision(double value, int precision) {
    double factor = std::pow(10.0, precision); // 10 的 `precision` 次方，用于放大数字
    return std::round(value * factor) / factor; // 四舍五入并还原到原始范围
}

// 从文件加载测试用例
std::vector<std::pair<std::string, std::string>> loadTestCasesFromFile(const std::string& filename) {
    std::vector<std::pair<std::string, std::string>> testExpressions; // 用于存储测试用例
    std::ifstream file(filename); // 打开指定文件
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n"; // 文件打开失败时输出错误
        return testExpressions;
    }

    std::string line;
    while (std::getline(file, line)) { // 逐行读取文件内容
        std::istringstream ss(line); // 使用字符串流处理当前行
        std::string expression, expected;

        // 解析行内容，表达式与期望结果通过 | 分隔
        if (std::getline(ss, expression, '|') && std::getline(ss, expected)) {
            testExpressions.emplace_back(expression, expected); // 添加有效测试用例
        } else {
            std::cerr << "Invalid line format: " << line << "\n"; // 格式无效时输出警告
        }
    }

    file.close(); // 关闭文件
    return testExpressions;
}

// 显示帮助信息
void showHelp() {
std::cout << "\n== HELP MENU ==\n";
std::cout << "- Enter a valid mathematical expression to calculate.\n";
std::cout << "Example: 4+11*(1e-1+10-(-1*111--11/222)+(111-11)) \n";
std::cout << "- Enter 'ptc' to run all test cases from the 'test_cases.txt' file.\n";
std::cout << "- Enter 'help' to display this help menu.\n";
std::cout << "- Enter 'exit' to exit the program.\n";
std::cout << "For more detailed instructions, please refer to the readme.md file.\n\n";
}

// 运行测试用例并验证结果
void runTests(const std::vector<std::pair<std::string, std::string>>& testExpressions) {
    ExpressionEvaluator evaluator; // 初始化表达式求值器
    int faults_num = 0; // 错误计数器
    int case_num = 1; // 用例编号

    std::cout << "\nRunning test cases...\n";
    for (const auto& [expression, expected] : testExpressions) {
        double result;
        std::cout << "Case " << case_num++ << ": " 
                  << (expression.empty() ? "(empty expression)" : expression) << "\n";

        // 尝试评估表达式
        if (evaluator.evaluate(expression, result)) {
            std::cout << "Result:    " << result << "\n";
            std::cout << "Expected:  " << expected << "\n";

            // 如果期望结果是小数，检查精度
            if (!expected.empty() && expected.find('.') != std::string::npos) {
                size_t decimalPos = expected.find('.'); // 找到小数点位置
                int precision = expected.size() - decimalPos - 1; // 小数位数
                double roundedResult = roundToPrecision(result, precision); // 四舍五入结果
                double expectedValue = std::stod(expected); // 转换期望结果

                if (std::fabs(roundedResult - expectedValue) < 1e-9) {
                    std::cout << "Test Passed!\n"; // 结果匹配
                } else {
                    faults_num++;
                    std::cout << "Test Failed! ***************************************************\n";
                }
            } else {
                // 对于整数或非小数格式，直接字符串比较
                if (std::to_string(result).substr(0, expected.size()) == expected) {
                    std::cout << "Test Passed!\n";
                } else {
                    faults_num++;
                    std::cout << "Test Failed! ***************************************************\n";
                }
            }
        } else {
            std::cout << "Invalid: Invalid expression!\n";
            std::cout << "Expected: " << expected << "\n";
            if (expected == "ILLEGAL") {
                std::cout << "Test Passed!\n"; // 非法表达式的正确结果
            } else {
                faults_num++;
                std::cout << "Test Failed! Unexpected error. ************************\n";
            }
        }

        std::cout << "-------------------------------\n";
    }
    std::cout << "Test cases completed.\n" << faults_num << " faults found.\n"; // 总结测试结果
}

// 交互模式：用户输入表达式进行求值
void interactiveMode() {
    ExpressionEvaluator evaluator; // 初始化表达式求值器
    std::string input;

    std::cout << "\n== EVALUATOR ==\n\n";
    std::cout << "this is a evaluator\n";
    std::cout << "Enter a mathematical expression to calculate, and enter 'exit' to exit or 'help' to view help.\n";

    while (true) {
        std::cout << ">> "; // 提示符
        std::getline(std::cin, input); // 获取用户输入

        if (input == "exit") { // 退出命令
            std::cout << ">_< bye!\n";
            break;
        }

        if (input == "help") { // 显示帮助菜单
            showHelp();
            continue;
        }

        if (input == "ptc") { // 运行测试用例
            std::vector<std::pair<std::string, std::string>> testExpressions = loadTestCasesFromFile("test_cases.txt");
            if (!testExpressions.empty()) {
                runTests(testExpressions);
            } else {
                std::cout << "No valid test cases found in 'test_cases.txt'.\n";
            }
            continue;
        }

        // 评估用户输入的表达式
        double result;
        if (evaluator.evaluate(input, result)) {
            std::cout << "Result: " << result << "\n"; // 输出计算结果
        } else {
            std::cout << "ILLEGAL\n"; // 非法表达式
        }
    }
}

// 程序入口
int main() {
    interactiveMode(); // 进入交互模式
    return 0; // 正常退出程序
}
