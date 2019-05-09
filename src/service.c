/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "service.h"

#define LOG_TAG "service"

/** Internal service state. */
struct service_state {
  /** Nonzero if service is started. */
  int started;
};

service_proc service_get_proc(const struct service* svc, int proc) {
  LOGT("Get procedure {}#{}", _str(svc->name), _i(proc));

  // Abort if service not loaded
  if (!svc->state) {
    LOGE("{} is not loaded", _str(svc->name));
    return NULL;
  }

  return svc->iface->get_proc(svc, proc);
}

int service_load(struct service* svc) {
  LOGT("Loading {}", _str(svc->name));

  // Abort if service already loaded
  if (svc->state) {
    LOGE("{} is already loaded", _str(svc->name));
    return 1;
  }

  // Create state for service
  svc->state = malloc(sizeof *svc->state);
  if (!svc->state) {
    LOGE("{} state alloc failed", _str(svc->name));
    return 1;
  }

  // Notify service
  if (svc->iface->on_load(svc)) {
    LOGE("{} aborted during load", _str(svc->name));

    // Service aborted during load
    free(svc->state);
    svc->state = NULL;
    return 1;
  }

  LOGI("Loaded {}", _str(svc->name));
  LOGI("{}", _str(svc->description));

  return 0;
}

int service_unload(struct service* svc) {
  LOGT("Unloading {}", _str(svc->name));

  // Abort if service not loaded
  if (!svc->state) {
    LOGE("{} is not loaded", _str(svc->name));
    return 1;
  }

  // Make a good-faith effort to stop service if started
  if (svc->state->started) {
    LOGT("{} is still started, so stopping it before unload", _str(svc->name));
    service_stop(svc);
  }

  // Notify service
  if (svc->iface->on_unload(svc)) {
    // Unload cannot be aborted
    LOGW("{} returned exceptional status during unload", _str(svc->name));
  }

  // Delete state for service
  free(svc->state);
  svc->state = NULL;

  return 0;
}

int service_start(struct service* svc) {
  LOGT("Starting {}", _str(svc->name));

  // Abort if service not loaded
  if (!svc->state) {
    LOGE("{} is not loaded", _str(svc->name));
    return 1;
  }

  // Abort if service already started
  if (svc->state->started) {
    LOGE("{} is already started", _str(svc->name));
    return 1;
  }

  // Set started state
  svc->state->started = 1;

  // Notify service
  if (svc->iface->on_start(svc)) {
    LOGE("{} aborted during start", _str(svc->name));

    // Service aborted during start
    svc->state->started = 0;
    return 1;
  }

  LOGI("Started {}", _str(svc->name));

  return 0;
}

int service_stop(struct service* svc) {
  LOGT("Stopping {}", _str(svc->name));

  // Abort if service not loaded
  if (!svc->state) {
    LOGE("{} is not loaded", _str(svc->name));
    return 1;
  }

  // Abort if service not started
  if (!svc->state->started) {
    LOGE("{} is not started", _str(svc->name));
    return 1;
  }

  // Clear started state
  svc->state->started = 0;

  // Notify service
  if (svc->iface->on_stop(svc)) {
    // Stop cannot be aborted
    LOGW("{} returned exceptional status during stop", _str(svc->name));
  }

  LOGI("Stopped {}", _str(svc->name));

  return 0;
}
