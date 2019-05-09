/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_SPEECH_H
#define SERVICE_SPEECH_H

/** A speech service procedure. */
enum service_speech_proc {
  service_speech_proc_hello,
};

/** The speech service. */
extern struct service* const SERVICE_SPEECH;

#endif // #ifndef SERVICE_SPEECH_H
