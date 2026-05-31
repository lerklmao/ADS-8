// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template<typename Type>
class BST {
 private:
    struct TreeNode {
        Type value;
        int count;
        TreeNode* leftChild;
        TreeNode* rightChild;

        explicit TreeNode(const Type& val)
            : value(val), count(1), leftChild(nullptr), rightChild(nullptr) {}
    };

    TreeNode* treeRoot;
    int totalElements;

    TreeNode* insertNode(TreeNode* currentNode, const Type& val) {
        if (currentNode == nullptr) {
            totalElements++;
            return new TreeNode(val);
        }
        if (val < currentNode->value) {
            currentNode->leftChild = insertNode(currentNode->leftChild, val);
        } else if (val > currentNode->value) {
            currentNode->rightChild = insertNode(currentNode->rightChild, val);
        } else {
            currentNode->count++;
        }
        return currentNode;
    }

    int calculateHeight(TreeNode* currentNode) const {
        if (currentNode == nullptr) {
            return -1;
        }
        int leftHeight = calculateHeight(currentNode->leftChild);
        int rightHeight = calculateHeight(currentNode->rightChild);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    int findCount(TreeNode* currentNode, const Type& val) const {
        if (currentNode == nullptr) {
            return 0;
        }
        if (val == currentNode->value) {
            return currentNode->count;
        }
        
        if (val < currentNode->value) {
            return findCount(currentNode->leftChild, val);
        }
        
        return findCount(currentNode->rightChild, val);
    }

    void clearTree(TreeNode* currentNode) {
        if (currentNode == nullptr) {
            return;
        }
        clearTree(currentNode->leftChild);
        clearTree(currentNode->rightChild);
        delete currentNode;
    }

    void collectNodes(TreeNode* currentNode, std::vector<std::pair<Type, int>>& result) const {
        if (currentNode == nullptr) {
            return;
        }
        collectNodes(currentNode->leftChild, result);
        result.push_back({currentNode->value, currentNode->count});
        collectNodes(currentNode->rightChild, result);
    }

 public:
    BST() : treeRoot(nullptr), totalElements(0) {}

    ~BST() {
        clearTree(treeRoot);
    }

    void insert(const Type& val) {
        treeRoot = insertNode(treeRoot, val);
    }

    int depth() const {
        return calculateHeight(treeRoot);
    }

    int search(const Type& val) const {
        return findCount(treeRoot, val);
    }

    int size() const {
        return totalElements;
    }

    bool empty() const {
        return treeRoot == nullptr;
    }

    std::vector<std::pair<Type, int>> getNodes() const {
        std::vector<std::pair<Type, int>> result;
        collectNodes(treeRoot, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
