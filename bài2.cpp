#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <stack>
#include <cctype>
#include <algorithm>
using namespace std;

bool isVariable(char c) {
    return isalpha(c) && islower(c);
}

bool evaluateExpression(const string& expression, const map<char, bool>& values) {
    stack<bool> operands;
    stack<char> operators;

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (c == ' ') {
            continue;  
        } else if (isVariable(c)) {
            operands.push(values.at(c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                bool val = operands.top();
                operands.pop();
                if (op == '!') {
                    operands.push(!val);
                }
            }
            operators.pop(); // Pop the '('
        } else if (c == '^' || c == '~' || c == '-') {
            operators.push(c);
        }
    }

    // Evaluate the remaining operators
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        bool right = operands.top();
        operands.pop();
        bool left = operands.top();
        operands.pop();

        if (op == '^') {
            operands.push(left && right);
        } else if (op == '~') {
            operands.push(left || right);
        } else if (op == '-') {
            operands.push(!left || right);
        }
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, expression);

    vector<char> variables;
    // Collect all unique variables
    for (int i = 0; i < expression.size(); ++i) {
    char c = expression[i];
    if (isVariable(c) && find(variables.begin(), variables.end(), c) == variables.end()) {
        variables.push_back(c);
    }
}

    int n = variables.size();
    int numCombinations = pow(2, n);  

    // Print the variable names
    for (int i = 0; i < variables.size(); ++i) {
        cout << variables[i] << " ";
    }
    cout << "Result" << endl;

    // Iterate over all possible combinations of truth values (true/false)
    for (int i = 0; i < numCombinations; ++i) {
        map<char, bool> values;
        
        // Generate the combination of truth values (0 or 1)
        for (int j = 0; j < n; ++j) {
            values[variables[j]] = ((i >> (n - j - 1)) & 1);  // This will generate 0 or 1
        }

        // Print the current combination of truth values
        for (int j = 0; j < n; ++j) {
            cout << (values[variables[j]] ? "T" : "F") << " ";
        }

        // Evaluate the expression for this combination of truth values
        bool result = evaluateExpression(expression, values);

        // Print the result of the evaluation
        cout << (result ? "T" : "F") << endl;
    }

    return 0; 
}

