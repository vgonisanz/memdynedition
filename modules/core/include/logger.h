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
#  define LOGD(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[D]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
#  define LOGI(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[I]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
#  define LOGW(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[W]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
#  define LOGE(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[E]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
/* Info level */
#elif defined(___LOG_INFO)
#  include <iostream>
#  define LOGD(...)
#  define LOGI(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[I]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
#  define LOGW(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[W]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
#  define LOGE(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[E]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
/* Warning level */
#elif defined(___LOG_WARNING)
#  include <iostream>
#  define LOGD(...)
#  define LOGI(...)
#  define LOGW(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[W]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
#  define LOGE(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[E]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
/* Error level */
#elif defined(___LOG_ERROR)
#  include <iostream>
#  define LOGD(...)
#  define LOGI(...)
#  define LOGW(...)
#  define LOGE(...) { UPDATE_TIME; std::cout << __TIME_ARRAY << "[E]" << "[" << LOG_TAG << "] " << __VA_ARGS__ << std::endl; }
/* NO LOGS level */
#else
#  define LOGD(...)
#  define LOGI(...)
#  define LOGW(...)
#  define LOGE(...)
#endif

#endif /* __LOGGER_H */
