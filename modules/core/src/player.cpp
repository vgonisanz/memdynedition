#include "player.h"

#define LOG_TAG "player"
#include "config.h"

namespace memdynedition
{

Player::Player()
{
    LOGI("Ready player one");
}

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

bool Player::checkIntegrity()
{
    LOGI("It can not be done.");
    return false;
}

void Player::useBomb()
{
    if (_items.bombs > 0)
    {
        /* Edit value manually */
        _items.bombs -= 1;
        LOGI("Using bomb! remaining: %u", _items.bombs);
    }
    else
    {
        LOGI("You have NO bombs!");
    }
}

void Player::dropCoin()
{
    if (_items.coins > 0)
    {
        /* Edit value manually */
        _items.coins -= 1;

        LOGI("Dropping a coin! remaining: %u", _items.coins);
    }
    else
    {
        LOGI("You have NO coins!");
    }
}

}   /* namespace memdynedition */
