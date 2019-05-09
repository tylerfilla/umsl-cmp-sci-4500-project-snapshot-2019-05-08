/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_MONITOR_H
#define SERVICE_MONITOR_H

/** A monitor service procedure. */
enum service_monitor_proc {
  service_monitor_proc_hello,
};

/** The monitor service. */
extern struct service* const SERVICE_MONITOR;

#endif // #ifndef SERVICE_MONITOR_H
