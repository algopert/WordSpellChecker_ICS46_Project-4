// StringHashing.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun

#include "StringHashing.hpp"



// This hash function returns zero for all strings.  As you might imagine,
// this isn't a very good choice in practice; try it and see what happens.

unsigned int hashStringAsZero(const std::string& word)
{
    return 0;
}


// This hash function returns a hash value calculated by summing the
// character codes of each character in the string.  Consider whether
// this is a good approach, and compare it to the hash function below.

unsigned int hashStringAsSum(const std::string& word)
{
    unsigned int hash = 0;

    for (size_t i = 0; i < word.length(); ++i)
    {
        hash += static_cast<unsigned int>(word[i]);
    }

    return hash;
}


// This hash function returns a hash value calculated in a way that
// includes multiplication by the prime number 37 repeatedly.  Consider
// why this approach might be better or worse than the one above.

unsigned int hashStringAsProduct(const std::string& word)
{
    unsigned int hash = 0;

    for (size_t i = 0; i < word.length(); ++i)
    {
        hash *= 37;
        hash += static_cast<unsigned int>(word[i]);
    }
    
    return hash;
}

