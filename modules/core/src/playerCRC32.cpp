#include "playerCRC32.h"

#define LOG_TAG "playerCRC32"
#include "config.h"

namespace memdynedition
{

PlayerCRC32::PlayerCRC32()
{
    LOGI("Adding CRC32 to player one");
    _secItems.setData(&_items, sizeof(_items));
    LOGD("Set up secure struct items with size: %u", sizeof(_items));

    /* Update CRC */
    uint32_t itemsCRC32 = _secItems.updateCRC32();
    LOGI("Initial items CRC32: 0x%08X", itemsCRC32);
}

void PlayerCRC32::useBomb()
{
    if (_items.bombs > 0)
    {
        checkIntegrity();   /* Detect if at this time the value has been modified */

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

void PlayerCRC32::dropCoin()
{
    if (_items.coins > 0)
    {
        checkIntegrity();   /* Detect if at this time the value has been modified */

        /* Assign value automatically sleeping 1s, if variable is locked is detected! */
        const uint32_t sleepInUs = 1000;
        if(!_secItems.assign<uint32_t>(&_items.coins, _items.coins - 1, sleepInUs))
            LOGE("Error assigning coins, external modification after wait a little.");

        LOGI("Dropping a coin! remaining: %u", _items.coins);
        LOGI("New items CRC32: 0x%08X", _secItems.getCRC32());
    }
    else
    {
        LOGI("You have NO coins!");
    }
}

bool PlayerCRC32::checkIntegrity()
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

}   /* namespace memdynedition */
