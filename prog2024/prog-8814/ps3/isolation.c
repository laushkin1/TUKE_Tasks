#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);

    return root;
}

bool compareTrees(Node* root1, Node* root2) {
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    return compareTrees(root1->left, root2->left) && compareTrees(root1->right, root2->right);
}

void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    size_t n, k;
    scanf("%zu %zu", &n, &k);

    int uniqueTreesCount = 0;
    Node** roots = malloc(n * sizeof(Node*));

    if (roots == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (size_t i = 0; i < n; ++i) {
        Node* currentRoot = NULL;
        for (size_t j = 0; j < k; ++j) {
            int value;
            scanf("%d", &value);
            currentRoot = insert(currentRoot, value);
        }

        bool isUnique = true; 

        for (size_t t = 0; t < uniqueTreesCount; ++t) {
            if (compareTrees(roots[t], currentRoot) && compareTrees(currentRoot, roots[t])) {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            roots[uniqueTreesCount] = currentRoot;
            uniqueTreesCount++;
        } else {
            freeTree(currentRoot); 
        }
    }

    printf("%d\n", uniqueTreesCount); 

    for (size_t i = 0; i < uniqueTreesCount; ++i) {
        freeTree(roots[i]);
    }
    free(roots);

    return 0;
}

