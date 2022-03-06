// TextFileReader.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun

#include <cctype>
#include "TextFileReader.hpp"


TextFileReader::TextFileReader(const std::string& textFilePath)
    : textFile{textFilePath}, eof{false}, line{}, lineIndex{0}, word{}
{
    advanceToNextWord();
}


bool TextFileReader::noMoreWords() const
{
    return eof;
}


void TextFileReader::advanceToNextWord()
{
    word = "";

    while (!eof)
    {
        while (lineIndex < line.length() && !std::isalnum(line[lineIndex]))
        {
            ++lineIndex;                
        }

        if (lineIndex >= line.length())
        {
            advanceToNextLine();
            continue;
        }

        while (lineIndex < line.length() &&
            (std::isalnum(line[lineIndex]) || line[lineIndex] == '-' || line[lineIndex] == '\''))
        {
            word.push_back(std::toupper(line[lineIndex++]));
        }

        if (!std::isalnum(word[word.length() - 1]))
        {
            word.pop_back();
        }

        if (word.length() > 0)
        {
            return;
        }
    }
}


void TextFileReader::advanceToNextLine()
{
    if (std::getline(textFile, line))
    {
        lineIndex = 0;
    }
    else
    {
        eof = true;
        line = "";
        lineIndex = 0;
    }
}


std::string TextFileReader::currentLine() const
{
    return line;
}


std::string TextFileReader::currentWord() const
{
    return word;
}

