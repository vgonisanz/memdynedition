#include "playerCP.h"

#define LOG_TAG "playerCP"
#include "config.h"

namespace memdynedition
{

PlayerCP::PlayerCP()
{
    LOGI("This player have a copy to player one data");
    _secItems.setData(&_items, sizeof(_items));
    LOGD("Set up secure struct items with size: %u", sizeof(_items));
}

void PlayerCP::useBomb()
{
    checkIntegrity();   /* Detect if at this time the value has been modified */

    if (_items.bombs > 0)
    {
        /* Edit value manually */
        _items.bombs -= 1;
        _secItems.update();
        LOGI("Using bomb! remaining: %u", _items.bombs);
    }
    else
    {
        LOGI("You have NO bombs!");
    }
}

void PlayerCP::dropCoin()
{
    checkIntegrity();   /* Detect if at this time the value has been modified */

    if (_items.coins > 0)
    {
        /* Edit value manually */
        _items.coins -= 1;
        _secItems.update();
        LOGI("Dropping a coin! remaining: %u", _items.coins);
    }
    else
    {
        LOGI("You have NO coins!");
    }
}

bool PlayerCP::checkIntegrity()
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
        _secItems.restore();
    }
    return isValid;
}

}   /* namespace memdynedition */
