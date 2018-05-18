#ifndef __MENU_BASIC_H
#define __MENU_BASIC_H

#include <stdint.h>
#include <iostream>
#include <string>

#include "player.h"

namespace memdynedition
{

constexpr unsigned int hash(const char* str, int h = 0);    /* Used to switch string */

class Menu
{
public:
    Menu();
    ~Menu() = default;

    void run();

private:
    Player _player;
    bool _quit;
    std::string _userInput;

    void printOptions();
    void getInput();
    void processOption();
    void quit();
};

}   /* namespace memdynedition */

#endif /* __MENU_BASIC_H */
