// main.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// You will not need to modify this file at all; it simply calls into the
// provided code and prints any error messages that emanate from it.

#include <iostream>
#include "SpellCheckShell.hpp"


int main()
{
    try
    {
        SpellCheckShell shell;
        shell.run();
    }
    catch (SpellCheckShell::ShellException& e)
    {
        std::cout << "ERROR: " << e.reason() << std::endl;
    }

    return 0;
}

