#ifndef __MENU_BASIC_H
#define __MENU_BASIC_H

#include <stdint.h>
#include <iostream>
#include <string>

#include "player.h"

namespace memdynedition
{

class Menu
{
public:
    Menu();
    ~Menu() = default;

    void run();

private:
    Player _player;
    bool _quit;
    uint8_t _userInput;

    void printOptions();
    void getInput();
    void processOption();
    inline bool isReturnCarriage();
    void quit();
};

}   /* namespace memdynedition */

#endif /* __MENU_BASIC_H */
