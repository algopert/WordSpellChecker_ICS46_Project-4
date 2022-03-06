// WordSetLoader.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun

#include <algorithm>
#include <cctype>
#include <fstream>
#include "WordSetLoader.hpp"



std::vector<std::string> WordSetLoader::load(const std::string& wordFilePath)
{
    std::ifstream wordFile{wordFilePath};
    std::vector<std::string> words;

    std::string word;

    while (std::getline(wordFile, word))
    {
        std::transform(
            word.begin(), word.end(), word.begin(),
            [](auto c) { return std::toupper(c); });

        word.erase(
            std::remove_if(
                word.begin(), word.end(),
                [](auto c) { return c == '\r' || c == '\n'; }),
            word.end());

        words.push_back(word);
    }

    return words;
}

