#pragma once
#include <stdint.h>

// Level 
#define LEVEL_WIDTH_BASE    6
#define LEVEL_WIDTH         (1 << LEVEL_WIDTH_BASE)
#define LEVEL_HEIGHT        57
#define LEVEL_SIZE          LEVEL_WIDTH / 2 * LEVEL_HEIGHT
extern const uint8_t sto_level_1[LEVEL_SIZE];
