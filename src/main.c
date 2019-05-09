/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "log.h"

int main() {
  LOGT("This log has severity %s",
    (struct log_format_arg) {.kind = log_format_arg_kind_string, .value.as_string = {"TRACE", 5}});
  LOGD("This log has severity %s",
    (struct log_format_arg) {.kind = log_format_arg_kind_string, .value.as_string = {"DEBUG", 5}});
  LOGI("This log has severity %s",
    (struct log_format_arg) {.kind = log_format_arg_kind_string, .value.as_string = {"INFO", 4}});
  LOGW("This log has severity %s",
    (struct log_format_arg) {.kind = log_format_arg_kind_string, .value.as_string = {"WARN", 4}});
  LOGE("This log has severity %s",
    (struct log_format_arg) {.kind = log_format_arg_kind_string, .value.as_string = {"ERROR", 5}});
  LOGF("This log has severity %s",
    (struct log_format_arg) {.kind = log_format_arg_kind_string, .value.as_string = {"FATAL", 5}});
}
