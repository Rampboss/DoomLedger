#pragma once

#include "os.h"
#include "ux.h"

#include "globals.h"
#include "bagl_extension.h"
#include "bagl_doom.h"

/**
 * Show main menu (DOOM ready screen, level selection, about, quit).
 */
void ui_menu_main(void);

/**
 * Show about submenu (copyright and project info, date).
 */
void ui_menu_about(void);

/**
 * Show level1 submenu (level1 game, quit).
 */
void ui_menu_level1(void);
