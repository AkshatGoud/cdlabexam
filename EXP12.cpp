#include <iostream>
#include <vector>
#include <string>
using namespace std;

int nextInstr = 0;
vector<int> patchList;

void emit(const string& code) {
    cout << nextInstr++ << ": " << code << endl;
}

void backpatch(const vector<int>& list, int target) {
    for (int i : list)
        cout << "// Backpatch instruction " << i << " → " << target << endl;
}

int main() {
    string var1, var2, lhs, rhs1, rhs2;
    char condOp, arithOp;

    // Input: if (var1 condOp var2) lhs = rhs1 arithOp rhs2;
    cout << "Enter condition (e.g., a < b): ";
    cin >> var1 >> condOp >> var2;
    cout << "Enter assignment (e.g., x = y + z): ";
    cin >> lhs >> rhs1 >> arithOp >> rhs2;

    emit("IF " + var1 + " " + condOp + " " + var2 + " GOTO _"); patchList.push_back(nextInstr - 1);
    emit("GOTO _"); patchList.push_back(nextInstr - 1);

    int trueBlockStart = nextInstr;
    emit("LOAD R1, " + rhs1);
    emit(string((arithOp == '+') ? "ADD" : (arithOp == '-') ? "SUB" : (arithOp == '*') ? "MUL" : "DIV") + " R1, " + rhs2);
    emit("STORE " + lhs + ", R1");

    int afterBlock = nextInstr;
    backpatch(patchList, afterBlock);

    return 0;
}