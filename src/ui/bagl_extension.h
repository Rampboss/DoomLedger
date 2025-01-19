#pragma once

#include <string.h>

#include "ux.h"
#include "os_utils.h"

#include "constants.h"

/**
 * @brief Structure to Displays two icons and a bold text. (used in menu)
 */
typedef struct ux_layout_ppb_params_s {
    const bagl_icon_details_t *icon1;
    const bagl_icon_details_t *icon2;
    const char                *line1;
} ux_layout_ppb_params_t;

/**
 * @brief Custom BAGL layout similar to the PB layout.
 * 
 * This layout is used to display a large image, split into two icons, providing 
 * a custom interface design for the user.
 * 
 * @param stack_slot The stack slot to initialize for the layout.
 */
void ux_layout_ppb_init(unsigned int stack_slot);

/**
 * @brief Structure to display four icons for rendering an image in full screen, 
 * along with the HUD for player health, entities, and collected keys.
 *
 */
typedef struct ux_layout_doom_params_s {
    const bagl_icon_details_t *icon1;
    const bagl_icon_details_t *icon2;
    const bagl_icon_details_t *icon3;
    const bagl_icon_details_t *icon4;
    const char * health;
    const char * keys;
    const char * entities;

} ux_layout_doom_params_t;

/**
 * @brief Custom BAGL layout to render an image in full screen.
 * 
 * Due to the limited size of the G_io_seproxyhal_spi_buffer, a wide screen image 
 * is rendered using four BAGL icon elements, arranged to display the image across 
 * the screen.
 * 
 * @param stack_slot The stack slot to initialize for the layout.
 */
void ux_layout_doom_init(unsigned int stack_slot);