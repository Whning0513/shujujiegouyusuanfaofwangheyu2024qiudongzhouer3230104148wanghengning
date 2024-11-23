#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "expression_evaluator.h"

// 帮助函数：四舍五入到指定的小数位
double roundToPrecision(double value, int precision) {
    double factor = std::pow(10.0, precision);
    return std::round(value * factor) / factor;
}

// 从文件加载测试用例
std::vector<std::pair<std::string, std::string>> loadTestCasesFromFile(const std::string& filename) {
    std::vector<std::pair<std::string, std::string>> testExpressions;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file: " << filename << "\n";
        return testExpressions;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string expression, expected;
        if (std::getline(ss, expression, '|') && std::getline(ss, expected)) {
            testExpressions.emplace_back(expression, expected);
        } else {
            std::cerr << "Warning: Skipping invalid line: " << line << "\n";
        }
    }
    return testExpressions;
}

// 显示帮助信息
void showHelp() {
    std::cout << "\n== HELP MENU ==\n"
              << "- Enter a valid mathematical expression to evaluate.\n"
              << "- Commands:\n"
              << "  'ptc': Run all test cases from 'test_cases.txt'.\n"
              << "  'help': Display this help menu.\n"
              << "  'exit': Exit the program.\n\n";
}

void runTests(const std::vector<std::pair<std::string, std::string>>& testExpressions) {
    ExpressionEvaluator evaluator; // 初始化表达式求值器
    int faults = 0;                // 错误计数
    int caseNum = 1;               // 测试用例编号

    std::cout << "\n== Running Test Cases ==\n";

    for (const auto& [expression, expected] : testExpressions) {
        std::string trimmedExpression = expression;
        std::string trimmedExpected = expected;

        // 去除前后空格
        trimmedExpression.erase(0, trimmedExpression.find_first_not_of(" \t\r\n"));
        trimmedExpression.erase(trimmedExpression.find_last_not_of(" \t\r\n") + 1);
        trimmedExpected.erase(0, trimmedExpected.find_first_not_of(" \t\r\n"));
        trimmedExpected.erase(trimmedExpected.find_last_not_of(" \t\r\n") + 1);

        double result; // 存储评估结果
        bool evaluationSuccess = evaluator.evaluate(trimmedExpression, result);
        bool isExpectedIllegal = (trimmedExpected == "ILLEGAL");

        std::cout << "Case " << caseNum++ << ": \"" << trimmedExpression << "\"\n";

        // 逻辑：计算失败，且预期为非法
        if (!evaluationSuccess && isExpectedIllegal) {
            std::cout << "Result: ILLEGAL (Passed)\n";
        } 
        // 逻辑：计算失败，且预期不是非法
        else if (!evaluationSuccess) {
            ++faults;
            std::cout << "Result: ILLEGAL (Failed, expected: " << trimmedExpected << ")\n";
        } 
        // 逻辑：计算成功，比较结果
        else {
            try {
                double expectedValue = std::stod(trimmedExpected);  // 将期望值转换为浮点数
                double roundedResult = roundToPrecision(result, 9); // 四舍五入统一精度

                if (std::fabs(roundedResult - expectedValue) < 1e-9) {
                    std::cout << "Result: " << result << " (Passed)\n";
                } else {
                    ++faults;
                    std::cout << "Result: " << result << " (Failed, expected: " << trimmedExpected << ")\n";
                }
            } catch (const std::exception& e) {
                // 如果期望值不是数字
                ++faults;
                std::cout << "Result: " << result << " (Failed, invalid expected format)\n";
            }
        }

        std::cout << "-------------------------------\n";
    }
    std::cout << "Test cases completed with " << faults << " faults.\n";
}


// 交互模式
void interactiveMode() {
    ExpressionEvaluator evaluator;
    std::string input;

    std::cout << "Welcome to the Expression Evaluator!\n"
              << "Enter 'help' for instructions or 'exit' to quit.\n";

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "Goodbye!\n";
            break;
        } else if (input == "help") {
            showHelp();
        } else if (input == "ptc") {
            auto testCases = loadTestCasesFromFile("test_cases.txt");
            if (!testCases.empty()) {
                runTests(testCases);
            } else {
                std::cout << "No valid test cases found.\n";
            }
        } else {
            double result;
            if (evaluator.evaluate(input, result)) {
                std::cout << "Result: " << result << "\n";
            } else {
                std::cout << "ILLEGAL.\n";
            }
        }
    }
}

int main() {
    interactiveMode();
    return 0;
}
