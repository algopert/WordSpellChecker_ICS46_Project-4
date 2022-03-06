// OutputSpellCheckerListener.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun

#include "OutputSpellCheckerListener.hpp"


OutputSpellCheckerListener::OutputSpellCheckerListener(std::ostream& out)
    : out{out}
{
}


void OutputSpellCheckerListener::misspellingFound(
    const std::string& word, const std::string& line,
    const std::vector<std::string>& suggestions)
{
    out << std::endl;
    out << line << std::endl;
    out << "     word not found: " << word << std::endl;

    if (suggestions.size() > 0)
    {
        out << "  perhaps you meant:" << std::endl;

        for (const std::string& suggestion : suggestions)
        {
            out << "      " << suggestion << std::endl;
        }
    }
}

