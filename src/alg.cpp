// Copyright 2021 NNTU-CS
// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        return;
    }

    std::string currentWord;
    char symbol;

    while (inputFile.get(symbol)) {
        if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) {
            if (symbol >= 'A' && symbol <= 'Z') {
                symbol = symbol - 'A' + 'a';
            }
            currentWord += symbol;
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord.clear();
            }
        }
    }

    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }

    inputFile.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> allNodes = tree.getNodes();

    std::sort(allNodes.begin(), allNodes.end(),
        [](const std::pair<std::string, int>& firstPair,
           const std::pair<std::string, int>& secondPair) {
            if (firstPair.second == secondPair.second) {
                return firstPair.first < secondPair.first;
            }
            return firstPair.second > secondPair.second;
        });

    std::ofstream outputFile("result/freq.txt");
    if (!outputFile.is_open()) {
        return;
    }

    for (const auto& node : allNodes) {
        outputFile << node.first << ": " << node.second << std::endl;
    }
    
    outputFile.close();
}
