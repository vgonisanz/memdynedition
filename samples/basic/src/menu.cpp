#include "menu.h"

#define LOG_TAG "menu"
#include "config.h"

namespace memdynedition
{

Menu::Menu():
_player(),
_quit(false),
_userInput(0) {};

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
    _userInput = getchar();
    getchar();  /* Ignore \n */
}

void Menu::quit()
{
    _quit = true;
}

void Menu::processOption()
{
    switch (_userInput)
    {
        case 'q':
            quit();
            break;
        case '1':
            _player.printStats();
            break;
        case '2':
            _player.printItems();
            break;
        case '3':
            _player.useBomb();
            break;
        case '\n':
            break;
        default:
            LOGE("Option invalid!");
            break;
    }
}

bool Menu::isReturnCarriage()
{
    return (_userInput == '\n');
}

void Menu::run()
{
    LOGI("Menu is running...");

    while (!_quit)
    {
        /* Avoid processing return carriage.
         * I don't like how multioption is processed
         * nearly works but....
         */
        if (!isReturnCarriage())
            printOptions();

        getInput();

        if (!isReturnCarriage())
            processOption();
    }
    LOGI("Quit menu!");
}

}   /* namespace memdynedition */
