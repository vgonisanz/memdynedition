#ifndef __MENU_BASIC_H
#define __MENU_BASIC_H

#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

#include "player.h"

namespace memdynedition
{

class Menu
{
public:
    Menu();
    ~Menu() = default;

    struct Option
    {
        std::string value;
        std::string description;
        std::function< void(void) > callback;

        Option(std::string value, std::string description, std::function< void(void) > callback)
        {
            this->value = value;
            this->description = description;
            this->callback = callback;
        }
    };

    void setOptions(std::vector<Option> options);
    void run();
    void quit();

private:
    bool _quit;
    std::string _userInput;
    std::vector<Option> _options;

    void printOptions();
    void getInput();
    void processOption();
};

}   /* namespace memdynedition */

#endif /* __MENU_BASIC_H */
