#include <iostream>
#include <string>
using namespace std;

// Define a structure for the nodes of the expression tree
struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string v) : value(v), left(nullptr), right(nullptr) {}
};

// Check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Check if the expression is wrapped by parentheses that encompass the entire expression, e.g. (a+b) is wrapped, but (a+b)*c is not
bool isWrappedByParentheses(const string& expr) {
    // An expression is wrapped by parentheses if it starts with '(' and ends with ')'
    if (expr.size() < 2 || expr.front() != '(' || expr.back() != ')')
        return false;

    // depth variable to track the level of nested parentheses
    int depth = 0;
    // We need to ensure that the parentheses at the start and end are a matching pair that encompasses the entire expression
    for (size_t i = 0; i < expr.size(); i++) {
        // Track parentheses depth
        if (expr[i] == '(') depth++;
        else if (expr[i] == ')') depth--;

        // If we return to depth 0 before reaching the end, it means the outer parentheses do not encompass the entire expression
        if (depth == 0 && i != expr.size() - 1)
            return false;
    }
    return true;
}

int findMainOperator(const string& expr) {
    // depth variable to track the level of nested parentheses
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
    // Remove outer parentheses if they wrap the entire expression
    while (isWrappedByParentheses(expr)) {
        // Remove the outer parentheses by taking the substring that excludes the first and last characters
        expr = expr.substr(1, expr.size() - 2);
    }

    // Find the main operator in the expression
    int opIndex = findMainOperator(expr);

    // If no operator is found, it's a leaf node (number)
    if (opIndex == -1) {
        return new Node(expr);
    }

    // Create a new node for the operator and recursively build left and right subtrees
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

// Helper function to print the tree (for debugging)
void printTree(Node* root, int depth = 0) {
    // Base case: if the node is null, return
    if (!root) return;

    // Print the right subtree first (so it appears on top when printed)
    printTree(root->right, depth + 1);

    // Print the current node with indentation based on depth
    for (int i = 0; i < depth; i++) cout << "    ";
    cout << root->value << endl;

    // Print the left subtree
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