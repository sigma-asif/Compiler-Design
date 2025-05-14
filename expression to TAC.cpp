#include <bits/stdc++.h>
using namespace std;

string code = "a + b + c * d / e - f";
// string code = "( a + b ) * ( c / e )";

vector<string> ans;
vector<string> tok;
stack<string> st;

int cnt1 = 0, cnt2 = 0;

void tokenize() {
    string s;
    stringstream ss(code);
    while (ss >> s) {
        tok.push_back(s);
    }
}

int pre(string s) {
    if (s == "+" || s == "-") {
        return 1;
    } else if (s == "*" || s == "/") {
        return 2;
    } else {
        return -1;
    }
}

void postfix() {
    for (int i = 0; i < tok.size(); i++) {
        if (tok[i] == "+" || tok[i] == "-" || tok[i] == "*" || tok[i] == "/") {
            while (!st.empty() && pre(st.top()) >= pre(tok[i])) {
                ans.push_back(st.top());
                st.pop();
            }
            st.push(tok[i]);
        } else if (tok[i] == "(") {
            st.push(tok[i]);
        } else if (tok[i] == ")") {
            while (!st.empty() && st.top() != "(") {
                ans.push_back(st.top());
                st.pop();
            }
            st.pop(); // pop "("
        } else {
            ans.push_back(tok[i]);
        }
    }
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
}

// Generate unique temp variable t0, t1, ...
string t() {
    return "t" + to_string(cnt1++);
}

// Generate unique register R0, R1, ...
string R() {
    return "R" + to_string(cnt2++);
}

// Replace tokens from [start, end] with temp variable
void replace(int start, int end, string temp) {
    ans.erase(ans.begin() + start, ans.begin() + end + 1);
    ans.insert(ans.begin() + start, temp);
}

// Generate three-address code and assembly-like instructions
void g3ac() {
    int i = 0;
    while (i < ans.size()) {
        string p1, p2, op, tmp;
        if (ans[i] == "+" || ans[i] == "-" || ans[i] == "*" || ans[i] == "/") {
            p1 = ans[i - 2];
            p2 = ans[i - 1];
            op = ans[i];
            tmp = t();
            cout << tmp << " = " << p1 << " " << op << " " << p2 << endl;

            string r = R();
            cout << "MOV " << r << ", " << p1 << endl;
            if (op == "+") cout << "ADD " << r << ", " << p2 << endl;
            if (op == "-") cout << "SUB " << r << ", " << p2 << endl;
            if (op == "*") cout << "MUL " << r << ", " << p2 << endl;
            if (op == "/") cout << "DIV " << r << ", " << p2 << endl;

            replace(i - 2, i, tmp);
            i = 0; // Reset i to re-scan new list with temp variable
        } else {
            i++;
        }
    }
}

int main() {
    tokenize();
    postfix();

    cout << "Postfix Expression: ";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl << endl;

    cout << "Three Address Code and Assembly Instructions:\n";
    g3ac();
}


