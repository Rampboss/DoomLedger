#pragma once
#include <string.h>
#include <stdbool.h>

#include "ux.h"
#include "os_utils.h"

#include "types.h"
#include "globals.h"
#include "ui/menu.h"
#include "math/math-trigo.h"
#include "ui/bagl_extension.h"
#include "doom/doom.h"

/**
 * Array of colors for bitmap
 * Only gray scale supported
 */
extern unsigned int DOOM_COLORS[2];

/**
 * bitmaps to render game
 */
extern unsigned char DOOM_BITMAP1[DOOM_BITMAP_LEN];
extern unsigned char DOOM_BITMAP2[DOOM_BITMAP_LEN];
extern unsigned char DOOM_BITMAP3[DOOM_BITMAP_LEN];
extern unsigned char DOOM_BITMAP4[DOOM_BITMAP_LEN];

/**
 * Zbuffer to render depth (Z-axis) with the 2D engine
 */
extern uint8_t zbuffer[ZBUFFER_SIZE];

/**
 *  BAGL component to render game with custom BAGL extension
 */
extern bagl_icon_details_t DOOM_BUFFER1;
extern bagl_icon_details_t DOOM_BUFFER2;
extern bagl_icon_details_t DOOM_BUFFER3;
extern bagl_icon_details_t DOOM_BUFFER4;

extern char health[30];
extern char keys[30];
extern char entities[30];


/**
 * @brief Called at each step of the infinite game loop to redraw the flow.
 * 
 */
void ui_dynamic_flow();

/**
 * @brief Initializes the game variables and starts the game.
 * 
 */
void ui_init_game_flow();
