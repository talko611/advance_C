#include "q2Funcs.h"

BOOL buildExpressionTree(const char *str, Tree *tr) {
    BOOL res = FALSE;

    if (isStrValid(str)) { //Validate str before building it
        tr->root = buildExpressionTreeHelper(str);
        res = TRUE;
    } else {
        tr->root = NULL;
    }
    return res;
}

TreeNode *buildExpressionTreeHelper(const char *str) {
    TreeNode *root;
    char *leftStr, *rightStr;
    int rootDataIndex = findRootNodeData(str);

    if (rootDataIndex == -1) {
        return NULL;
    }
    root = createNewTreeNode(str[rootDataIndex], NULL, NULL);
    leftStr = copyStr(str + 1, rootDataIndex - 1);//adding -1 and +1 is to remove '(' from smaller str
    root->left = buildExpressionTreeHelper(leftStr);
    rightStr = copyStr(str + rootDataIndex + 1,
                       strlen(str) - rootDataIndex + 2); // +2 to remove outer parentheses from length
    root->right = buildExpressionTreeHelper(rightStr);
    free(leftStr);
    free(rightStr);

    return root;
}

char *createNewStr(int size) {
    char *res;
    res = (char *) malloc(sizeof(char) * size + 1);
    checkMemoryAllocation(res);

    return res;
}

char *copyStr(const char *src, int length) {
    char *res;
    int i;

    res = createNewStr(length);
    for (i = 0; i < length; i++) {
        res[i] = src[i];
    }
    res[i] = '\0';

    return res;
}

BOOL isValidParentheses(const char *str, int *parenthesesCounter) {
    int leftParentheses = 0, rightParentheses = 0, size;
    size = strlen(str);

    for (int i = 0; i < size; i++) {
        if (str[i] == '(') {
            leftParentheses++;
        }
        if (str[i] == ')') {
            rightParentheses++;
        }
    }
    if (leftParentheses == rightParentheses && leftParentheses != 0) {
        *parenthesesCounter = leftParentheses + rightParentheses;
        return TRUE;
    }
    return FALSE;
}

TreeNode *createNewTreeNode(char data, TreeNode *left, TreeNode *right) {
    TreeNode *new;

    new = (TreeNode *) malloc(sizeof(TreeNode));
    checkMemoryAllocation(new);

    new->data = data;
    new->right = right;
    new->left = left;

    return new;
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Error- memory allocation failed\n");
        exit(1);
    }
}

int findRootNodeData(const char *str) {
    int res = -1, leftParenthesesCounter = 0, rightParenthesesCounter = 0, size = strlen(str);


    for (int i = 0; i < size; i++) {
        if (str[i] == '(') {
            leftParenthesesCounter++;
        }
        if (str[i] == ')') {
            rightParenthesesCounter++;
        }
        if (isValidOperator(str[i]) == 1 && (leftParenthesesCounter == rightParenthesesCounter + 1)) {
            res = i;
            break;
        }
    }
    if (res == -1) {// case didn't find operator in expression
        res = findFirstNum(str);
    }
    return res;
}

BOOL isStrValid(const char *str) {
    int testsCounter = 0, size = strlen(str);
    BOOL res = FALSE;

    if (isValidParentheses(str, &testsCounter) == 1) {
        for (int i = 0; i < size; i++) {
            if (isValidNum(str[i]) == 1) {
                testsCounter++;
            }
            if (isValidOperator(str[i]) == 1) {
                testsCounter++;
            }
        }
        if (testsCounter == size) {
            res = TRUE;
        }
    }
    return res;
}

BOOL isValidNum(char ch) {
    if (ch - '0' < 10 && ch - '0' >= 0) {
        return TRUE;
    }
    return FALSE;
}

BOOL isValidOperator(char ch) {
    BOOL res;
    switch (ch) {
        case '+':
            res = TRUE;
            break;
        case '-':
            res = TRUE;
            break;
        case '/':
            res = TRUE;
            break;
        case '*':
            res = TRUE;
            break;
        case '%':
            res = TRUE;
            break;
        default:
            res = FALSE;
    }
    return res;
}

int findFirstNum(const char *str) {
    int res = -1, size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (str[i] - '0' >= 0 && str[i] - '0' < 10) {
            res = i;
            break;
        }
    }
    return res;
}

void freeTree(Tree *tr) {
    if (tr->root == NULL) {
        return;
    }
    freeTreeHelper(tr->root);
}

void freeTreeHelper(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    freeTreeHelper(root->left);
    freeTreeHelper(root->right);
    free(root);
}

double calcExpression(Tree tr) {
    return calcExpressionHelper(tr.root);
}

double calcExpressionHelper(TreeNode *root) {
    double leftSum, rightSum;

    if (root == NULL) {
        return 0;
    }
    if (isValidNum(root->data) == 1) {
        return root->data - '0';
    } else {
        leftSum = calcExpressionHelper(root->left);
        rightSum = calcExpressionHelper(root->right);
        return calcWithOperator(leftSum, rightSum, root->data);
    }
}

double calcWithOperator(int num1, int num2, char operator) {
    double res = 0;

    switch (operator) {
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num1 - num2;
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
            res = num1 / num2;
            break;
        case '%':
            res = num1 % num2;
        default:
            break;
    }
    return res;
}