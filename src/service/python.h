/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_PYTHON_H
#define SERVICE_PYTHON_H

/** A Python service procedure. */
enum service_python_proc {
  service_python_proc_hello,
};

/** The Python service. */
extern struct service* const SERVICE_PYTHON;

#endif // #ifndef SERVICE_PYTHON_H
