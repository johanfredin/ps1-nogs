#ifndef PSX_LOGGER_H
#define PSX_LOGGER_H

#define OFF 0
#define ERROR 1
#define WARN 2
#define INFO 3
#define DEBUG 4
#define TRACE 5

#define LOG_LEVEL DEBUG

#if LOG_LEVEL > OFF
#define LOG_INFO(M, ...) printf("[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_ERR(M, ...) printf("[ERROR] (%s:%d) " M "\n", __FILE__, __LINE__,##__VA_ARGS__)
#define LOG_WARN(M, ...) printf("[WARN] (%s:%d) " M "\n", __FILE__, __LINE__,##__VA_ARGS__)
# else
#define LOG_INFO(M, ...)
#define LOG_ERR(M, ...)
#define LOG_WARN(M, ...)
#endif

#if LOG_LEVEL >= DEBUG
#define LOG_DEBUG(M, ...) printf("[DEBUG] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(M, ...)
#endif

#if LOG_LEVEL >= TRACE
#define LOG_TRACE(M, ...) printf("[TRACE] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_TRACE(M, ...)
#endif

#endif // PSX_LOGGER_H
