#ifndef __LOGGER_H
#define __LOGGER_H

/* Check if LOG_TAG is defined */
#if !defined(LOG_TAG)
#pragma message("logger.h included without define LOG_TAG before!")
#endif

/* Initialize logger */
#if defined(___LOG_DEBUG) || defined(___LOG_INFO) || defined(___LOG_WARNING) || defined(___LOG_ERROR)
#include <chrono>
#include <ctime>

/* Be careful with multithreading!!! */
static char __TIME_ARRAY[100];
static time_t __TIME_NOW = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

#   define UPDATE_TIME { __TIME_NOW = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
                         std::strftime(__TIME_ARRAY, sizeof(__TIME_ARRAY), "[%Y-%m-%d %H:%M:%S]", std::localtime(&__TIME_NOW)); }
#endif

/* Debug level */
#if defined(___LOG_DEBUG)
#  include <iostream>
#  define LOGD(...) { UPDATE_TIME; fprintf(stdout, "[%s][D][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#  define LOGI(...) { UPDATE_TIME; fprintf(stdout, "[%s][V][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#  define LOGW(...) { UPDATE_TIME; fprintf(stdout, "[%s][W][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#  define LOGE(...) { UPDATE_TIME; fprintf(stdout, "[%s][E][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
/* Info level */
#elif defined(___LOG_INFO)
#  include <iostream>
#  define LOGD(...)
#  define LOGI(...) { UPDATE_TIME; fprintf(stdout, "[%s][V][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#  define LOGW(...) { UPDATE_TIME; fprintf(stdout, "[%s][W][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#  define LOGE(...) { UPDATE_TIME; fprintf(stdout, "[%s][E][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
/* Warning level */
#elif defined(___LOG_WARNING)
#  include <iostream>
#  define LOGD(...)
#  define LOGI(...)
#  define LOGW(...) { UPDATE_TIME; fprintf(stdout, "[%s][W][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#  define LOGE(...) { UPDATE_TIME; fprintf(stdout, "[%s][E][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
/* Error level */
#elif defined(___LOG_ERROR)
#  include <iostream>
#  define LOGD(...)
#  define LOGI(...)
#  define LOGW(...)
#  define LOGE(...) { UPDATE_TIME; fprintf(stdout, "[%s][E][%s] ", __TIME_ARRAY, LOG_TAG); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
/* NO LOGS level */
#else
#  define LOGD(...)
#  define LOGI(...)
#  define LOGW(...)
#  define LOGE(...)
#endif

#endif /* __LOGGER_H */
