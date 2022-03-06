// WordSetLoader.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// A class that loads a word set from a file containing one word on
// each line.

#ifndef WORDSETLOADER_HPP
#define WORDSETLOADER_HPP

#include <string>
#include <vector>



class WordSetLoader
{
public:
    std::vector<std::string> load(const std::string& wordFilePath);
};



#endif

