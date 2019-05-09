/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef LOG_H
#define LOG_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

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

  /** The format string. */
  const char* format;

  /** The format arguments array. */
  struct log_format_arg* format_args;

  /** The length of the format arguments array. */
  size_t format_args_len;

  /** The source line number. */
  unsigned int line;

  /** The source file name. */
  const char* file;
};

/** A kind of log format argument. */
enum log_format_arg_kind {
  /** As char. */
  log_format_arg_kind_char,

  /** As signed char. */
  log_format_arg_kind_signed_char,

  /** As unsigned char. */
  log_format_arg_kind_unsigned_char,

  /** As short int. */
  log_format_arg_kind_short,

  /** As unsigned short int. */
  log_format_arg_kind_unsigned_short,

  /** As int. */
  log_format_arg_kind_int,

  /** As unsigned int. */
  log_format_arg_kind_unsigned_int,

  /** As long int. */
  log_format_arg_kind_long,

  /** As unsigned long int. */
  log_format_arg_kind_unsigned_long,

  /** As long long int. */
  log_format_arg_kind_long_long,

  /** As unsigned long long int. */
  log_format_arg_kind_unsigned_long_long,

  /** As float. */
  log_format_arg_kind_float,

  /** As double. */
  log_format_arg_kind_double,

  /** As long double. */
  log_format_arg_kind_long_double,

  /** As a char string. */
  log_format_arg_kind_string,

  /** As an arbitrary pointer. */
  log_format_arg_kind_pointer,
};

/** A log format argument value. */
union log_format_arg_value {
  /** View as char. */
  char as_char;

  /** View as signed char. */
  signed char as_signed_char;

  /** View as unsigned char. */
  unsigned char as_unsigned_char;

  /** View as signed short int. */
  signed short int as_short;

  /** View as unsigned short int. */
  unsigned short int as_unsigned_short;

  /** View as signed int. */
  signed int as_int;

  /** View as unsigned int. */
  unsigned int as_unsigned_int;

  /** View as signed long int. */
  signed long int as_long;

  /** View as unsigned long int. */
  unsigned long int as_unsigned_long;

  /** View as signed long long int. */
  signed long long int as_long_long;

  /** View as unsigned long long int. */
  unsigned long long int as_unsigned_long_long;

  /** View as float. */
  float as_float;

  /** View as double. */
  double as_double;

  /** View as long double. */
  long double as_long_double;

  /** View as a char string. */
  const char* as_string;

  /** View as an arbitrary pointer. */
  const void* as_pointer;
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

#ifdef __cplusplus
} // extern "C"
#endif

//
// Macros for Quick Submission
//
// The function-like macros that follow intended to be used to send quick
// submissions to the logging system with sane assumptions. For instance, these
// macros assume that the expansion site's source file name and line number are
// desired for the respective log request fields.
//

/**
 * Log a message with the given severity.
 *
 * The source file name and line number at the expansion site are used for the
 * file name and line number fields of the request, respectively.
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

//
// Decorations for Format Types
//
// The macros that follow are designed to be used as "decorators" for format
// arguments provided to a submission function or function-like macro.
//

/**
 * Decorate argument type char.
 *
 * @param x The argument
 */
#define LOG_ARG_CHAR(x) (struct log_format_arg) { \
      .kind = log_format_arg_kind_char,           \
      .value.as_char = (char) (x),                \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_CHAR. */
#define _c(x) LOG_ARG_CHAR(x)
#endif

/**
 * Decorate argument type signed char.
 *
 * @param x The argument
 */
#define LOG_ARG_SIGNED_CHAR(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_signed_char,            \
      .value.as_signed_char = (signed char) (x),          \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_SIGNED_CHAR. */
#define _sc(x) LOG_ARG_SIGNED_CHAR(x)
#endif

/**
 * Decorate argument type unsigned char.
 *
 * @param x The argument
 */
#define LOG_ARG_UNSIGNED_CHAR(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_unsigned_char,            \
      .value.as_unsigned_char = (unsigned char) (x),        \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_UNSIGNED_CHAR. */
#define _uc(x) LOG_ARG_UNSIGNED_CHAR(x)
#endif

/**
 * Decorate argument type signed short int.
 *
 * @param x The argument
 */
#define LOG_ARG_SHORT(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_short,            \
      .value.as_short = (short int) (x),            \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_SHORT. */
#define _s(x) LOG_ARG_SHORT(x)
#endif

