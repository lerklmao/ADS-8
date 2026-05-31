// Copyright 2021 NNTU-CS
#include <iostream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    
    makeTree(tree, "src/war_peace.txt");
    
    std::cout << "=== Статистика дерева ===" << std::endl;
    std::cout << "Уникальных слов: " << tree.size() << std::endl;
    std::cout << "Глубина дерева: " << tree.depth() << std::endl;
    std::cout << std::endl;
    
    std::cout << "Сохраняю результат в result/freq.txt..." << std::endl;
    printFreq(tree);
    
    std::cout << "Готово!" << std::endl;
    
    return 0;
}
