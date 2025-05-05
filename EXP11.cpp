#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    string s, lhs, op1, op2;
    char op;
    getline(cin, s);
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    int eq = s.find('='), opPos = s.find_first_of("+-*/", eq);
    lhs = s.substr(0, eq);
    op1 = s.substr(eq + 1, opPos - eq - 1);
    op = s[opPos];
    op2 = s.substr(opPos + 1);
    cout << "LOAD R1, " << op1 << "\n";
    cout << (op == '+' ? "ADD" : op == '-' ? "SUB" : op == '*' ? "MUL" : "DIV") << " R1, " << op2 << "\n";
    cout << "STORE " << lhs << ", R1\n";
}