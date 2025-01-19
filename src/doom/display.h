#pragma once

#include <stdbool.h>  // bool
#include <stdint.h>

//LEDGER SDK
#include "ux.h"
#include "constants.h"

//DOOM
#include "doom/sprites.h"
#include "ui/bagl_doom.h"

// This is slightly faster than bitRead (bits are also read from left to right).
extern uint8_t const bit_mask[8];
#define READ_BIT(b, n) ((b & bit_mask[n]) ? 1 : 0)

/**
 * @brief Gets the pixel's index in the bitmap.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The index in one of the bitmaps used to render the game.
 */
#define GET_PIXEL_INDEX(x,y) (DOOM_NUMBER_BITMAP * y + (x % DOOM_BITMAP_WIDTH) / 8)

/**
 * @brief Selects the bitmap based on the x position.
 * 
 * @param x The x-coordinate of the pixel on the screen.
 * @return The bitmap buffer to draw on.
 */
unsigned char * get_bitmap_buffer(uint8_t x);

/**
 * @brief Gets the FPS for the game.
 * 
 * On a Ledger device, this is not really necessary as the actual FPS is 10.
 * This is because the ticker event is assumed to occur every 100ms, and this value is hard-coded.
 * Therefore, every loop happens every 100ms. However, it is possible for a loop to take longer to process the game state.
 * Although we can't really calculate it since there is no clock accessible from the Ledger SDK.
 * 
 * @return The FPS of the game.
 */
double getActualFps();

/**
 * @brief Computes the FPS between two frames.
 * 
 * On a Ledger device, the ticker event is assumed to be constant (100ms), and it is a hardcoded value. 
 * Therefore, the delta between two frames is constant and is always 100ms. The SDK does not provide any way to access the device's clock.
 */
void fps();

/**
 * @brief Gradient used for fade effect or rendering distant walls.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param i The intensity of the pixel.
 * @return True if the pixel is ON.
 */
bool getGradientPixel(uint8_t x, uint8_t y, uint8_t i);

/**
 * @brief Fade effect for the loading screen.
 * 
 * @param intensity The intensity of the gradient effect.
 * @param color If false, the screen will fade to black.
 */
void fadeScreen(uint8_t intensity, bool color);

/**
 * @brief Draws a pixel on the screen with the given color.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */
void drawPixel(uint8_t x, uint8_t y, bool color);

/**
 * @brief Draws a vertical line on the screen based on the intensity.
 * 
 * @param x The x-coordinate of the line.
 * @param start_y The y-coordinate where the vertical line starts.
 * @param end_y The y-coordinate where the vertical line ends.
 * @param intensity The intensity of the vertical line pixels.
 */
void drawVLine(uint8_t x, int8_t start_y, int8_t end_y, uint8_t intensity);


/**
 * @brief Draws a sprite (e.g., gun/entities) on the screen.
 *      
 *            X coord
 *       0 +----->
 *         |    
 * Y coord |    #####   ^
 *         |   #######  |
 *         v   ##   ##  | h 
 *             #######  |
 *              #####   v
 *             <----->
 *                w   
 *  
 * @param x The x-coordinate where drawing of the sprite begins.
 * @param y The y-coordinate where drawing of the sprite begins.
 * @param bitmap The bitmap containing the sprite to draw.
 * @param mask The mask to apply on the sprite.
 * @param w The width of the sprite.
 * @param h The height of the sprite.
 * @param sprite The sprite's index in the bitmap.
 * @param start_y The y-coordinate to start drawing the sprite vertically.
 * @param end_y The y-coordinate to end drawing the sprite vertically.
 * @param intensity The intensity of the sprite's pixels.
*/
void drawSprite(int8_t x,
                int8_t y,
                const uint8_t bitmap[],
                const uint8_t mask[],
                int16_t w,
                int16_t h,
                uint8_t sprite,
                double distance);

/**
 * @brief Draws a bitmap (e.g., gun/entities) on the screen.
 *      
 *            X coord
 *       0 +----->
 *         |    
 * Y coord |    #####   ^
 *         |   #######  |
 *         v   ##   ##  | h 
 *             #######  |
 *              #####   v
 *             <----->
 *                w   
 *  
 * @param x The x-coordinate where drawing of the bitmap begins.
 * @param y The y-coordinate where drawing of the bitmap begins.
 * @param bitmap The bitmap to draw.
 * @param w The width of the bitmap.
 * @param h The height of the bitmap.
 * @param color The color of the bitmap.
*/
void drawBitmap(int8_t x,
                int8_t y,
                const uint8_t bitmap[],
                int16_t w,
                int16_t h,
                uint8_t color);
