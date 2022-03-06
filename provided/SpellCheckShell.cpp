// SpellCheckShell.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include "SpellCheckShell.hpp"
#include "AVLSet.hpp"
#include "EmptySet.hpp"
#include "HashSet.hpp"
#include "OutputSpellCheckerListener.hpp"
#include "Set.hpp"
#include "SkipListSet.hpp"
#include "SpellChecker.hpp"
#include "Stopwatch.hpp"
#include "StringHashing.hpp"
#include "TextFileReader.hpp"
#include "VectorSet.hpp"
#include "WordChecker.hpp"
#include "WordSetLoader.hpp"



SpellCheckShell::ShellException::ShellException(const std::string& reason)
    : reason_{reason}
{
}


std::string SpellCheckShell::ShellException::reason() const
{
    return reason_;
}



namespace
{
    std::string readString()
    {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }


    std::unique_ptr<Set<std::string>> makeWordSet(const std::string& setType)
    {
        if (setType == "AVL")
        {
            return std::make_unique<AVLSet<std::string>>();
        }
        else if (setType == "EMPTY")
        {
            return std::make_unique<EmptySet<std::string>>();
        }
        else if (setType == "HASH ZERO")
        {
            return std::make_unique<HashSet<std::string>>(hashStringAsZero);
        }
        else if (setType == "HASH SUM")
        {
            return std::make_unique<HashSet<std::string>>(hashStringAsSum);
        }
        else if (setType == "HASH PRODUCT")
        {
            return std::make_unique<HashSet<std::string>>(hashStringAsProduct);
        }
        else if (setType == "VECTOR")
        {
            return std::make_unique<VectorSet<std::string>>();
        }
        else if (setType == "SKIPLIST")
        {
            return std::make_unique<SkipListSet<std::string>>();
        }
        else
        {
            throw SpellCheckShell::ShellException{"Invalid search structure type: " + setType};
        }
    }

    
    void requireNonEmptyFileExists(const std::string& filePath)
    {
        std::ifstream file{filePath};

        if (file.is_open())
        {
            char c;
            
            if (file >> c)
            {
                return;
            }
            else
            {
                throw SpellCheckShell::ShellException{"File is empty: " + filePath};
            }
        }
        else
        {
            throw SpellCheckShell::ShellException{"Cannot open file: " + filePath};
        }
    }


    enum class OutputType
    {
        Display,
        TimeOnly
    };


    OutputType makeOutputType(const std::string& outputType)
    {
        if (outputType == "DISPLAY")
        {
            return OutputType::Display;
        }
        else if (outputType == "TIME")
        {
            return OutputType::TimeOnly;
        }
        else
        {
            throw SpellCheckShell::ShellException{"Invalid output type: " + outputType};
        }
    }


    void runWithDisplay(
        Set<std::string>& wordSet,
        const std::string& wordFilePath, const std::string& textFilePath)
    {
        SpellChecker spellChecker;

        std::shared_ptr<OutputSpellCheckerListener> output =
            std::make_shared<OutputSpellCheckerListener>(std::cout);

        spellChecker.addObserver(output);

        std::cout << std::endl;
        std::cout << "Loading word set from " << wordFilePath << " ..." << std::endl;

        for (const std::string& word : WordSetLoader{}.load(wordFilePath))
        {
            wordSet.add(word);
        }

        std::cout << "Checking spelling in " << textFilePath << " ..." << std::endl;

        WordChecker wordChecker{wordSet};
        TextFileReader reader{textFilePath};

        spellChecker.run(wordChecker, reader);
    }


    void runTimingTest(
        Set<std::string>& wordSet,
        const std::string& wordFilePath, const std::string& textFilePath)
    {
        std::cout << std::endl;
        std::cout << "Loading words from " << wordFilePath << " ..." << std::endl;

        std::vector<std::string> words = WordSetLoader{}.load(wordFilePath);

        SpellChecker spellChecker;
        Stopwatch stopwatch;

        std::cout << "Storing words into search structure ..." << std::endl;

        {
            stopwatch.start();

            for (const std::string& word : words)
            {
                wordSet.add(word);
            }

            stopwatch.stop();
        }

        double wordSetLoadDuration = stopwatch.lastDuration();

        std::cout << "Checking spelling of words in " << textFilePath
                  << " using search structure ..." << std::endl;

        {
            stopwatch.start();
            WordChecker wordChecker{wordSet};
            TextFileReader reader{textFilePath};
            spellChecker.run(wordChecker, reader);
            stopwatch.stop();
        }

        double wordSetSpellCheckDuration = stopwatch.lastDuration();

        EmptySet<std::string> emptySet;
        
        std::cout << "Storing words into empty set ..." << std::endl;
        {
            stopwatch.start();

            for (const std::string& word : words)
            {
                emptySet.add(word);
            }

            stopwatch.stop();
        }

        double emptySetLoadDuration = stopwatch.lastDuration();

        std::cout << "Checking spelling of words in " << textFilePath
                  << " using empty set ..." << std::endl;

        {
            stopwatch.start();
            WordChecker wordChecker{emptySet};
            TextFileReader reader{textFilePath};
            spellChecker.run(wordChecker, reader);
            stopwatch.stop();
        }

        double emptySetSpellCheckDuration = stopwatch.lastDuration();

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "RESULTS" << std::endl;

        std::cout << "                LoadTime     SpellCheckTime     TotalTime" << std::endl;

        std::cout << std::left << std::setw(12) << "Everything";

        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(12)
                  << wordSetLoadDuration << "usec";
        
        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(15)
                  << wordSetSpellCheckDuration << "usec";

        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(10)
                  << (wordSetLoadDuration + wordSetSpellCheckDuration) << "usec";

        std::cout << std::endl;

        std::cout << std::left << std::setw(12) << "Empty Set";

        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(12)
                  << emptySetLoadDuration << "usec";
        
        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(15)
                  << emptySetSpellCheckDuration << "usec";

        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(10)
                  << (emptySetLoadDuration + emptySetSpellCheckDuration) << "usec";

        std::cout << std::endl;

        std::cout << std::left << std::setw(12) << "Set Only";

        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(12)
                  << (wordSetLoadDuration - emptySetLoadDuration) << "usec";
        
        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(15)
                  << (wordSetSpellCheckDuration - emptySetSpellCheckDuration) << "usec";

        std::cout << std::right << std::fixed << std::setprecision(0) << std::setw(10)
                  << (wordSetLoadDuration + wordSetSpellCheckDuration)
                     - (emptySetLoadDuration + emptySetSpellCheckDuration) << "usec";

        std::cout << std::endl;
    }
}



void SpellCheckShell::run()
{
    std::unique_ptr<Set<std::string>> wordSet = makeWordSet(readString());

    if (!wordSet->isImplemented())
    {
        throw SpellCheckShell::ShellException{
            "Search structure type not implemented (did you change isImplemented() to return true?)"};
    }

    std::string wordFilePath = readString();
    requireNonEmptyFileExists(wordFilePath);

    std::string textFilePath = readString();
    requireNonEmptyFileExists(textFilePath);

    OutputType outputType = makeOutputType(readString());

    switch (outputType)
    {
    case OutputType::Display:
        runWithDisplay(*wordSet, wordFilePath, textFilePath);
        break;

    case OutputType::TimeOnly:
        runTimingTest(*wordSet, wordFilePath, textFilePath);
        break;
    }
}

