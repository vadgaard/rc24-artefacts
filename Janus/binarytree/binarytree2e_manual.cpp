#include <stdio.h>     /* printf */
#include <stdlib.h>     /* atoi */

typedef struct Node {
    int value;          // Value of the node
    struct Node* left;  // Pointer to the left child
    struct Node* right; // Pointer to the right child
} Node;

Node* createNode(int value) {
    Node* newNode = new Node;
    if (newNode != NULL) {
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

void insert(int value, Node** tree) {
    if (*tree == NULL) {
        *tree = createNode(value); // Insert the new node if current spot is NULL
    } else if (value < (*tree)->value) {
        insert(value, &((*tree)->left)); // Recur on the left subtree
    } else if (value > (*tree)->value) {
        insert(value, &((*tree)->right)); // Recur on the right subtree
    }
    // If value is equal to the node's value, do not insert duplicates
}

bool dfs(Node* node, int target) {
    // Base case: if the current node is NULL, the target is not found
    if (node == NULL) {
        return false;
    }

    // Check if the current node's value matches the target
    if (node->value == target) {
        return true; // Target found
    }

    // Recursively search in the left subtree
    if (dfs(node->left, target)) {
        return true; // Target found in the left subtree
    }

    // Recursively search in the right subtree
    if (dfs(node->right, target)) {
        return true; // Target found in the right subtree
    }

    return false; // Target not found in either subtree
}

void printTree(Node* node) {
    if (node == NULL) return;

    printf("%d {", node->value);

    printTree(node->left);

    printf("}{");

    printTree(node->right);

    printf("}");
}

void freeTree(Node* node) {
    if (node == NULL) return; // Base case: node is NULL

    // First, free the left subtree
    freeTree(node->left);

    // Then, free the right subtree
    freeTree(node->right);

    // Finally, free the current node
    delete node;
}

int main(int argc, char **argv) {
    if (argc < 2) {
      return 1;
    }

    int n = 0;

    n += (int) atoi(argv[1]);

    Node* root = NULL; // Starting with an empty tree
    insert(n / 2, &root);

    for (int i = 0; i < n / 2; i++) {
        insert(i, &root);
    }

    for (int i = n / 2 + 1; i < n; i++) {
        insert(i, &root);
    }

    // printTree(root);

    dfs(root, n / 2 - 1);

    freeTree(root);

    return 0;
}
