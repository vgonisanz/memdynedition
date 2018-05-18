#include "menu.h"
#include <unistd.h>

#define LOG_TAG "menu"
#include "config.h"

namespace memdynedition
{

constexpr unsigned int hash(const char* str, int h)
{
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

Menu::Menu():
_player(),
_quit(false),
_userInput("") {};

void Menu::printOptions()
{
    std::cout << "Options:\n";
    std::cout << "\t1. Print stats.\n";
    std::cout << "\t2. Print items.\n";
    std::cout << "\t3. Use bomb.\n";
    std::cout << "\tq. Quit menu.";
    std::cout << std::endl;
    std::cout << "Select an option: ";
}

void Menu::getInput()
{
    _userInput = "";
    while(_userInput == "")
    {
        getline(std::cin, _userInput);
        usleep(1000);
    }
}

void Menu::quit()
{
    _quit = true;
}

void Menu::processOption()
{
    switch (hash(_userInput.c_str()))
    {
        case hash("q"):
            quit();
            break;
        case hash("1"):
            _player.printStats();
            break;
        case hash("2"):
            _player.printItems();
            break;
        case hash("3"):
            _player.useBomb();
            break;
        // case '\n':
        //     break;
        default:
            LOGE("Option invalid!");
            //std::cin.get();
            break;
    }
}

void Menu::run()
{
    LOGI("Menu is running...");

    while (!_quit)
    {
        printOptions();
        getInput();
        processOption();
    }
    LOGI("Quit menu!");
}

}   /* namespace memdynedition */
