// SpellChecker.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// This class implements a basic spell checker.  It uses the given
// WordChecker to determine whether words are spelled correctly,
// the given TextFileReader to determine which words to check,
// and notifies any observers whenever misspellings are found.

#ifndef SPELLCHECKER_HPP
#define SPELLCHECKER_HPP

#include <ics46/observable/Observable.hpp>
#include "SpellCheckerListener.hpp"
#include "TextFileReader.hpp"
#include "WordChecker.hpp"



class SpellChecker : public ics46::observable::Observable<SpellCheckerListener>
{
public:
    void run(const WordChecker& wordChecker, TextFileReader& reader);

private:
    void notifyMisspellingFound(
        const std::string& word, const std::string& line,
        const std::vector<std::string>& suggestions);
};



#endif

