#include <bits/stdc++.h>
using namespace std;

map<string, int> IS = {{"STOP", 0}, {"ADD", 1}, {"SUB", 2}, {"MULT", 3},
                       {"MOVER", 4}, {"MOVEM", 5}, {"DIV", 6},
                       {"READ", 7}, {"PRINT", 8}};
map<string, int> DL = {{"DC", 1}, {"DS", 2}};
map<string, int> AD = {{"START", 1}, {"END", 2}, {"LTORG", 5}};
map<string, int> REG = {{"AREG", 1}, {"BREG", 2}, {"CREG", 3}, {"DREG", 4}};

struct Symbol {
    string name;
    int address;
};

struct Literal {
    string value;
    int address;
};

vector<Symbol> symtab;
vector<Literal> littab;
vector<int> pooltab = {0};
vector<string> intermediate;

int LC = 0;

int findSymbol(string name) {
    for (int i = 0; i < symtab.size(); ++i)
        if (symtab[i].name == name)
            return i;
    return -1;
}

int findLiteral(string value) {
    for (int i = 0; i < littab.size(); ++i)
        if (littab[i].value == value)
            return i;
    return -1;
}

// Improved parser for operand splitting!
void parseOperands(string ops, string &op1, string &op2) {
    size_t comma = ops.find(',');
    if (comma != string::npos) {
        op1 = ops.substr(0, comma);
        op2 = ops.substr(comma + 1);
    } else {
        op1 = ops;
        op2 = "";
    }
    // Trim whitespace
    op1.erase(0, op1.find_first_not_of(' '));
    op1.erase(op1.find_last_not_of(' ') + 1);
    op2.erase(0, op2.find_first_not_of(' '));
    op2.erase(op2.find_last_not_of(' ') + 1);
}

void pass1(vector<string> code) {
    for (auto line : code) {
        string label, opcode, rest;
        stringstream ss(line);
        ss >> label;

        if (IS.count(label) || DL.count(label) || AD.count(label)) {
            opcode = label;
            getline(ss, rest);
            label = "";
        } else {
            ss >> opcode;
            getline(ss, rest);
        }

        string op1, op2;
        parseOperands(rest, op1, op2);

        if (opcode == "START") {
            LC = stoi(op1);
            intermediate.push_back("(AD,01) (C," + op1 + ")");
            continue;
        }

        if (!label.empty() && findSymbol(label) == -1) {
            symtab.push_back({label, LC});
        }

        if (IS.count(opcode)) {
            string ic = "(IS," + to_string(IS[opcode]) + ")";
            if (!op1.empty() && REG.count(op1))
                ic += " (R," + to_string(REG[op1]) + ")";
            if (!op2.empty()) {
                if (op2[0] == '=') {
                    if (findLiteral(op2) == -1)
                        littab.push_back({op2, -1});
                    int lit_idx = findLiteral(op2);
                    ic += " (L," + to_string(lit_idx + 1) + ")";
                } else {
                    if (findSymbol(op2) == -1)
                        symtab.push_back({op2, -1});
                    int sym_idx = findSymbol(op2);
                    ic += " (S," + to_string(sym_idx + 1) + ")";
                }
            }
            intermediate.push_back(ic);
            LC++;
        } else if (DL.count(opcode)) {
            string ic = "(DL," + to_string(DL[opcode]) + ")";
            if (opcode == "DC") {
                ic += " (C," + op1 + ")";
                LC++;
            } else if (opcode == "DS") {
                ic += " (C," + op1 + ")";
                LC += stoi(op1);
            }
            intermediate.push_back(ic);
        } else if (opcode == "LTORG") {
            for (int i = pooltab.back(); i < littab.size(); i++) {
                littab[i].address = LC++;
            }
            pooltab.push_back(littab.size());
            intermediate.push_back("(AD,05)");
        } else if (opcode == "END") {
            for (int i = pooltab.back(); i < littab.size(); i++) {
                littab[i].address = LC++;
            }
            pooltab.push_back(littab.size());
            intermediate.push_back("(AD,02)");
        }
    }
}

void pass2() {
    cout << "--- MACHINE CODE ---" << endl;
    int currLC = 0; // Start from first executable address
    for (auto ic : intermediate) {
        if (ic.find("(IS") != string::npos) {
            stringstream ss(ic);
            string token;
            vector<string> parts;
            while (ss >> token) parts.push_back(token);

            int opcode = stoi(parts[0].substr(4, 1));
            int reg = 0, addr = 0;

            if (parts.size() > 1 && parts[1].find("(R,") != string::npos)
                reg = stoi(parts[1].substr(3, 1));

            if (parts.size() > 2) {
                if (parts[2].find("(S,") != string::npos) {
                    int idx = stoi(parts[2].substr(3, 1)) - 1;
                    addr = symtab[idx].address;
                } else if (parts[2].find("(L,") != string::npos) {
                    int idx = stoi(parts[2].substr(3, 1)) - 1;
                    addr = littab[idx].address;
                }
            }
            cout << currLC++ << " : " << opcode << " " << reg << " " << addr << endl;
        }
    }
}

int main() {
    vector<string> code = {
        "START 200",
        "MOVER AREG,='5'",
        "ADD BREG,ONE",
        "SUB AREG,='1'",
        "MOVEM AREG,TEMP",
        "ONE DC 1",
        "TEMP DS 1",
        "LTORG",
        "END"
    };

    pass1(code);

    cout << "---- INTERMEDIATE CODE ----" << endl;
    for (auto s : intermediate) cout << s << endl;

    cout << "---- SYMBOL TABLE ----" << endl;
    for (int i = 0; i < symtab.size(); i++)
        cout << i + 1 << "  " << symtab[i].name << "    " << symtab[i].address << endl;

    cout << "---- LITERAL TABLE ----" << endl;
    for (int i = 0; i < littab.size(); i++)
        cout << i + 1 << "  " << littab[i].value << "   " << littab[i].address << endl;

    cout << "---- POOL TABLE ----" << endl;
    for (auto p : pooltab) cout << p << " ";
    cout << endl;

    pass2();

    return 0;
}
