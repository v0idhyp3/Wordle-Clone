#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <ctime>
#include <cstdlib>

void printAnswerInColor(std::string& solution, std::string& answer) {
    int size = solution.size();

    if (size != answer.size()) return;

    std::unordered_map<char, int> lettersInSolution;
    std::vector<std::string> colors(size, "\033[90m");

    for (int it = 0; it < size; ++it) {
        if (solution[it] == answer[it]) {
            colors[it] = "\033[32m";
        }
        else {
            ++lettersInSolution[solution[it]];
        }
    }

    for (int it = 0; it < size; ++it) {
        if (solution[it] != answer[it] && lettersInSolution[answer[it]]) {
            colors[it] = "\033[33m";
            --lettersInSolution[answer[it]];
        }
        std::cout << colors[it] << answer[it] << "\033[0m";
    }

    std::cout << "\n";
}

void getWordList(std::unordered_set<std::string>& output, int wordSize) {
    std::ifstream file;

    switch (wordSize) {
    case 5:
        file = std::ifstream("word5.txt");
        break;
    }

    std::string line;

    while (std::getline(file, line)) {
        output.insert(line);
    }
}

std::string getRandomSolution(std::unordered_set<std::string>& wordList) {
    std::srand(std::time(0));
    auto it = std::next(wordList.begin(), std::rand() % wordList.size());
    return *it;
}

bool isAnswerValid(std::unordered_set<std::string>& wordList, std::string& answer) {
    return (wordList.find(answer) != wordList.end());
}

void gameLoop(int wordSize, int triesTotal) {
    std::unordered_set<std::string> wordList;
    getWordList(wordList, wordSize);
    std::string solution = getRandomSolution(wordList);
    std::string answer;
    int tryNum = 1;
    while (tryNum <= triesTotal) {
        do {
            std::cout << "(" << tryNum << "/" << triesTotal << ") ";
            std::cin >> answer;
            std::cout << "\x1b[A" << "\033[2K";
        } while (!isAnswerValid(wordList, answer));
        std::cout << "(" << tryNum << "/" << triesTotal << ") ";
        printAnswerInColor(solution, answer);

        if (solution == answer) break;

        ++tryNum;
    }

    std::cout << (tryNum <= triesTotal ? "YOU WIN! " : "YOU LOSE! ") << "SOLUTION: " << solution << "\n";

    system("pause");
}

int main() {
    gameLoop(5, 6);
}

