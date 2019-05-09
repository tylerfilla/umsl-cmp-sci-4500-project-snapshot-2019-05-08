/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_CONSOLE_H
#define SERVICE_CONSOLE_H

/** A console service procedure. */
enum service_console_proc {
  service_console_proc_hello,
};

/** The console service. */
extern struct service* const SERVICE_CONSOLE;

#endif // #ifndef SERVICE_CONSOLE_H
