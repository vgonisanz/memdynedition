#include "core.h"

#define LOG_TAG "core"
#include "config.h"

namespace my_main_project
{
    void test()
    {
        LOGD("Debug");
        LOGI("Info");
        LOGW("Warning");
        LOGE("Error");
    }
}   /* namespace my_main_project */
