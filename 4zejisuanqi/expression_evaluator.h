/*whn 3230104148 2024DS 11.21*/
#ifndef EXPRESSIONEVALUATOR_HPP
#define EXPRESSIONEVALUATOR_HPP

#include <stack>
#include <string>
#include <cctype>

// 用于解析和计算数学表达式的类
class ExpressionEvaluator {
  private:
    std::stack<double> values;  // 存储操作数的栈
    std::stack<char> ops;       // 存储操作符和括号的栈

    // 判断字符是否是运算符
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    // 检查左右括号是否匹配
    bool isMatchingParenthesis(char left, char right) {
        return (left == '(' && right == ')') ||
               (left == '[' && right == ']') ||
               (left == '{' && right == '}');
    }

    // 获取操作符的优先级，值越大优先级越高
    int precedence(char op) {
        if (op == '+' || op == '-') return 2; // 加减运算优先级最低
        if (op == '*' || op == '/') return 4; // 乘除运算优先级较高
        return 0; // 其他字符无优先级
    }

    // 从值栈中取出两个操作数并执行指定的运算
    bool compute(char op) {
        if (values.size() < 2) return false; // 不足两个操作数则无法计算
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        if (op == '/' && b == 0) return false; // 防止除以零
        switch (op) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/': values.push(a / b); break;
            default: return false; // 不支持的运算符
        }
        return true;
    }

    // 判断字符是否是数字的一部分（包括小数点和科学计数法符号）
    bool isPartOfNumber(char c) {
        return isdigit(c) || c == '.' || c == 'e' || c == 'E';
    }

    // 检查数字字符串的格式是否合法
    bool isValidNumber(const std::string& number) {
        size_t decimalCount = 0;
        size_t exponentCount = 0;
        for (char c : number) {
            if (c == '.') decimalCount++;
            if (c == 'e' || c == 'E') exponentCount++;
        }
        // 合法数字最多包含一个小数点和一个科学计数法符号
        return decimalCount <= 1 && exponentCount <= 1;
    }

    // 从表达式中提取并解析数字，支持一元负号
    bool processNumber(const std::string& expression, size_t& index, bool& isNegative) {
        size_t start = index;
        bool hasDecimal = false, hasExponent = false;

        // 如果存在一元负号，先处理
        if (isNegative) {
            isNegative = false;
            values.push(-1); // 先压入 -1
            ops.push('*');   // 表示乘法
        }

        // 如果数字带符号（+ 或 -），跳过符号字符
        if (expression[start] == '-' || expression[start] == '+') index++;

        // 逐字符解析数字
        while (index < expression.length()) {
            char c = expression[index];
            if (isdigit(c)) {
                index++;
            } else if (c == '.' && !hasDecimal && !hasExponent) {
                hasDecimal = true; // 标记小数点
                index++;
            } else if ((c == 'e' || c == 'E') && !hasExponent) {
                hasExponent = true; // 标记科学计数法符号
                index++;
                // 跳过科学计数法中的指数符号（+ 或 -）
                if (index < expression.length() && (expression[index] == '+' || expression[index] == '-')) index++;
                // 指数后必须有数字
                if (index >= expression.length() || !isdigit(expression[index])) return false;
            } else {
                break; // 遇到非数字字符停止解析
            }
        }

        // 提取数字字符串并验证格式
        std::string number = expression.substr(start, index - start);
        if (!isValidNumber(number)) return false;

        // 将数字转换为浮点数并压入值栈
        try {
            values.push(std::stod(number));
        } catch (...) {
            return false; // 转换失败
        }

        index--; // 回退到最后一个有效字符
        return true;
    }

    // 处理左括号
    void processLeftParenthesis(char c, bool& isNegative) {
        if (isNegative) {
            values.push(-1);
            ops.push('*'); // 左括号前的一元负号等效为乘以 -1
            isNegative = false;
        }
        ops.push(c);
    }

    // 处理右括号并计算括号内的表达式
    bool processRightParenthesis(char c) {
        while (!ops.empty() && !isMatchingParenthesis(ops.top(), c)) {
            if (!compute(ops.top())) return false;
            ops.pop();
        }
        if (ops.empty() || !isMatchingParenthesis(ops.top(), c)) return false; // 匹配失败
        ops.pop(); // 弹出匹配的左括号
        return true;
    }

    // 处理运算符
    bool processOperator(char op, bool& expectOperator, bool& isNegative) {
        if (!expectOperator) {
            if (op == '-') {
                isNegative = !isNegative; // 将减号标记为一元负号
            } else {
                return false;
            }
        } else {
            // 弹出优先级高于或等于当前运算符的运算符并计算
            while (!ops.empty() && precedence(ops.top()) >= precedence(op)) {
                if (!compute(ops.top())) return false;
                ops.pop();
            }
            ops.push(op); // 当前运算符入栈
            expectOperator = false; // 下一个期望操作数
        }
        return true;
    }

    // 解析整个表达式
    bool parseExpression(const std::string& expression) {
        bool expectOperator = false, isNegative = false;

        for (size_t i = 0; i < expression.length(); ++i) {
            char c = expression[i];
            if (isspace(c)) continue; // 跳过空格
            if (isdigit(c) || c == '.') {
                if (!processNumber(expression, i, isNegative)) return false;
                expectOperator = true; // 处理完数字后需要操作符
            } else if (c == '(' || c == '[' || c == '{') {
                processLeftParenthesis(c, isNegative);
            } else if (c == ')' || c == ']' || c == '}') {
                if (!processRightParenthesis(c)) return false;
                expectOperator = true; // 右括号后期待操作符
            } else if (isOperator(c)) {
                if (!processOperator(c, expectOperator, isNegative)) return false;
            } else {
                return false; // 非法字符
            }
        }
        return true;
    }

    // 计算最终结果
    bool computeResult(double& result) {
        while (!ops.empty()) {
            if (!compute(ops.top())) return false;
            ops.pop();
        }
        if (values.size() != 1) return false; // 结果应唯一
        result = values.top();
        return true;
    }

  public:
    // 解析并计算表达式
    bool evaluate(const std::string& expression, double& result) {
        clear(); // 初始化清理栈
        if (!parseExpression(expression)) return false;
        return computeResult(result);
    }

    // 清空值栈和操作符栈
    void clear() {
        while (!values.empty()) values.pop();
        while (!ops.empty()) ops.pop();
    }
};

#endif
