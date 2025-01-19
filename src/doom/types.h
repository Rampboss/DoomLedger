#pragma once

#include <stdint.h>
#include <math.h>

//DOOM
#include "constants.h"
#include "doom/level.h"
#include "math/math-sqrt.h"

//LEDGER
#include "os_pic.h"

#define UID_null  0

// Entity types (legend applies to level.h)
#define E_FLOOR             0x0   // . (also null)
#define E_WALL              0xF   // #
#define E_PLAYER            0x1   // P
#define E_ENEMY             0x2   // E
#define E_DOOR              0x4   // D
#define E_LOCKEDDOOR        0x5   // L
#define E_EXIT              0x7   // X
// collectable entities >= 0x8
#define E_MEDIKIT           0x8   // M
#define E_KEY               0x9   // K
#define E_FIREBALL          0xA   // not in map

/// UID for entities
typedef uint16_t UID;

/**
 * Entity type
*/
typedef uint8_t  EType;

/**
 * Structure to handle 2D coordinate of entities & walls
*/
typedef struct Coords {
  double x;
  double y;
} Coords;

/**
 * @brief Creates a unique identifier (UID) based on type and coordinates.
 *
 * @param type The Etype of the entity.
 * @param x The x-coordinate value.
 * @param y The y-coordinate value.
 * @return The computed UID.
 */
UID create_uid(EType type, uint8_t x, uint8_t y);

/**
 * @brief Extracts the type component from a UID.
 *
 * @param uid The UID from which to extract the type.
 * @return The `Etype` component of the UID.
 */
EType uid_get_type(UID uid);

/**
 * @brief Creates a `Coords` structure with the specified x and y values.
 *
 * @param x The x-coordinate value.
 * @param y The y-coordinate value.
 * @return A `Coords` structure initialized with the provided x and y values.
 */
Coords create_coords(double x, double y);

/**
 * @brief Updates the x and y values of a `Coords` structure.
 *
 * @param c A pointer to the `Coords` structure to be updated.
 * @param x The new x-coordinate value.
 * @param y The new y-coordinate value.
 */
void set_coords(Coords *c, double x, double y);

/**
 * @brief Computes the distance between two `Coords` structures with a scaling factor 
 * (`DISTANCE_MULTIPLIER`)
 * 
 * @param a A pointer to the first `Coords` structure.
 * @param b A pointer to the second `Coords` structure.
 * @return The scaled Euclidean distance between the two coordinates
 */
float coords_distance(Coords* a, Coords* b);