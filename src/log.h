/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef LOG_H
#define LOG_H

#include <stddef.h>
#include <stdio.h>

/** A log severity level. */
enum log_level {
  log_level_trace,
  log_level_debug,
  log_level_info,
  log_level_warn,
  log_level_error,
  log_level_fatal,
};

struct log_format_arg;

/** A request to log. */
struct log_request {
  /** The severity level. */
  enum log_level level;

  /** The format string (source lifetime). */
  const char* format;

  /** The format arguments array (source lifetime). */
  struct log_format_arg* format_args;

  /** The length of the format arguments array. */
  size_t format_args_len;

  /** The source line number. */
  unsigned int line;

  /** The source file name (source lifetime). */
  const char* file;
};

/** A log format argument value. */
union log_format_arg_value {
  /** View as char. */
  char as_char;

  /** View as signed char. */
  signed char as_signed_char;

  /** View as unsigned char. */
  unsigned char as_unsigned_char;

  /** View as short int. */
  short as_short;

  /** View as unsigned short int. */
  unsigned short as_unsigned_short;

  /** View as int. */
  int as_int;

  /** View as unsigned int. */
  unsigned int as_unsigned_int;

  /** View as long int. */
  long as_long;

  /** View as unsigned long int. */
  unsigned long as_unsigned_long;

  /** View as long long int. */
  long long as_long_long;

  /** View as unsigned long long int. */
  unsigned long long as_unsigned_long_long;

  /** View as a char string. */
  struct {
    /** The string data (source lifetime). */
    const char* data;

    /** The string size. */
    size_t size;
  } as_string;

  /** View as an arbitrary pointer (source lifetime). */
  void* as_pointer;
};

/** A kind of log format argument. */
enum log_format_arg_kind {
  log_format_arg_kind_char,
  log_format_arg_kind_signed_char,
  log_format_arg_kind_unsigned_char,
  log_format_arg_kind_short,
  log_format_arg_kind_unsigned_short,
  log_format_arg_kind_int,
  log_format_arg_kind_unsigned_int,
  log_format_arg_kind_long,
  log_format_arg_kind_unsigned_long,
  log_format_arg_kind_long_long,
  log_format_arg_kind_unsigned_long_long,
  log_format_arg_kind_string,
  log_format_arg_kind_pointer,
};

/** A log format argument. */
struct log_format_arg {
  /** The argument kind. */
  enum log_format_arg_kind kind;

  /** The argument value. */
  union log_format_arg_value value;
};

/** @private */
void log__submit_request(struct log_request* req);

/**
 * Log a message.
 *
 * @param lvl The severity level
 * @param fmt The format string literal
 * @param ... The format arguments
 */
#define LOG(lvl, fmt, ...) log__submit_request(&(struct log_request) {                                      \
      .level = (enum log_level) (lvl),                                                                      \
      .format = (const char*) (fmt),                                                                        \
      .format_args = (struct log_format_arg[]) { __VA_ARGS__ },                                             \
      .format_args_len = sizeof((struct log_format_arg[]) { __VA_ARGS__ }) / sizeof(struct log_format_arg), \
      .line = __LINE__,                                                                                     \
      .file = __FILE__,                                                                                     \
    })

/**
 * Log with TRACE severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGT(fmt, ...) LOG(log_level_trace, (fmt), ##__VA_ARGS__)

/**
 * Log with DEBUG severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGD(fmt, ...) LOG(log_level_debug, (fmt), ##__VA_ARGS__)

/**
 * Log with INFO severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGI(fmt, ...) LOG(log_level_info, (fmt), ##__VA_ARGS__)

/**
 * Log with WARN severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGW(fmt, ...) LOG(log_level_warn, (fmt), ##__VA_ARGS__)

/**
 * Log with ERROR severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGE(fmt, ...) LOG(log_level_error, (fmt), ##__VA_ARGS__)

/**
 * Log with FATAL severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGF(fmt, ...) LOG(log_level_fatal, (fmt), ##__VA_ARGS__)

#endif // #ifndef LOG_H
