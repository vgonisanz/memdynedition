#include "player.h"

#define LOG_TAG "player"
#include "config.h"

namespace memdynedition
{

Player::Player()
{
    _secItems.setData(&_items);

    /* Update CRC */
    uint32_t itemsCRC32 = _secItems.update();
    LOGI("Initial items CRC32: 0x%08X", itemsCRC32);
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

void Player::useBomb()
{
    if (_items.bombs > 0)
    {
        /* Check */
        bool isValid = _secItems.check();
        if (isValid)
        {
            LOGI("The data has not been altered.");
        }
        else
        {
            LOGE("The data was externally modified!!");
        }

        /* Process: TODO check/think about a secure edit using Securizer class  */
        _items.bombs -= 1;
        LOGI("Using bomb! remaining: %u", _items.bombs);

        /* Update */
        uint32_t itemsCRC32 = _secItems.update();
        LOGI("New items CRC32: 0x%08X", itemsCRC32);
    }
    else
    {
        LOGI("You have NO bombs!");
    }
}

}   /* namespace memdynedition */
