#include "core.h"

#define LOG_TAG "basicsample"
#include "config.h"

int main()
{
    LOGI("Executing basic sample...");
    memdynedition::testCRC32();
    memdynedition::testCRC32PerDW();

    return 0;
}
