#pragma once

/**
 * Length of APPNAME variable in the Makefile.
 */
#define APPNAME_LEN (sizeof(APPNAME) - 1)

/**
 * Maximum length of MAJOR_VERSION || MINOR_VERSION || PATCH_VERSION.
 */
#define APPVERSION_LEN 3

/**
 * Maximum length of application name.
 */
#define MAX_APPNAME_LEN 64

/**
 * Desired time per frame in ms (66.666666 is ~15 fps)
 */
#define FRAME_TIME 66.666666

/**
 * Higher values will result in lower horizontal resolution when rasterize and lower process
 * and memory usage Lower will require more process and memory, but looks nicer
 */
#define RES_DIVIDER 1

/**
 * Zbuffer resolution divider. We sacrifice resolution to save memory
 */
#define Z_RES_DIVIDER 2

/**
 * Distances are stored as uint8_t, multiplying the distance we can obtain more precision
 * taking care of keep numbers inside the type range. Max is 256 / MAX_RENDER_DEPTH
 */
#define DISTANCE_MULTIPLIER 20

/**
 * Maximum depth to render on screen in player view
 */
#define MAX_RENDER_DEPTH 12

/**
 * Maximum depth to render in the player view
 */
#define MAX_SPRITE_DEPTH 8

/**
 * Size of the ZBUFFER which is responsible of the depth (Z-axis) for the rendering process
 */
#define ZBUFFER_SIZE (BAGL_WIDTH / Z_RES_DIVIDER)

/**
 * Scenes are defined by a number, should change to an enum
 */
#define INTRO     0
#define GAME_PLAY 1

/**
 * Default Height of the gun, used to make animation on start or when shoting
 */
#define GUN_TARGET_POS 18

/**
 * Default Height of the gun when player has fired
 */
#define GUN_SHOT_POS (GUN_TARGET_POS + 4)

/**
 * Rotation speed for the player, used when right and left input are hit
 */
#define ROT_SPEED 0.12

/**
 * Default move speed of the player, used when up and down input are hit
 */
#define MOV_SPEED 0.2

/**
 * Invert of the move speed, useful to compute the jogging speed of the player
 * and make running animation
 */
#define MOV_SPEED_INV (1 / MOV_SPEED)

/**
 * Jogging speed over time to make running animation
 */
#define JOGGING_SPEED 0.005

/**
 * Movement speed for enemies entities over time
 */
#define ENEMY_SPEED 0.002

/**
 * Fireball speed over time
 */
#define FIREBALL_SPEED 0.2

/**
 * Num of angles per PI
 */
#define FIREBALL_ANGLES 45

/**
 * Max num of active entities on the screen
 */
#define MAX_ENTITIES 10

/**
 * Distance for entity spawning
 */
#define MAX_ENTITY_DISTANCE 200

/**
 * Distance when ennemy enter the alert state
 * upon detecting the player
 */
#define MAX_ENEMY_VIEW 80

/**
 * Distance for collision detection between item and player
 */
#define ITEM_COLLIDER_DIST 6

/**
 * Distance for collision detection between enemy and player
 */
#define ENEMY_COLLIDER_DIST 14

/**
 * Distance for collision detection between fireball and enemy
 */
#define FIREBALL_COLLIDER_DIST 2

/**
 * Distance to check if ennemy melee attack can reach player
 */
#define ENEMY_MELEE_DIST 16

/**
 * Suqare distance for collision between player and walls
*/
#define WALL_COLLIDER_DIST 0.2

/**
 * Enemy melee attack damage dealt to player when hit
*/
#define ENEMY_MELEE_DAMAGE  8

/**
 * Enemy fireball attack damage dealt to player when hit
*/
#define ENEMY_FIREBALL_DAMAGE 15

/**
 * Player Maximum gun damage dealt to enemies
 * Closer the enemy is, higher the dommage is
*/
#define GUN_MAX_DAMAGE 25

/**
 * Screen half width depends of the bagl lib and target device
*/
#define HALF_WIDTH    (BAGL_WIDTH / 2)

/**
 * Screen half height depends of the bagl lib and target device
*/
#define HALF_HEIGHT   (BAGL_HEIGHT / 2)

/**
 * Height to render the player view and left space to render stats
*/
#define RENDER_HEIGHT (BAGL_HEIGHT - 12)

/**
 * Their is 4 bitmap to render doom game. 
 * The root cause is the size of the seproxyhal buffer.
 * Refer to the bagl_extention where everything is explain.  
 * for now the number of bitmap will always be 4
 * TODO: enable handling more bitmap with this variable,
*/
#define DOOM_NUMBER_BITMAP 4

/**
 * Game bitmap width
*/
#define DOOM_BITMAP_WIDTH (128 / DOOM_NUMBER_BITMAP)

/**
 * Bitmap bit per pixel, only grayscale is supported for now (value of 1)
*/
#define DOOM_BITMAP_BPP   1

/**
 * DOOM bitmap is a array which the size is compute from the equation under.
 * Notice that bitmap have a height equals to render height, 
 * because bitmap are only used to render the player view.
 * Stats are render below by the other BAGL component
*/
#define DOOM_BITMAP_LEN   (DOOM_BITMAP_WIDTH * (RENDER_HEIGHT) / 8 * DOOM_BITMAP_BPP)