/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>
#include "log.h"

void log__submit_request(struct log_request* req) {
  // TODO: Actually do the thing here
  printf("%d [%s:%d] %s\n", req->level, req->file, req->line, req->format);
}
