#include <iostream>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string v) : value(v), left(nullptr), right(nullptr) {}
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isWrappedByParentheses(const string& expr) {
    if (expr.size() < 2 || expr.front() != '(' || expr.back() != ')')
        return false;

    int depth = 0;
    for (size_t i = 0; i < expr.size(); i++) {
        if (expr[i] == '(') depth++;
        else if (expr[i] == ')') depth--;

        if (depth == 0 && i != expr.size() - 1)
            return false;
    }
    return true;
}

int findMainOperator(const string& expr) {
    int depth = 0;

    // Scan from right to left to find the main operator (lowest precedence)
    for (int i = expr.size() - 1; i >= 0; i--) {
        // Track parentheses depth to ignore operators inside them
        if (expr[i] == ')') depth++;
        // If we encounter an opening parenthesis, we decrease depth
        else if (expr[i] == '(') depth--;
        // If we're at depth 0 and find a '+' or '-', that's our main operator
        else if (depth == 0 && (expr[i] == '+' || expr[i] == '-'))
            // Return the index of the main operator
            return i;
    }

    // Reset
    depth = 0;

    // If we didn't find '+' or '-', look for '*' or '/' at depth 0
    for (int i = expr.size() - 1; i >= 0; i--) {
        // Track parentheses depth to ignore operators inside them
        if (expr[i] == ')') depth++;
        // If we encounter an opening parenthesis, we decrease depth
        else if (expr[i] == '(') depth--;
        // If we're at depth 0 and find a '*' or '/', that's our main operator
        else if (depth == 0 && (expr[i] == '*' || expr[i] == '/'))
            // Return the index of the main operator
            return i;
    }

    return -1;
}

Node* buildTree(string expr) {
    while (isWrappedByParentheses(expr)) {
        expr = expr.substr(1, expr.size() - 2);
    }

    int opIndex = findMainOperator(expr);

    if (opIndex == -1) {
        return new Node(expr);
    }

    Node* root = new Node(string(1, expr[opIndex]));
    root->left = buildTree(expr.substr(0, opIndex));
    root->right = buildTree(expr.substr(opIndex + 1));
    return root;
}

int evaluate(Node* root) {
    // if it's a leaf node, it should be a number
    if (!root->left && !root->right)
        return stoi(root->value);

    // evaluate left and right subtrees
    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    if (root->value == "+") return leftVal + rightVal;
    if (root->value == "-") return leftVal - rightVal;
    if (root->value == "*") return leftVal * rightVal;
    if (root->value == "/") return leftVal / rightVal;

    return 0;
}

void printTree(Node* root, int depth = 0) {
    if (!root) return;

    printTree(root->right, depth + 1);

    for (int i = 0; i < depth; i++) cout << "    ";
    cout << root->value << endl;

    printTree(root->left, depth + 1);
}

int main() {
    string expr;
    cout << "Enter an expression: ";
    cin >> expr;

    Node* root = buildTree(expr);

    cout << "\nExpression tree:\n";
    printTree(root);

    cout << "\nResult: " << evaluate(root) << endl;

    return 0;
}