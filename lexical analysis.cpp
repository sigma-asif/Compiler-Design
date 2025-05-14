#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;
vector<string>op;
vector<string>id;
vector<string>key;
vector<string>num;



bool isIdentifierStart(char ch) {
    return isalpha(ch) || ch == '_'; // Allow underscore as identifier start
}

bool isIdentifierNowhere(char ch) {
    return isalnum(ch) || ch == '_'; // Allow underscore in identifiers
}

bool isKeyword(string str) {
    string keywords[] = {"int", "float", "double", "if", "else", "while", "for", "return", "void", "main", "char", "bool", "true", "false", "using", "namespace", "std"};
    return find(begin(keywords), end(keywords), str) != end(keywords);
}

bool isPunctuation(char ch) {
    string punc = ".,;:(){}[]";
    return punc.find(ch) != string::npos;
}

bool isOperator(const string &code, int start, int length) {
    const string operators[] = {"+", "-", "*", "/", "%", "=", "==", "+=", "-=", "*=", "/=", "%=", "<", "<<", "<=", ">", ">>", ">=", "!", "!=", "&", "&&", "|", "||", "^", "~", "<<=", ">>="};
    string potentialOperator = code.substr(start, length);
    return find(begin(operators), end(operators), potentialOperator) != end(operators);
}

void lexical_analysis(const string &code) {
    int length = code.length();
    for (int i = 0; i < length; i++) {
        // Skip single line comments
        if (i < length - 1 && code[i] == '/' && code[i + 1] == '/') {
            int x = i;
            int y = x;
            while (i < length && code[i] != '\n') {
                i++;
            }
            //number of line
            int cnt1=0;
            for(int j = 0; j<=i; j++){
                if(code[j] =='\n'){
                    cnt1++;
                }
            }
            cout<<"single line comment at line:"<<cnt1<<endl;


                        while (x < code.length() && code[x] != '\n') {
                            x++;
                        }
                        cout<<code.substr(y,x-y)<<endl;
                        cout<<endl;
                 cout<<"length of commment:"<<x-y<<endl;

        }

            // Skip multiline comments
        else if (i < length - 1 && code[i] == '/' && code[i + 1] == '*') {
            i += 2;
            int x = i;
            while (i < length - 1 && !(code[i] == '*' && code[i + 1] == '/')) {
                i++;
            }
            i += 1; // Skip the closing */
            //number of line
            int y = i;
            int cnt2=0;
            for(int j = 0; j<=i+1; j++){
                if(code[j] =='\n'){
                    cnt2++;
                }
            }
            cout<<"multi line comment at line:"<<cnt2<<endl;
            cout<<code.substr(x,(y-x+1))<<endl;
            cout<<"length of commment:"<<y-x+1<<endl;

        }
            // Identify string literal
        else if (code[i] == '"') {
            int start = ++i;
            while (i < length && code[i] != '"') {
                i++;
            }
            cout << "String literal found: " << code.substr(start, i - start) << endl;
        }
            // Identify identifiers & keywords
        else if (isIdentifierStart(code[i])) {
            int start = i;
            while (i < length && isIdentifierNowhere(code[i])) {
                i++;
            }
            string k = code.substr(start, i - start);
            if (!isKeyword(k)) {
               // cout << "Identifier found: " << k << endl;
                id.push_back(k);
            } else {
               // cout << "Keyword found: " << k << endl;
                key.push_back(k);
            }
            i--; // Adjust i because it will be incremented in the loop
        }
            // Identify numbers
        else if (isdigit(code[i])) {
            int start = i;
            while (i < length && isdigit(code[i])) {
                i++;
            }
            //cout << "Number found: " << code.substr(start, i - start) << endl;
            num.push_back(code.substr(start, i - start));
            i--; // Adjust i because it will be incremented in the loop
        }
            // Identify operators
        else if (isOperator(code, i, 3)) {    //i = 2,3,4,, i =5
            //cout << "Operator found: " << code.substr(i, 3) << endl;
            op.push_back(code.substr(i, 3));
            i += 2; // Move index forward by 2 to skip next characters (since the length is 3)
        }
        else if (isOperator(code, i, 2)) {
            //cout << "Operator found: " <<  code.substr(i, 2)<< endl;
            i += 1; // Move index forward by 1 to skip next character (since the length is 2)
           op.push_back(code.substr(i, 2));
        }
        else if (isOperator(code, i, 1)) {
            //cout << "Operator found: " << code[i] << endl;
            // No need to increment i here since length is 1
            op.push_back(code.substr(i, 1));
        }
            // Identify punctuation
        else if (isPunctuation(code[i])) {
            cout << "Punctuation found: " << code[i] << endl;
        }
    }
}



int main() {
    //ifstream file("Y:\\1.compiler design\\example.cpp");
    ifstream file("D:\\addition.cpp");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return 1; // Exit if file cannot be opened
    }

    // Read the file contents into a string
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Close the file
    file.close();

    // Perform lexical analysis
    lexical_analysis(code);
    // Print results
    cout << "\n--- Identifiers ---" << endl;
    for (const string &identifier : id) {
        cout << identifier << endl;
    }

    cout << "\n--- Keywords ---" << endl;
    for (const string &keyword : key) {
        cout << keyword << endl;
    }

    cout << "\n--- Operators ---" << endl;
    for (const string &operatorToken : op) {
        cout << operatorToken << endl;
    }

    cout << "\n--- Numbers ---" << endl;
    for (const string &number : num) {
        cout << number << endl;
    }

    return 0;
}
