#pragma once

#include <stdint.h>

#include "os_io.h"
#include "parser.h"

#include "apdu/apdu.h"
#include "apdu/sw.h"

#include "handler/get_version.h"
#include "handler/get_app_name.h"
#include "handler/get_input.h"

/**
 * Dispatch APDU command received to the right handler.
 *
 * @param[in] cmd
 *   Structured APDU command (CLA, INS, P1, P2, Lc, Command data).
 *
 * @return zero or positive integer if success, negative integer otherwise.
 *
 */
int apdu_dispatcher(const command_t *cmd);

/**
 * Handle APDU command received and send back APDU response using handlers.
 */
void handle_apdu();
