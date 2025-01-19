#pragma once

#include "io.h"
#include "os_pic.h"

#include "constants.h"
#include "apdu/sw.h"

/**
 * Handler for GET_APP_NAME command. Send APDU response with ASCII
 * encoded name of the application.
 *
 * @see variable APPNAME in Makefile.
 *
 * @return zero or positive integer if success, negative integer otherwise.
 *
 */
int handler_get_app_name(void);
