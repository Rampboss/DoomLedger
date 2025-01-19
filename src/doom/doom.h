#pragma once

#include <stdio.h>

// DOOM
#include "constants.h"
#include "doom/level.h"
#include "doom/sprites.h"
#include "doom/entities.h"
#include "doom/types.h"
#include "doom/display.h"
#include "math/math-trigo.h"
#include "ui/bagl_doom.h"

//SDK
#include "ux.h"
#include "os_io_seproxyhal.h"


/**
 * Structure for general doom settings
 */
typedef struct general_doom_ctx {
    uint8_t scene;
    bool exit_scene;
    bool invert_screen;
    uint8_t flash_screen;
    bool game_initialised;
} general_doom_ctx;

/**
 * Structure for game's entities (I.E player, Enemies, fireball)
 */
typedef struct entities_doom_ctx {
    Player player;
    Entity entity[MAX_ENTITIES];
    uint8_t num_entities;
} entities_doom_ctx;

/**
 * Struct to handle input of the game
*/
typedef struct doom_input {
    bool fired;
    bool up;
    bool down;
    bool left;
    bool right;
} doom_input_ctx;

/**
 * Structure to store global values needed for each frame.
 */
typedef struct L_doom_ctx {
    bool walkSoundToggle;
    uint8_t gun_pos;
    double rot_speed;
    double old_dir_x;
    double old_plane_x;
    double view_height;
    double jogging;
    uint8_t fade;
    bool gun_fired;
    double delta;
    unsigned long lastFrameTime;
} L_doom_ctx;

/**
 * Structure for global doom ctx
 */
typedef struct global_doom_ctx {
    L_doom_ctx L_doom_ctx;
    general_doom_ctx G_doom_ctx;
    entities_doom_ctx E_doom_ctx;
    doom_input_ctx I_doom_ctx;
} global_doom_ctx;

// game context
extern global_doom_ctx G_doom;

#define player G_doom.E_doom_ctx.player
#define delta G_doom.L_doom_ctx.delta
#define lastFrameTime G_doom.L_doom_ctx.lastFrameTime

/**
 * @brief Resets the input to avoid counting it twice.
 */
void reset_input();

/**
 * @brief Initializes the game and global context.
 * 
 */
void initDoom();

/**
 * @brief Called each frame, takes into account inputs to move/fire the player.
*/
void loopGamePlay();

/**
 * @brief Called each frame, renders the game after moving entities.
*/
void render_doom();


/**
 * @brief Called each times Player shoots at enemies, applies damage if touched.
*/
void fire();

/**
 * @brief Initializes the level from the provided static map.
 * 
 * @param level The static map data used to initialize the level.
 */
void initializeLevel(const uint8_t level[]);

/**
 * @brief Gets a block from the provided static map at the given coordinates.
 * 
 * 
 * @param level The static map data.
 * @param x The x-coordinate of the block in the map.
 * @param y The y-coordinate of the block in the map.
 * @return The block at the specified coordinates.
 */
uint8_t getBlockAt(const uint8_t level[], uint8_t x, uint8_t y);

/**
 * @brief Translates a sprite's position relative to the camera view.
 * 
 * 
 * @param pos The sprite's coordinates in the world space.
 * @return The translated coordinates relative to the camera view.
 */
Coords translateIntoView(Coords *pos);

/**
 * @brief Enables jumping to the intro scene when the player dies by pressing space.
 * 
 * @param target_scene The scene to transition to when the player dies.
 */
void jumpTo(uint8_t target_scene);

/**
 * @brief Sorts entities based on their distance (from closest to furthest).
 * 
 */
void sortEntities();

/**
 * @brief Updates all entities based on their states and the provided static level.
 * 
 * 
 * @param level The static level data used to update the entities.
 */
void updateEntities(const uint8_t level[]);

/**
 * @brief Updates the position of an entity (e.g., enemies, player) by checking for collisions.
 * 
 * 
 * @param level The static map data representing the level.
 * @param pos The current position of the entity to be updated.
 * @param relative_x The relative movement in the x-direction.
 * @param relative_y The relative movement in the y-direction.
 * @param only_walls If true, only wall collisions are checked; if false, all collisions are checked.
 * 
 * @return The UID of the collided entity if any, else UID_NULL.
 */
UID updatePosition(const uint8_t level[],
                   Coords *pos,
                   double relative_x,
                   double relative_y,
                   bool only_walls);

/**
 * @brief Checks for collisions of an entity (e.g., enemies, player).
 * 
 * 
 * @param level The static map data representing the level.
 * @param pos The current position of the entity to be checked for collisions.
 * @param relative_x The relative movement in the x-direction.
 * @param relative_y The relative movement in the y-direction.
 * @param only_walls If true, only wall collisions are checked; if false, all collisions are checked.
 * 
 * @return The UID of the collided entity if any, else UID_NULL.
 */
UID detectCollision(const uint8_t level[],
                    Coords *pos,
                    double relative_x,
                    double relative_y,
                    bool only_walls);

/**
 * @brief Deletes an entity based on its UID.
 * 
 * @param uid UID of the entity to be removed.
 */
void removeEntity(UID uid);

/**
 * @brief Spawns a fireball at the provided coordinates, moving towards the player.
 * 
 * 
 * @param x The x-coordinate to spawn the fireball.
 * @param y The y-coordinate to spawn the fireball.
 */
void spawnFireball(double x, double y);

/**
 * @brief Spawns an entity at the specified coordinates.
 * 
 * 
 * @param type The Etype of the entity to spawn (e.g., enemy, item, etc.).
 * @param x The x-coordinate to spawn the entity at.
 * @param y The y-coordinate to spawn the entity at.
 */
void spawnEntity(uint8_t type, uint8_t x, uint8_t y);

/**
 * @brief Checks if the given UID is already linked to an existing entity.
 * 
 * 
 * @param uid The UID to check.
 * @return True if the UID is linked to an entity, false otherwise.
 */
bool isSpawned(UID uid);

// Rendering
/**
 * @brief Renders the gun based on the speed of the player and the position the gun should have.
 * 
 * @param gun_pos The position of the gun in the player's view.
 * @param amount_jogging The speed the player has, affecting the gun's rendering.
 */
void renderGun(uint8_t gun_pos, double amount_jogging);

/**
 * @brief Renders entities based on the view height of the player (e.g., above the ground when alive, 
 * on the ground when dead).
 * 
 * @param view_height The height of the player's view, which affects how entities are rendered.
 */
void renderEntities(double view_height);

/**
 * @brief Renders walls based on the view height of the player (e.g., above the ground when alive, 
 * on the ground when dead) and the provided static map.
 * 
 * @param level The static map data representing the level.
 * @param view_height The height of the player's view, which affects how the walls are rendered.
 */
void renderMap(const uint8_t level[], double view_height);