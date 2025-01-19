#pragma once

#include <stdbool.h>

#include "doom/types.h"

// Shortcuts
#define create_enemy(x, y)            create_entity(E_ENEMY, x, y, S_STAND, 100)
#define create_medikit(x, y)          create_entity(E_MEDIKIT, x, y, S_STAND, 0)
#define create_key(x, y)              create_entity(E_KEY, x, y, S_STAND, 0)
#define create_fireball(x, y, dir)    create_entity(E_FIREBALL, x, y, S_STAND, dir)

// entity statuses
#define S_STAND               0
#define S_ALERT               1
#define S_FIRING              2
#define S_MELEE               3
#define S_HIT                 4
#define S_DEAD                5
#define S_HIDDEN              6
#define S_OPEN                7
#define S_CLOSE               8

// Struct for player
typedef struct Player { 
  Coords pos;
  Coords dir;
  Coords plane;
  double velocity;
  uint8_t health;
  uint8_t keys;  
} Player;

//Struct for entities (fireball, enemies, items)
typedef struct Entity {
  UID uid;
  Coords pos;
  uint8_t state;
  uint8_t health;     // angle for fireballs
  int distance;
  uint8_t timer;
} Entity;


/**
 * @brief Initializes a `Player` structure with default values.
 * 
 * @param p A pointer to the `Player` structure to be initialized.
 * @param x The x-coordinate of the player's starting position.
 * @param y The y-coordinate of the player's starting position.
 */
void set_player(Player *p, uint8_t x, uint8_t y);

/**
 * @brief Creates and initializes an `Entity` structure.
 *
 *
 * @param type The Etype of the entity.
 * @param x The x-coordinate of the entity's position.
 * @param y The y-coordinate of the entity's position.
 * @param initialState The initial state of the entity.
 * @param initialHealth The initial health value of the entity (angle for fireball)
 * @return A fully initialized `Entity` structure.
 */
Entity create_entity(uint8_t type, uint8_t x,  uint8_t y, uint8_t initialState, uint8_t initialHealth);


