#pragma once

#include "io.h"
#include "parser.h"

#include "apdu/sw.h"
#include "apdu/apdu.h"

#include "doom/doom.h"

/**
 * @brief Parses Doom input command data to retrieve the player's inputs.
 *
 * @param[in] cmd
 *   Structured APDU command (CLA, INS, P1, P2, Lc, Command data).
 *
 */
void handler_doom_input(const command_t *cmd);

/**
 * @brief Handles Doom command.
 *
 * @return zero or positive integer if success, negative integer otherwise.
 *
 */
int handler_doom_command(const command_t *cmd);