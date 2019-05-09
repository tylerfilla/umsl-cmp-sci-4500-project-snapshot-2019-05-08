/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stddef.h>

#include "../face.h"

#include "../../log.h"
#include "../../service.h"

#define LOG_TAG "face"

static int proc_hello(struct service* svc, const void* arg1, void* arg2) {
  LOGI("Hello, world!");
  return 0;
}

static service_proc get_proc(const struct service* svc, int proc) {
  switch (proc) {
    case service_face_proc_hello:
      return &proc_hello;
    default:
      return NULL;
  }
}

static int on_load(struct service* svc) {
  LOGI("Face service load");
  return 0;
}

static int on_unload(struct service* svc) {
  LOGI("Face service unload");
  return 0;
}

static int on_start(struct service* svc) {
  LOGI("Face service start");
  return 0;
}

static int on_stop(struct service* svc) {
  LOGI("Face service stop");
  return 0;
}

struct service* const SERVICE_FACE = &(struct service) {
  .name = "face",
  .description = "The face service does face recognition.",
  .iface = &(struct service_iface) {
    .get_proc = &get_proc,
    .on_load = &on_load,
    .on_unload = &on_unload,
    .on_start = &on_start,
    .on_stop = &on_stop,
  },
};
