/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>
#include "log.h"

int main() {
  printf("Hello, world!\n");

  LOGT("This log has severity %s", "TRACE");
  LOGD("This log has severity %s", "DEBUG");
  LOGI("This log has severity %s", "INFO");
  LOGW("This log has severity %s", "WARN");
  LOGE("This log has severity %s", "ERROR");
  LOGF("This log has severity %s", "FATAL");
}
