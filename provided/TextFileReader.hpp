// TextFileReader.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// Reads an input file and makes it possible to consume it word by word,
// with spaces and punctuation skipped (except for hyphens or apostrophes
// within words).

#ifndef TEXTFILEREADER_HPP
#define TEXTFILEREADER_HPP

#include <fstream>
#include <string>



class TextFileReader
{
public:
    TextFileReader(const std::string& textFilePath);

    bool noMoreWords() const;
    void advanceToNextWord();

    std::string currentLine() const;
    std::string currentWord() const;

private:
    std::ifstream textFile;

    bool eof;

    std::string line;
    int lineIndex;

    std::string word;

private:
    void advanceToNextLine();
};



#endif

