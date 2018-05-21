#include "player.h"

#define LOG_TAG "player"
#include "config.h"

namespace memdynedition
{

Player::Player()
{
    _secItems.setData(&_items, sizeof(_items));
    LOGD("Set up secure struct items with size: %u", sizeof(_items));

    /* Update CRC */
    uint32_t itemsCRC32 = _secItems.updateCRC32();
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

bool Player::checkIntegrity()
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
    return isValid;
}

void Player::useBomb()
{
    if (_items.bombs > 0)
    {
        checkIntegrity();

        /* Edit value manually */
        _items.bombs -= 1;
        LOGI("Using bomb! remaining: %u", _items.bombs);

        /* Update manually CRC32 */
        uint32_t itemsCRC32 = _secItems.updateCRC32();
        LOGI("New items CRC32: 0x%08X", itemsCRC32);
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
        checkIntegrity();

        /* Assign value automatically */
        if(!_secItems.assign<uint32_t>(&_items.coins, _items.coins - 1))
            LOGE("Error assigning coins");
            
        LOGI("Dropping a coin! remaining: %u", _items.coins);
        LOGI("New items CRC32: 0x%08X", _secItems.getCRC32());
    }
    else
    {
        LOGI("You have NO coins!");
    }
}

}   /* namespace memdynedition */
