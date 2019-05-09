/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_FACE_H
#define SERVICE_FACE_H

/** A face service procedure. */
enum service_face_proc {
  service_face_proc_hello,
};

/** The face service. */
extern struct service* const SERVICE_FACE;

#endif // #ifndef SERVICE_FACE_H
