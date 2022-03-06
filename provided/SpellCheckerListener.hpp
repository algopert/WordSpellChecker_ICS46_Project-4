// SpellCheckerListener.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// An abstract base class for listeners that are told when spell
// checkers do interesting things.  At present, there's only one
// such thing: a notification that a misspelling was found.

#ifndef SPELLCHECKERLISTENER_HPP
#define SPELLCHECKERLISTENER_HPP

#include <string>
#include <vector>



class SpellCheckerListener
{
public:
    virtual ~SpellCheckerListener() = default;

    virtual void misspellingFound(
        const std::string& word, const std::string& line,
        const std::vector<std::string>& suggestions) = 0;
};



#endif

