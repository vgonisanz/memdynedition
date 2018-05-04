#include "crc32sample.h"

#define LOG_TAG "main"
#include "config.h"

int main()
{
    LOGI("Executing crc32 sample...");
    memdynedition::testCRC32();
    memdynedition::testCRC32PerDW();
    return 0;
}
