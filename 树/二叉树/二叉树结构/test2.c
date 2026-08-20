// 二叉树遍历——非递归前序遍历
#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;

typedef struct TreeNode
{
    ElemType data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(ElemType data)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preOrderNonRecursive(TreeNode *root)
{
    if (root == NULL)
        return;
    TreeNode *stack[100];
    int top = -1;
    stack[++top] = root;
    while (top >= 0)
    {
        TreeNode *node = stack[top--];
        printf("%c ", node->data);
        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
}


// 二叉树遍历——非递归中序遍历
void inOrderNonRecursive(TreeNode *root)
{
    TreeNode *stack[100];
    int top = -1;
    TreeNode *current = root;
    while (current != NULL || top >= 0)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%c ", current->data);
        current = current->right;
    }
}


// 二叉树遍历——非递归后序遍历
void postOrderNonRecursive(TreeNode *root)
{
    TreeNode *stack[100];
    int top = -1;
    TreeNode *current = root;
    TreeNode *lastVisited = NULL;
    while (current != NULL || top >= 0)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        TreeNode *peekNode = stack[top];
        if (peekNode->right != NULL && lastVisited != peekNode->right)
        {
            current = peekNode->right;
        }
        else
        {
            printf("%c ", peekNode->data);
            lastVisited = peekNode;
            top--;
        }
    }
}

TreeNode *buildSampleTree()
{
    TreeNode *A = createNode('A');
    TreeNode *B = createNode('B');
    TreeNode *C = createNode('C');
    TreeNode *D = createNode('D');
    TreeNode *E = createNode('E');
    TreeNode *F = createNode('F');

    A->left = B;
    A->right = C;
    B->left = D;
    B->right = E;
    C->right = F;
    return A;
}

void freeTree(TreeNode *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    TreeNode *root = buildSampleTree();
    printf("非递归前序遍历: ");
    preOrderNonRecursive(root);
    printf("\n");

    printf("非递归中序遍历: ");
    inOrderNonRecursive(root);
    printf("\n");

    printf("非递归后序遍历: ");
    postOrderNonRecursive(root);
    printf("\n");

    freeTree(root);
    return 0;
}
