#pragma once

#include <stdint.h>


//GUN
#define BMP_GUN_WIDTH  32
#define BMP_GUN_HEIGHT 32
extern const uint8_t bmp_gun_bits[128];
extern const uint8_t bmp_gun_mask[128];

//FIRE
#define BMP_FIRE_WIDTH  24
#define BMP_FIRE_HEIGHT 20
extern const uint8_t bmp_fire_bits[60];

//IMP
#define BMP_IMP_WIDTH  32
#define BMP_IMP_HEIGHT 32
#define BMP_IMP_COUNT  5
extern const uint8_t bmp_imp_bits[640];
extern const uint8_t bmp_imp_mask[640];

//FIREBALL
#define BMP_FIREBALL_WIDTH  16
#define BMP_FIREBALL_HEIGHT 16
extern const uint8_t bmp_fireball_bits[32];
extern const uint8_t bmp_fireball_mask[32];

//ITEMS
#define BMP_ITEMS_WIDTH  16
#define BMP_ITEMS_HEIGHT 16
#define BMP_ITEMS_COUNT  2
extern const uint8_t bmp_items_bits[64];
extern const uint8_t bmp_items_mask[64];

// Gradient for lighting.
// Note: Width and height are in bytes
#define GRADIENT_WIDTH  2
#define GRADIENT_HEIGHT 8
#define GRADIENT_COUNT  8
#define GRADIENT_WHITE  7
#define GRADIENT_BLACK  0
extern const uint8_t gradient[128];