/**
 * Decorate argument type unsigned short int.
 *
 * @param x The argument
 */
#define LOG_ARG_UNSIGNED_SHORT(x) (struct log_format_arg) { \
      .kind = log_format_arg_kind_unsigned_short,           \
      .value.as_unsigned_short = (unsigned short int) (x),  \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_UNSIGNED_SHORT. */
#define _us(x) LOG_ARG_UNSIGNED_SHORT(x)
#endif

/**
 * Decorate argument type signed int.
 *
 * @param x The argument
 */
#define LOG_ARG_INT(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_int,            \
      .value.as_int = (signed int) (x),           \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_INT. */
#define _i(x) LOG_ARG_INT(x)
#endif

/**
 * Decorate argument type unsigned int.
 *
 * @param x The argument
 */
#define LOG_ARG_UNSIGNED_INT(x) (struct log_format_arg) { \
      .kind = log_format_arg_kind_unsigned_int,           \
      .value.as_unsigned_int = (unsigned int) (x),        \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_UNSIGNED_INT. */
#define _ui(x) LOG_ARG_UNSIGNED_INT(x)
#endif

/**
 * Decorate argument type signed long int.
 *
 * @param x The argument
 */
#define LOG_ARG_LONG(x) (struct log_format_arg) { \
      .kind = log_format_arg_kind_long,           \
      .value.as_long = (signed long int) (x),     \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_LONG. */
#define _l(x) LOG_ARG_LONG(x)
#endif

/**
 * Decorate argument type unsigned long int.
 *
 * @param x The argument
 */
#define LOG_ARG_UNSIGNED_LONG(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_unsigned_long,            \
      .value.as_unsigned_long = (unsigned long int) (x),    \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_UNSIGNED_LONG. */
#define _ul(x) LOG_ARG_UNSIGNED_LONG(x)
#endif

/**
 * Decorate argument type signed long long int.
 *
 * @param x The argument
 */
#define LOG_ARG_LONG_LONG(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_long_long,            \
      .value.as_long_long = (signed long long int) (x), \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_LONG_LONG. */
#define _ll(x) LOG_ARG_LONG_LONG(x)
#endif

/**
 * Decorate argument type unsigned long long int.
 *
 * @param x The argument
 */
#define LOG_ARG_UNSIGNED_LONG_LONG(x) (struct log_format_arg) {     \
      .kind = log_format_arg_kind_unsigned_long_long,               \
      .value.as_unsigned_long_long = (unsigned long long int) (x),  \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_UNSIGNED_LONG_LONG. */
#define _ull(x) LOG_ARG_UNSIGNED_LONG_LONG(x)
#endif

/**
 * Decorate argument type float.
 *
 * @param x The argument
 */
#define LOG_ARG_FLOAT(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_float,            \
      .value.as_float = (float) (x),                \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_FLOAT. */
#define _f(x) LOG_ARG_FLOAT(x)
#endif

/**
 * Decorate argument type double.
 *
 * @param x The argument
 */
#define LOG_ARG_DOUBLE(x) (struct log_format_arg) { \
      .kind = log_format_arg_kind_double,           \
      .value.as_double = (double) (x),              \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_DOUBLE. */
#define _d(x) LOG_ARG_DOUBLE(x)
#endif

/**
 * Decorate argument type long double.
 *
 * @param x The argument
 */
#define LOG_ARG_LONG_DOUBLE(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_long_double,            \
      .value.as_long_double = (long double) (x),          \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_LONG_DOUBLE. */
#define _ld(x) LOG_ARG_LONG_DOUBLE(x)
#endif

/**
 * Decorate argument of char string type.
 *
 * @param x The argument
 */
#define LOG_ARG_STRING(x) (struct log_format_arg) { \
      .kind = log_format_arg_kind_string,           \
      .value.as_string = (const char*) (x),         \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_STRING. */
#define _str(x) LOG_ARG_STRING(x)
#endif

/**
 * Decorate argument of arbitrary pointer type.
 *
 * @param x The argument
 */
#define LOG_ARG_POINTER(x) (struct log_format_arg) {  \
      .kind = log_format_arg_kind_pointer,            \
      .value.as_pointer = (const void*) (x),          \
    }

#ifndef LOG_ARG_NO_SHORT
/** Alias of LOG_ARG_POINTER. */
#define _ptr(x) LOG_ARG_POINTER(x)
#endif

#endif // #ifndef LOG_H
