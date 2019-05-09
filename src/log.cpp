/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <algorithm>
#include <vector>

#include <fmt/format.h>

#include "log.h"

constexpr auto log__level_name(log_level level) {
  switch (level) {
    case log_level_debug:
      return "DEBUG";
    case log_level_trace:
      return "TRACE";
    case log_level_info:
      return "INFO ";
    case log_level_warn:
      return "WARN ";
    case log_level_error:
      return "ERROR";
    case log_level_fatal:
      return "FATAL";
    default:
      return "???";
  }
}

/**
 * Convert one of our format arguments into an {fmt} format argument.
 *
 * @param arg Our format argument
 * @return {fmt}'s format argument
 */
constexpr auto log__format_arg_to_fmt_arg(const log_format_arg& arg) {
  switch (arg.kind) {
    case log_format_arg_kind_char:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_char);
    case log_format_arg_kind_signed_char:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_signed_char);
    case log_format_arg_kind_unsigned_char:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_unsigned_char);
    case log_format_arg_kind_short:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_short);
    case log_format_arg_kind_unsigned_short:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_unsigned_short);
    case log_format_arg_kind_int:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_int);
    case log_format_arg_kind_unsigned_int:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_unsigned_int);
    case log_format_arg_kind_long:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_long);
    case log_format_arg_kind_unsigned_long:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_unsigned_long);
    case log_format_arg_kind_long_long:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_long_long);
    case log_format_arg_kind_unsigned_long_long:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_unsigned_long_long);
    case log_format_arg_kind_float:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_float);
    case log_format_arg_kind_double:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_double);
    case log_format_arg_kind_long_double:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_long_double);
    case log_format_arg_kind_string:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_string);
    case log_format_arg_kind_pointer:
    default:
      return fmt::internal::make_arg<fmt::format_context>(arg.value.as_pointer);
  }
}

void log__submit_request(log_request* req) {
  // A place to hold {fmt} arguments
  std::vector<fmt::basic_format_arg<fmt::format_context>> args_vec;
  args_vec.reserve(req->format_args_len);

  // Begin and end iterators over the request format arguments
  auto format_args_begin = req->format_args;
  auto format_args_end = req->format_args + req->format_args_len;

  // Load up the {fmt} argument vector
  std::for_each(format_args_begin, format_args_end, [&](const log_format_arg& arg) {
    args_vec.push_back(log__format_arg_to_fmt_arg(arg));
  });

  // Wrap {fmt} argument vector into a packed arguments view
  fmt::basic_format_args<fmt::format_context> args(args_vec.data(), args_vec.size());

  // Format the log message
  auto msg = fmt::vformat(req->format, args);

  // Format the log record string
  auto rec = fmt::format("{} [{}:{}] {}", log__level_name(req->level), req->file, req->line, msg);

  // FIXME: Send to standard output for now
  fmt::print("{}\n", rec);
}
