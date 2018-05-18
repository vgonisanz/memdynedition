#include "menu.h"

#define LOG_TAG "menu"
#include "config.h"

namespace memdynedition
{

Menu::Menu():
_quit(false),
_userInput("")
{
};

void Menu::setOptions(std::vector<Option> options)
{
    _options = options;
}

void Menu::printOptions()
{
    std::cout << "Options:\n";
    for (auto &option : _options)
    {
        std::cout << "\t" << option.value << ". " << option.description << std::endl;
    }
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
    auto it = std::find_if(_options.begin(), _options.end(), [this](const Option& opt) { return opt.value == _userInput; });
    if (it != _options.end())
        (*it).callback();
    else
        std::cout << "Option invalid!" << std::endl;
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
