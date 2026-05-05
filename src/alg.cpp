// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int getPriority(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.isEmpty() && stack.top() == '(')
                stack.pop();
        } else if (isOperator(c)) {
            while (!stack.isEmpty() && stack.top() != '(' && getPriority(stack.top()) >= getPriority(c)) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        result += stack.pop();
        result += ' ';
    }

    if (!result.empty() && result.back() == ' ')
        result.pop_back();

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];
        if (isdigit(c)) {
            int num = 0;
            while (i < post.length() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            stack.push(num);
            --i;
        } else if (isOperator(c)) {
            int b = stack.pop();
            int a = stack.pop();
            switch (c) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }

    return stack.pop();
}
