/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_H
#define SERVICE_H

struct service;
struct service_iface;
struct service_state;

/**
 * A service procedure.
 *
 * @param svc The service definition
 * @param arg1 An immutable argument
 * @param arg2 A mutable argument
 * @return Zero on success, otherwise nonzero
 */
typedef int (* service_proc)(struct service* svc, const void* arg1, void* arg2);

/** A service definition. */
struct service {
  /** A unique name of the service. */
  const char* name;

  /** A human-readable description of the service. */
  const char* description;

  /** An interface to the service. */
  struct service_iface* iface;

  /** The internal state of the service. Opaque. */
  struct service_state* state;
};

/** A service interface. */
struct service_iface {
  /**
   * Called after the service loads.
   *
   * @param svc The service definition
   * @return Zero on success, otherwise nonzero
   */
  int (* on_load)(struct service* svc);

  /**
   * Called before the service unloads.
   *
   * @param svc The service definition
   * @return Zero on success, otherwise nonzero
   */
  int (* on_unload)(struct service* svc);

  /**
   * Called after the service starts.
   *
   * @param svc The service definition
   * @return Zero on success, otherwise nonzero
   */
  int (* on_start)(struct service* svc);

  /**
   * Called before the service stops.
   *
   * @param svc The service definition
   * @return Zero on success, otherwise nonzero
   */
  int (* on_stop)(struct service* svc);

  /**
   * Look up a service procedure.
   *
   * @param svc The service definition
   * @param proc The procedure number
   * @return The service procedure or NULL on failure
   */
  service_proc (* get_proc)(const struct service* svc, int proc);
};

/**
 * Look up a service procedure.
 *
 * @param svc The service definition
 * @param proc The procedure number
 * @return The service procedure or NULL on failure
 */
service_proc service_get_proc(const struct service* svc, int proc);

/**
 * Load a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_load(struct service* svc);

/**
 * Unload a loaded service.
 *
 * It is an error to load it after calling this.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_unload(struct service* svc);

/**
 * Start a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_start(struct service* svc);

/**
 * Stop a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_stop(struct service* svc);

/**
 * Call a service.
 *
 * This is a convenience function meant for infrequent or prototype use. If you
 * need to call the same service procedure many times, consider looking up the
 * procedure yourself with service_get_proc(...) and caching it for later.
 *
 * @param svc The service definition
 * @param proc The function ordinal
 * @param arg1 An immutable argument
 * @param arg2 A mutable argument
 * @return Zero on success, otherwise nonzero
 */
inline static int service_call(struct service* svc, int proc, const void* arg1, void* arg2) {
  // Look up the target procedure
  service_proc sp = service_get_proc(svc, proc);

  if (sp) {
    // Procedure exists (forward return code)
    return sp(svc, arg1, arg2);
  } else {
    // Procedure nonexistent
    return 1;
  }
}

#endif // #ifndef SERVICE_H
