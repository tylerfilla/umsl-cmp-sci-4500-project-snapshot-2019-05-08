/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "log.h"

int main() {
  LOGT("This log has severity {}", _str("TRACE"));
  LOGD("This log has severity {}", _str("DEBUG"));
  LOGI("This log has severity {}", _str("INFO"));
  LOGW("This log has severity {}", _str("WARN"));
  LOGE("This log has severity {}", _str("ERROR"));
  LOGF("This log has severity {}", _str("FATAL"));
}
