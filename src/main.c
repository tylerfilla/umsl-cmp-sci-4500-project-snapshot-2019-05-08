/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <unistd.h>

#include "service/console.h"
#include "service/face.h"
#include "service/monitor.h"
#include "service/python.h"
#include "service/speech.h"

#include "service.h"

int main() {
  // Test ALL the services!

  service_load(SERVICE_CONSOLE);
  service_load(SERVICE_FACE);
  service_load(SERVICE_MONITOR);
  service_load(SERVICE_PYTHON);
  service_load(SERVICE_SPEECH);

  service_start(SERVICE_CONSOLE);
  service_start(SERVICE_FACE);
  service_start(SERVICE_MONITOR);
  service_start(SERVICE_PYTHON);
  service_start(SERVICE_SPEECH);

  service_stop(SERVICE_SPEECH);
  service_stop(SERVICE_PYTHON);
  service_stop(SERVICE_MONITOR);
  service_stop(SERVICE_FACE);
  service_stop(SERVICE_CONSOLE);

  service_unload(SERVICE_SPEECH);
  service_unload(SERVICE_PYTHON);
  service_unload(SERVICE_MONITOR);
  service_unload(SERVICE_FACE);
  service_unload(SERVICE_CONSOLE);
}
