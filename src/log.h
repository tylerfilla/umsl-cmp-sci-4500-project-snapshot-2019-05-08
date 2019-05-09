/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/**
 * Log a message.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOG(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)

/**
 * Log with TRACE severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGT(fmt, ...) LOG("TRACE: " fmt, ##__VA_ARGS__)

/**
 * Log with DEBUG severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGD(fmt, ...) LOG("DEBUG: " fmt, ##__VA_ARGS__)

/**
 * Log with INFO severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGI(fmt, ...) LOG("INFO: " fmt, ##__VA_ARGS__)

/**
 * Log with WARN severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGW(fmt, ...) LOG("WARN: " fmt, ##__VA_ARGS__)

/**
 * Log with ERROR severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGE(fmt, ...) LOG("ERROR: " fmt, ##__VA_ARGS__)

/**
 * Log with FATAL severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGF(fmt, ...) LOG("FATAL: " fmt, ##__VA_ARGS__)

#endif // #ifndef LOG_H
