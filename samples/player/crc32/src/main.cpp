#include "menu.h"
#include "playerCRC32.h"

#define LOG_TAG "playercrc32sample"
#include "config.h"

using namespace memdynedition;

int main()
{
    LOGI("Executing basic sample...");
    PlayerCRC32 player;
    Menu menu;

    std::vector<Menu::Option> options;
    options.push_back(Menu::Option("1", "Print stats",   std::bind(&Player::printStats, &player)));
    options.push_back(Menu::Option("2", "Print items",   std::bind(&Player::printItems, &player)));
    options.push_back(Menu::Option("3", "Use bomb",      std::bind(&Player::useBomb, &player)));
    options.push_back(Menu::Option("4", "Drop coin",      std::bind(&Player::dropCoin, &player)));
    options.push_back(Menu::Option("q", "Quit menu",     std::bind(&Menu::quit, &menu)));

    menu.setOptions(options);
    menu.run();
    return 0;
}
