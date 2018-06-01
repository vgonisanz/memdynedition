#include "playerRS.h"
#include "securizerRS.h"

#define LOG_TAG "playerRS"
#include "config.h"

namespace memdynedition
{

PlayerRS::PlayerRS()
{
    LOGI("Adding RS to player one");
    _secItems = new SecurizerRS();
    _secItems->setData(&_items, sizeof(_items));
    _secItems->secureBlock();
    LOGD("Set up secure struct items with size: %u", sizeof(_items));
}

void PlayerRS::useBomb()
{
    checkIntegrity();   /* Detect if at this time the value has been modified BEFORE use or check error */
    if (_items.bombs > 0)
    {
        /* Edit value manually */
        _items.bombs -= 1;
        _secItems->secureBlock();
        LOGI("Using bomb! remaining: %u", _items.bombs);
    }
    else
    {
        LOGI("You have NO bombs!");
    }
}

void PlayerRS::dropCoin()
{
    checkIntegrity();   /* Detect if at this time the value has been modified BEFORE use or check error */
    if (_items.coins > 0)
    {
        /* Edit value manually */
        _items.coins -= 1;
        _secItems->secureBlock();
        LOGI("Dropping a coin! remaining: %u", _items.coins);
    }
    else
    {
        LOGI("You have NO coins!");
    }
}

bool PlayerRS::checkIntegrity()
{
    /* Check */
    bool isValid = _secItems->check();
    if (isValid)
    {
        LOGI("The data has not been altered.");
    }
    else
    {
        LOGE("The data was externally modified, restoring...");
        _secItems->restoreBlock();
    }
    return isValid;
}

}   /* namespace memdynedition */
