// Copyright 2021 NNTU-CS
#include "alg.h"
#include "tstack.h"
#include <cctype>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> st;
    std::string out;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                out += inf[i];
                ++i;
            }
            out += ' ';
            --i;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.isEmpty() && st.top() != '(') {
                out += st.pop();
                out += ' ';
            }
            if (!st.isEmpty() && st.top() == '(')
                st.pop();
        } else if (isOperator(c)) {
            while (!st.isEmpty() && st.top() != '(' && precedence(st.top()) >= precedence(c)) {
                out += st.pop();
                out += ' ';
            }
            st.push(c);
        }
    }

    while (!st.isEmpty()) {
        out += st.pop();
        out += ' ';
    }

    if (!out.empty() && out.back() == ' ')
        out.pop_back();

    return out;
}

int eval(std::string post) {
    TStack<int, 100> st;

    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];
        if (std::isdigit(c)) {
            int num = 0;
            while (i < post.length() && std::isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            st.push(num);
            --i;
        } else if (isOperator(c)) {
            int b = st.pop();
            int a = st.pop();
            int res = 0;
            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            st.push(res);
        }
    }

    return st.pop();
}
