#include "player.h"

#define LOG_TAG "player"
#include "config.h"

namespace memdynedition
{

void Player::printItems()
{
    LOGI("\nPlayer items are:\n\t* coins: %u\n\t* bombs: %u\n\t* keys: %u",
            _items.coins, _items.bombs, _items.keys);
}

void Player::printStats()
{
    LOGI("\nPlayer status is:\n\t* health: %u\n\t* strenght: %u\n\t* dexterity: %u\n\
\t* constitution: %u\n\t* defense: %u\n\t* charisma: %u\n\t* wisdom: %u\n\t* willpower: %u\n\
\t* perception: %u\n\t* luck: %u", _stats.health, _stats.strenght, _stats.dexterity,
        _stats.constitution, _stats.defense, _stats.charisma, _stats.wisdom,
        _stats.willpower, _stats.perception, _stats.luck);
}

void Player::useBomb()
{
    if (_items.bombs > 0)
    {
        _items.bombs -= 1;
        LOGI("Using bomb! remaining: %u", _items.bombs);
    }
    else
    {
        LOGI("You have NO bombs!");
    }
}

}   /* namespace memdynedition */
