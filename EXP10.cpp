#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

// Structure for Quadruple
struct Quadruple {
    string op, arg1, arg2, result;
};

// Structure for Triple
struct Triple {
    string op, arg1, arg2;
};

// Helper function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Infix to Postfix conversion
string infixToPostfix(string exp) {
    stack<char> st;
    string postfix;

    for (char c : exp) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top(); st.pop();
            }
            st.pop(); // pop '('
        } else {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top(); st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top(); st.pop();
    }

    return postfix;
}

// Generate intermediate representations from postfix
void generateIntermediateCode(string postfix) {
    vector<Quadruple> quads;
    vector<Triple> triples;
    vector<int> pointerTable;
    stack<string> s;
    int tempVar = 1;

    for (char c : postfix) {
        if (isalnum(c)) {
            string op(1, c);
            s.push(op);
        } else if (isOperator(c)) {
            string arg2 = s.top(); s.pop();
            string arg1 = s.top(); s.pop();

            string temp = "t" + to_string(tempVar++);

            // For Quadruple
            quads.push_back({ string(1, c), arg1, arg2, temp });

            // For Triple
            int index1 = -1, index2 = -1;
            try {
                index1 = stoi(arg1.substr(1));
                index2 = stoi(arg2.substr(1));
            } catch (...) {}
            triples.push_back({ string(1, c), arg1, arg2 });

            s.push(temp);
        }
    }

    // Printing Quadruples
    cout << "\nQuadruples:\n";
    cout << "Index\tOp\tArg1\tArg2\tResult\n";
    for (int i = 0; i < quads.size(); i++) {
        cout << i << "\t" << quads[i].op << "\t" << quads[i].arg1 << "\t" << quads[i].arg2 << "\t" << quads[i].result << "\n";
    }

    // Printing Triples
    cout << "\nTriples:\n";
    cout << "Index\tOp\tArg1\tArg2\n";
    for (int i = 0; i < triples.size(); i++) {
        cout << i << "\t" << triples[i].op << "\t" << triples[i].arg1 << "\t" << triples[i].arg2 << "\n";
    }

    // Indirect Triples
    cout << "\nIndirect Triples:\n";
    pointerTable.resize(triples.size());
    for (int i = 0; i < triples.size(); i++) pointerTable[i] = i;

    cout << "Pointer\tStatement\n";
    for (int i = 0; i < pointerTable.size(); i++) {
        int index = pointerTable[i];
        cout << i << "\t(" << triples[index].op << ", " << triples[index].arg1 << ", " << triples[index].arg2 << ")\n";
    }
}

int main() {
    string infix;
    cout << "Enter infix expression (e.g., a+b*c-d): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    generateIntermediateCode(postfix);

    return 0;
}