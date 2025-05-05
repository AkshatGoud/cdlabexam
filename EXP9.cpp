#include <iostream>
#include <stack>
#include <algorithm>
#include <cctype>

using namespace std;

// Function to check precedence of operators
int precedence(char op) {
    if(op == '+'|| op == '-') return 1;
    if(op == '*'|| op == '/') return 2;
    return 0;
}

// Function to check if character is operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Convert infix to postfix
string infixToPostfix(const string& infix) {
    stack<char> st;
    string postfix;

    for(char c : infix) {
        if(isalnum(c)) {
            postfix += c;
        } else if(c == '(') {
            st.push(c);
        } else if(c == ')') {
            while(!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // pop '('
        } else {
            while(!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// Convert infix to prefix
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());

    for(char& c : infix) {
        if(c == '(') c = ')';
        else if(c == ')') c = '(';
    }

    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int main() {
    string infix;

    cout << "Enter an infix expression (e.g., a+b*(c-d)): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Intermediate Code (Postfix): " << postfix << endl;
    cout << "Intermediate Code (Prefix): " << prefix << endl;

    return 0;
}
