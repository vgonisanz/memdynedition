#include "menu.h"

#define LOG_TAG "basicsample"
#include "config.h"

using namespace memdynedition;

Menu menu;

int main()
{
    LOGI("Executing basic sample...");
    menu.run();
    return 0;
}
