
#include "doom/doom.h"

// Useful macros
#define swap(a, b)          \
    do {                    \
        typeof(a) temp = a; \
        a = b;              \
        b = temp;           \
    } while (0)
#define sign(a, b) (double) (a > b ? 1 : (b > a ? -1 : 0))

global_doom_ctx G_doom;


void render_doom() {
    updateEntities(sto_level_1);
    if (G_doom.L_doom_ctx.gun_pos > GUN_TARGET_POS) {
        // Right after fire
        G_doom.L_doom_ctx.gun_pos -= 1;
    } else if (G_doom.L_doom_ctx.gun_pos < GUN_TARGET_POS) {
        // Showing up
        G_doom.L_doom_ctx.gun_pos += 2;
    }
    // // Render stuff
    renderMap(sto_level_1, G_doom.L_doom_ctx.view_height);
    renderEntities(G_doom.L_doom_ctx.view_height);
    renderGun(G_doom.L_doom_ctx.gun_pos, G_doom.L_doom_ctx.jogging);
    
  
    // // Fade in effect
    if (G_doom.L_doom_ctx.fade > 0) {
        fadeScreen(G_doom.L_doom_ctx.fade, 0);
        G_doom.L_doom_ctx.fade--;

    }

    // flash screen
    if (G_doom.G_doom_ctx.flash_screen > 0) {
        G_doom.G_doom_ctx.invert_screen = !G_doom.G_doom_ctx.invert_screen;
        G_doom.G_doom_ctx.flash_screen--;
        
    } else if (G_doom.G_doom_ctx.invert_screen) {
        G_doom.G_doom_ctx.invert_screen = 0;
    }
}

void loopGamePlay() {
    // If the player is alive

    fps();

    if (player.health > 0) {
        // Player speed
        if (G_doom.I_doom_ctx.up) {
            G_doom.I_doom_ctx.up = false;
            player.velocity += (double) (MOV_SPEED - player.velocity) * .4;
        } else if (G_doom.I_doom_ctx.down) {
            G_doom.I_doom_ctx.down = false;
            player.velocity += (double) (-MOV_SPEED - player.velocity) * .4;
        } else {
            player.velocity *= .5;
        }

        G_doom.L_doom_ctx.jogging = fabs(player.velocity) * MOV_SPEED_INV;

        // // Player rotation
        if (G_doom.I_doom_ctx.right) {
            G_doom.I_doom_ctx.right = false;
            G_doom.L_doom_ctx.rot_speed = ROT_SPEED * delta;
            G_doom.L_doom_ctx.old_dir_x = player.dir.x;
            player.dir.x = player.dir.x * cosine(-G_doom.L_doom_ctx.rot_speed) -
                           player.dir.y * sine(-G_doom.L_doom_ctx.rot_speed);
            player.dir.y = G_doom.L_doom_ctx.old_dir_x * sine(-G_doom.L_doom_ctx.rot_speed) +
                           player.dir.y * cosine(-G_doom.L_doom_ctx.rot_speed);
            G_doom.L_doom_ctx.old_plane_x = player.plane.x;
            player.plane.x = player.plane.x * cosine(-G_doom.L_doom_ctx.rot_speed) -
                             player.plane.y * sine(-G_doom.L_doom_ctx.rot_speed);
            player.plane.y = G_doom.L_doom_ctx.old_plane_x * sine(-G_doom.L_doom_ctx.rot_speed) +
                             player.plane.y * cosine(-G_doom.L_doom_ctx.rot_speed);
        } else if (G_doom.I_doom_ctx.left) {
            G_doom.I_doom_ctx.left = false;
            G_doom.L_doom_ctx.rot_speed = ROT_SPEED * delta;
            G_doom.L_doom_ctx.old_dir_x = player.dir.x;
            player.dir.x = player.dir.x * cosine(G_doom.L_doom_ctx.rot_speed) -
                           player.dir.y * sine(G_doom.L_doom_ctx.rot_speed);
            player.dir.y = G_doom.L_doom_ctx.old_dir_x * sine(G_doom.L_doom_ctx.rot_speed) +
                           player.dir.y * cosine(G_doom.L_doom_ctx.rot_speed);
            G_doom.L_doom_ctx.old_plane_x = player.plane.x;
            player.plane.x = player.plane.x * cosine(G_doom.L_doom_ctx.rot_speed) -
                             player.plane.y * sine(G_doom.L_doom_ctx.rot_speed);
            player.plane.y = G_doom.L_doom_ctx.old_plane_x * sine(G_doom.L_doom_ctx.rot_speed) +
                             player.plane.y * cosine(G_doom.L_doom_ctx.rot_speed);
        }

        G_doom.L_doom_ctx.view_height =
            fabs(sine(G_io_app.ms * JOGGING_SPEED)) * 6 * G_doom.L_doom_ctx.jogging;

        // Update gun
        if (G_doom.L_doom_ctx.gun_pos > GUN_TARGET_POS) {
            // Right after fire
            G_doom.L_doom_ctx.gun_pos -= 1;
        } else if (G_doom.L_doom_ctx.gun_pos < GUN_TARGET_POS) {
            // Showing up
            G_doom.L_doom_ctx.gun_pos += 2;
        } else if (!G_doom.L_doom_ctx.gun_fired && G_doom.I_doom_ctx.fired) {
            // ready to fire and fire pressed
            G_doom.I_doom_ctx.fired = false;
            G_doom.L_doom_ctx.gun_pos = GUN_SHOT_POS;
            G_doom.L_doom_ctx.gun_fired = true;
            fire();
        } else if (G_doom.L_doom_ctx.gun_fired) {
            // just fired and restored position
            G_doom.L_doom_ctx.gun_fired = false;
        }
    } else {
        // The player is dead
        if (G_doom.L_doom_ctx.view_height > -10)
            G_doom.L_doom_ctx.view_height--;
        else if (G_doom.I_doom_ctx.fired)
            jumpTo(INTRO);

        if (G_doom.L_doom_ctx.gun_pos > 1) G_doom.L_doom_ctx.gun_pos -= 2;
    }

    // // Player movement
    if (fabs(player.velocity) > 0.003) {
        updatePosition(sto_level_1,
                       &(player.pos),
                       player.dir.x * player.velocity * delta,
                       player.dir.y * player.velocity * delta,
                       false);
    } else {
        player.velocity = 0.0;
    }
    
}


void reset_input() {
    G_doom.I_doom_ctx.down = false;
    G_doom.I_doom_ctx.up = false;
    G_doom.I_doom_ctx.left = false;
    G_doom.I_doom_ctx.right = false;
    G_doom.I_doom_ctx.fired = false;
}

uint8_t getBlockAt(const uint8_t level[], uint8_t x, uint8_t y) {
    if (x < 0 || x >= LEVEL_WIDTH || y < 0 || y >= LEVEL_HEIGHT) {
        return E_FLOOR;
    }

    // y is read in inverse order
    return level[((LEVEL_HEIGHT - 1 - y) * LEVEL_WIDTH + x) / 2] >>
               (!(x % 2) * 4)  // displace part of wanted bits
           & 0b1111;           // mask wanted bits
}

Coords translateIntoView(Coords *pos) {
    // translate sprite position to relative to camera
    double sprite_x = pos->x - player.pos.x;
    double sprite_y = pos->y - player.pos.y;

    // required for correct matrix multiplication
    double inv_det = 1.0 / (player.plane.x * player.dir.y - player.dir.x * player.plane.y);
    double transform_x = inv_det * (player.dir.y * sprite_x - player.dir.x * sprite_y);
    double transform_y =
        inv_det * (-player.plane.y * sprite_x + player.plane.x * sprite_y);  // Z in screen
    Coords coords = {transform_x, transform_y};
    return coords;
}

// Jump to another scene
void jumpTo(uint8_t target_scene) {
    G_doom.G_doom_ctx.scene = target_scene;
    G_doom.G_doom_ctx.exit_scene = true;
    G_doom.G_doom_ctx.game_initialised = false;
}

// Finds the player in the map
void initializeLevel(const uint8_t level[]) {
    for (uint8_t y = LEVEL_HEIGHT - 1; y >= 0; y--) {
        for (uint8_t x = 0; x < LEVEL_WIDTH; x++) {
            uint8_t block = getBlockAt(level, x, y);

            if (block == E_PLAYER) {
                set_player(&player, x, y);
                return;
            }
        }
    }
}

bool isSpawned(UID uid) {
    for (uint8_t i = 0; i < G_doom.E_doom_ctx.num_entities; i++) {
        if (G_doom.E_doom_ctx.entity[i].uid == uid) return true;
    }

    return false;
}

void spawnEntity(uint8_t type, uint8_t x, uint8_t y) {
    // Limit the number of spawned entities
    if (G_doom.E_doom_ctx.num_entities >= MAX_ENTITIES) {
        return;
    }

    switch (type) {
        case E_ENEMY:
            G_doom.E_doom_ctx.entity[G_doom.E_doom_ctx.num_entities] = create_enemy(x, y);
            G_doom.E_doom_ctx.num_entities++;
            break;

        case E_KEY:
            G_doom.E_doom_ctx.entity[G_doom.E_doom_ctx.num_entities] = create_key(x, y);
            G_doom.E_doom_ctx.num_entities++;
            break;

        case E_MEDIKIT:
            G_doom.E_doom_ctx.entity[G_doom.E_doom_ctx.num_entities] = create_medikit(x, y);
            G_doom.E_doom_ctx.num_entities++;
            break;
    }
}

void spawnFireball(double x, double y) {
    // Limit the number of spawned entities
    if (G_doom.E_doom_ctx.num_entities >= MAX_ENTITIES) {
        return;
    }

    UID uid = create_uid(E_FIREBALL, x, y);
    // Remove if already exists, don't throw anything. Not the best, but shouldn't happen too often
    if (isSpawned(uid)) return;

    // Calculate direction. 32 angles
    int16_t dir =
        FIREBALL_ANGLES + atan2_custom(y - player.pos.y, x - player.pos.x) / PI * FIREBALL_ANGLES;
    if (dir < 0) dir += FIREBALL_ANGLES * 2;
    G_doom.E_doom_ctx.entity[G_doom.E_doom_ctx.num_entities] = create_fireball(x, y, 0);
    G_doom.E_doom_ctx.num_entities++;
}

void removeEntity(UID uid) {
    uint8_t i = 0;
    bool found = false;

    while (i < G_doom.E_doom_ctx.num_entities) {
        if (!found && G_doom.E_doom_ctx.entity[i].uid == uid) {
            // todo: doze it
            found = true;
            G_doom.E_doom_ctx.num_entities--;
        }

        // displace entities
        if (found) {
            G_doom.E_doom_ctx.entity[i] = G_doom.E_doom_ctx.entity[i + 1];
        }

        i++;
    }
}

UID detectCollision(const uint8_t level[],
                    Coords *pos,
                    double relative_x,
                    double relative_y,
                    bool only_walls) {
    // Wall collision
    uint8_t round_x = (uint8_t) (pos->x + relative_x);
    uint8_t round_y = (uint8_t) (pos->y + relative_y);
    uint8_t block = getBlockAt(level, round_x, round_y);

    if (block == E_WALL) {
        return create_uid(block, round_x, round_y);
    }

    if (only_walls) {
        return UID_null;
    }

    // Entity collision
    for (uint8_t i = 0; i < G_doom.E_doom_ctx.num_entities; i++) {
        // Don't collide with itself
        if (&(G_doom.E_doom_ctx.entity[i].pos) == pos) {
            continue;
        }

        uint8_t type = uid_get_type(G_doom.E_doom_ctx.entity[i].uid);

        // // Only ALIVE enemy collision
        if (type != E_ENEMY || G_doom.E_doom_ctx.entity[i].state == S_DEAD ||
            G_doom.E_doom_ctx.entity[i].state == S_HIDDEN) {
            continue;
        }

        Coords new_coords = create_coords(G_doom.E_doom_ctx.entity[i].pos.x - relative_x,
                                          G_doom.E_doom_ctx.entity[i].pos.y - relative_y);
        int distance = (int) coords_distance(pos, &new_coords);

        // Check distance and if it's getting closer
        if (distance < ENEMY_COLLIDER_DIST && distance < G_doom.E_doom_ctx.entity[i].distance) {
            return G_doom.E_doom_ctx.entity[i].uid;
        }
    }

    return UID_null;
}

// Shoot
void fire() {
    for (uint8_t i = 0; i < G_doom.E_doom_ctx.num_entities; i++) {
        // Shoot only ALIVE enemies
        if (uid_get_type(G_doom.E_doom_ctx.entity[i].uid) != E_ENEMY ||
            G_doom.E_doom_ctx.entity[i].state == S_DEAD ||
            G_doom.E_doom_ctx.entity[i].state == S_HIDDEN) {
            continue;
        }

        Coords transform = translateIntoView(&(G_doom.E_doom_ctx.entity[i].pos));
        if (fabs(transform.x) < 20 && transform.y > 0) {
            uint8_t damage = (double) MIN(
                GUN_MAX_DAMAGE,
                GUN_MAX_DAMAGE / (fabs(transform.x) * G_doom.E_doom_ctx.entity[i].distance) / 5);
            if (damage > 0) {
                G_doom.E_doom_ctx.entity[i].health =
                    MAX(0, G_doom.E_doom_ctx.entity[i].health - damage);
                G_doom.E_doom_ctx.entity[i].state = S_HIT;
                G_doom.E_doom_ctx.entity[i].timer = 4;
            }
        }
    }
}

// Update coords if possible. Return the collided uid, if any
UID updatePosition(const uint8_t level[],
                   Coords *pos,
                   double relative_x,
                   double relative_y,
                   bool only_walls) {
    UID collide_x = detectCollision(level, pos, relative_x, 0, only_walls);
    UID collide_y = detectCollision(level, pos, 0, relative_y, only_walls);

    if (!collide_x) pos->x += relative_x;
    if (!collide_y) pos->y += relative_y;

    return collide_x || collide_y || UID_null;
}

void updateEntities(const uint8_t level[]) {
    uint8_t i = 0;
    while (i < G_doom.E_doom_ctx.num_entities) {
        // update distance
        G_doom.E_doom_ctx.entity[i].distance = (int)
            coords_distance(&(player.pos), &(G_doom.E_doom_ctx.entity[i].pos));

        // Run the timer. Works with actual frames.
        // Todo: use delta here. But needs double type and more memory
        if (G_doom.E_doom_ctx.entity[i].timer > 0) G_doom.E_doom_ctx.entity[i].timer--;

        // too far away. put it in doze mode
        if (G_doom.E_doom_ctx.entity[i].distance > MAX_ENTITY_DISTANCE) {
            removeEntity(G_doom.E_doom_ctx.entity[i].uid);
            // don't increase 'i', since current one has been removed
            continue;
        }

        // bypass render if hidden
        if (G_doom.E_doom_ctx.entity[i].state == S_HIDDEN) {
            i++;
            continue;
        }


        uint8_t type = uid_get_type(G_doom.E_doom_ctx.entity[i].uid);

        switch (type) {
            case E_ENEMY: {
                // Enemy "IA"
                if (G_doom.E_doom_ctx.entity[i].health == 0) {
                    if (G_doom.E_doom_ctx.entity[i].state != S_DEAD) {
                        G_doom.E_doom_ctx.entity[i].state = S_DEAD;
                        G_doom.E_doom_ctx.entity[i].timer = 6;
                    }
                } else if (G_doom.E_doom_ctx.entity[i].state == S_HIT) {
                    if (G_doom.E_doom_ctx.entity[i].timer == 0) {
                        // Back to alert state
                        G_doom.E_doom_ctx.entity[i].state = S_ALERT;
                        G_doom.E_doom_ctx.entity[i].timer = 20;  // delay next fireball thrown
                    }
                } else if (G_doom.E_doom_ctx.entity[i].state == S_FIRING) {
                    if (G_doom.E_doom_ctx.entity[i].timer == 0) {
                        // Back to alert state
                        G_doom.E_doom_ctx.entity[i].state = S_ALERT;
                        G_doom.E_doom_ctx.entity[i].timer = 20;  // delay next fireball throwm
                    }
                } else {
                    // ALERT STATE
                    if (G_doom.E_doom_ctx.entity[i].distance > ENEMY_MELEE_DIST &&
                        G_doom.E_doom_ctx.entity[i].distance < MAX_ENEMY_VIEW) {
                        if (G_doom.E_doom_ctx.entity[i].state != S_ALERT) {
                            G_doom.E_doom_ctx.entity[i].state = S_ALERT;
                            G_doom.E_doom_ctx.entity[i].timer = 10;  // used to throw fireballs
                        } else {
                            if (G_doom.E_doom_ctx.entity[i].timer == 0) {
                                // Throw a fireball
                                spawnFireball(G_doom.E_doom_ctx.entity[i].pos.x,
                                              G_doom.E_doom_ctx.entity[i].pos.y);
                                G_doom.E_doom_ctx.entity[i].state = S_FIRING;
                                G_doom.E_doom_ctx.entity[i].timer = 6;
                            } else {
                                // move towards to the player.
                                updatePosition(
                                    level,
                                    &(G_doom.E_doom_ctx.entity[i].pos),
                                    sign(player.pos.x, G_doom.E_doom_ctx.entity[i].pos.x) *
                                        ENEMY_SPEED * 100.0,
                                    sign(player.pos.y, G_doom.E_doom_ctx.entity[i].pos.y) *
                                        ENEMY_SPEED * 100.0,
                                    true);
                            }
                        }
                    } else if (G_doom.E_doom_ctx.entity[i].distance <= ENEMY_MELEE_DIST) {
                        if (G_doom.E_doom_ctx.entity[i].state != S_MELEE) {
                            // Preparing the melee attack
                            G_doom.E_doom_ctx.entity[i].state = S_MELEE;
                            G_doom.E_doom_ctx.entity[i].timer = 10;
                        } else if (G_doom.E_doom_ctx.entity[i].timer == 0) {
                            // Melee attack
                            player.health = MAX(0, player.health - ENEMY_MELEE_DAMAGE);
                            G_doom.E_doom_ctx.entity[i].timer = 14;
                            G_doom.G_doom_ctx.flash_screen = 1;
                        }
                    } else {
                        // stand
                        G_doom.E_doom_ctx.entity[i].state = S_STAND;
                    }
                }
                break;
            }

            case E_FIREBALL: {
                if (G_doom.E_doom_ctx.entity[i].distance < FIREBALL_COLLIDER_DIST) {
                    // Hit the player and disappear
                    player.health = MAX(0, player.health - ENEMY_FIREBALL_DAMAGE);
                    G_doom.G_doom_ctx.flash_screen = 1;
                    removeEntity(G_doom.E_doom_ctx.entity[i].uid);
                    continue;  // continue in the loop
                } else {
                    // Move. Only collide with walls.
                    // Note: using health to store the angle of the movement
                    UID collided = updatePosition(
                        level,
                        &(G_doom.E_doom_ctx.entity[i].pos),
                        cosine((double) G_doom.E_doom_ctx.entity[i].health / FIREBALL_ANGLES * PI) *
                            FIREBALL_SPEED,
                        sine((double) G_doom.E_doom_ctx.entity[i].health / FIREBALL_ANGLES * PI) *
                            FIREBALL_SPEED,
                        true);

                    if (collided) {
                        removeEntity(G_doom.E_doom_ctx.entity[i].uid);
                        continue;  // continue in the entity check loop
                    }
                }
                break;
            }

            case E_MEDIKIT: {
                if (G_doom.E_doom_ctx.entity[i].distance < ITEM_COLLIDER_DIST) {
                    // pickup
                    G_doom.E_doom_ctx.entity[i].state = S_HIDDEN;
                    player.health = MIN(100, player.health + 50);
                    G_doom.G_doom_ctx.flash_screen = 1;
                }
                break;
            }

            case E_KEY: {
                if (G_doom.E_doom_ctx.entity[i].distance < ITEM_COLLIDER_DIST) {
                    // pickup
                    G_doom.E_doom_ctx.entity[i].state = S_HIDDEN;
                    player.keys++;
                    G_doom.G_doom_ctx.flash_screen = 1;
                }
                break;
            }
        }

        i++;
    }
}

// The map raycaster. Based on https://lodev.org/cgtutor/raycasting.html
void renderMap(const uint8_t level[], double view_height) {
    UID last_uid;

    for (uint8_t x = 0; x < BAGL_WIDTH; x += RES_DIVIDER) {
        double camera_x = 2 * (double) x / BAGL_WIDTH - 1;
        double ray_x = player.dir.x + player.plane.x * camera_x;
        double ray_y = player.dir.y + player.plane.y * camera_x;
        uint8_t map_x = (uint8_t) player.pos.x;
        uint8_t map_y = (uint8_t) player.pos.y;
        Coords map_coords = {player.pos.x, player.pos.y};
        double delta_x = fabs(1 / ray_x);
        double delta_y = fabs(1 / ray_y);

        int8_t step_x;
        int8_t step_y;
        double side_x;
        double side_y;

        if (ray_x < 0) {
            step_x = -1;
            side_x = (player.pos.x - map_x) * delta_x;
        } else {
            step_x = 1;
            side_x = (map_x + 1.0 - player.pos.x) * delta_x;
        }

        if (ray_y < 0) {
            step_y = -1;
            side_y = (player.pos.y - map_y) * delta_y;
        } else {
            step_y = 1;
            side_y = (map_y + 1.0 - player.pos.y) * delta_y;
        }

        // Wall detection
        uint8_t depth = 0;
        bool hit = 0;
        bool side;
        while (!hit && depth < MAX_RENDER_DEPTH) {
            if (side_x < side_y) {
                side_x += delta_x;
                map_x += step_x;
                side = 0;
            } else {
                side_y += delta_y;
                map_y += step_y;
                side = 1;
            }

            uint8_t block = getBlockAt(level, map_x, map_y);

            if (block == E_WALL) {
                hit = 1;
            } else {
                // Spawning entities here, as soon they are visible for the
                // player. Not the best place, but would be a very performance
                // cost scan for them in another loop
                if (block == E_ENEMY || (block & 0b00001000) /* all collectable items */) {
                    // Check that it's close to the player
                    if (coords_distance(&(player.pos), &map_coords) < MAX_ENTITY_DISTANCE) {
                        UID uid = create_uid(block, map_x, map_y);
                        if (last_uid != uid && !isSpawned(uid)) {
                            spawnEntity(block, map_x, map_y);
                            last_uid = uid;
                        }
                    }
                }
            }

            depth++;
        }

        if (hit) {
            double distance;

            if (side == 0) {
                distance = fmax(1, (map_x - player.pos.x + (1 - step_x) / 2) / ray_x);
            } else {
                distance = fmax(1, (map_y - player.pos.y + (1 - step_y) / 2) / ray_y);
            }

            // store zbuffer value for the column
            zbuffer[x / Z_RES_DIVIDER] = fmin(distance * DISTANCE_MULTIPLIER, 255);

            // rendered line height
            uint8_t line_height = RENDER_HEIGHT / distance;

            drawVLine(
                x,
                view_height / distance - line_height / 2 + RENDER_HEIGHT / 2,
                view_height / distance + line_height / 2 + RENDER_HEIGHT / 2,
                GRADIENT_COUNT - (int) (distance / MAX_RENDER_DEPTH * GRADIENT_COUNT) - side * 2);
        }
    }
}

// Sort entities from far to close
void sortEntities() {
    uint8_t gap = G_doom.E_doom_ctx.num_entities;
    bool swapped = false;
    while (gap > 1 || swapped) {
        // shrink factor 1.3
        gap = (gap * 10) / 13;
        if (gap == 9 || gap == 10) gap = 11;
        if (gap < 1) gap = 1;
        swapped = false;
        for (uint8_t i = 0; i < G_doom.E_doom_ctx.num_entities - gap; i++) {
            uint8_t j = i + gap;
            if (G_doom.E_doom_ctx.entity[i].distance < G_doom.E_doom_ctx.entity[j].distance) {
                swap(G_doom.E_doom_ctx.entity[i], G_doom.E_doom_ctx.entity[j]);
                swapped = true;
            }
        }
    }
}

void renderEntities(double view_height) {
    sortEntities();

    for (uint8_t i = 0; i < G_doom.E_doom_ctx.num_entities; i++) {
        if (G_doom.E_doom_ctx.entity[i].state == S_HIDDEN) continue;
        Coords transform = translateIntoView(&(G_doom.E_doom_ctx.entity[i].pos));

        // don´t render if behind the player or too far away
        if (transform.y <= 0.3f || transform.y > MAX_SPRITE_DEPTH) {
            continue;
        }

        int16_t sprite_screen_x = HALF_WIDTH * (1.0 + transform.x / transform.y);
        int8_t sprite_screen_y = RENDER_HEIGHT / 2 + view_height / transform.y;
        uint8_t type = uid_get_type(G_doom.E_doom_ctx.entity[i].uid);
        
        // don´t try to render if outside of screen
        // doing this pre-shortcut due int16 -> int8 conversion makes out-of-screen
        // values fit into the screen space
        if (sprite_screen_x < -HALF_WIDTH || sprite_screen_x > BAGL_WIDTH + HALF_WIDTH) {
            continue;
        }

        switch (type) {
            case E_ENEMY: {
                uint8_t sprite;
                if (G_doom.E_doom_ctx.entity[i].state == S_ALERT) {
                    // walking
                    sprite = (int) (G_io_app.ms / 500) % 2;
                } else if (G_doom.E_doom_ctx.entity[i].state == S_FIRING) {
                    // fireball
                    sprite = 2;
                } else if (G_doom.E_doom_ctx.entity[i].state == S_HIT) {
                    // hit
                    sprite = 3;
                } else if (G_doom.E_doom_ctx.entity[i].state == S_MELEE) {
                    // melee attack
                    sprite = G_doom.E_doom_ctx.entity[i].timer > 10 ? 2 : 1;
                } else if (G_doom.E_doom_ctx.entity[i].state == S_DEAD) {
                    // dying
                    sprite = G_doom.E_doom_ctx.entity[i].timer > 0 ? 3 : 4;
                } else {
                    // stand
                    sprite = 0;
                }

      


                drawSprite(sprite_screen_x - BMP_IMP_WIDTH * .5 / transform.y,
                           sprite_screen_y - 8 / transform.y,
                           bmp_imp_bits,
                           bmp_imp_mask,
                           BMP_IMP_WIDTH,
                           BMP_IMP_HEIGHT,
                           sprite,
                           transform.y);
                break;
            }

            case E_FIREBALL: {
                drawSprite(sprite_screen_x - BMP_FIREBALL_WIDTH / 2 / transform.y,
                           sprite_screen_y - BMP_FIREBALL_HEIGHT / 2 / transform.y,
                           bmp_fireball_bits,
                           bmp_fireball_mask,
                           BMP_FIREBALL_WIDTH,
                           BMP_FIREBALL_HEIGHT,
                           0,
                           transform.y);
                break;
            }

            case E_MEDIKIT: {
                drawSprite(sprite_screen_x - BMP_ITEMS_WIDTH / 2 / transform.y,
                           sprite_screen_y + 5 / transform.y,
                           bmp_items_bits,
                           bmp_items_mask,
                           BMP_ITEMS_WIDTH,
                           BMP_ITEMS_HEIGHT,
                           0,
                           transform.y);
                break;
            }

            case E_KEY: {
                drawSprite(sprite_screen_x - BMP_ITEMS_WIDTH / 2 / transform.y,
                           sprite_screen_y + 5 / transform.y,
                           bmp_items_bits,
                           bmp_items_mask,
                           BMP_ITEMS_WIDTH,
                           BMP_ITEMS_HEIGHT,
                           1,
                           transform.y);
                break;
            }
        }
    }
}

void renderGun(uint8_t gun_pos, double amount_jogging) {
    uint8_t x = 48 + (uint8_t) sine((double) G_io_app.ms * JOGGING_SPEED) * 10 * amount_jogging;
    uint8_t y = RENDER_HEIGHT - gun_pos +
                fabs(cosine((double) G_io_app.ms * JOGGING_SPEED)) * 8 * amount_jogging;

    if (gun_pos > GUN_SHOT_POS - 2) {
        // Gun fire
        drawBitmap(x + 6, y - 11, bmp_fire_bits, BMP_FIRE_WIDTH, BMP_FIRE_HEIGHT, 1);
    }

    // Don't draw over the hud!
    uint8_t clip_height = MAX(0, MIN(y + BMP_GUN_HEIGHT, RENDER_HEIGHT) - y);

    // Draw the gun (black mask + actual sprite).
    drawBitmap(x, y, bmp_gun_mask, BMP_GUN_WIDTH, clip_height, 0);
    drawBitmap(x, y, bmp_gun_bits, BMP_GUN_WIDTH, clip_height, 1);
}

void initDoom() {
    // general
    G_doom.G_doom_ctx.scene = GAME_PLAY;
    G_doom.G_doom_ctx.exit_scene = false;
    G_doom.G_doom_ctx.invert_screen = false;
    G_doom.G_doom_ctx.flash_screen = false;
    G_doom.G_doom_ctx.game_initialised = true;

    // game
    // player and entities
    G_doom.E_doom_ctx.num_entities = 0;
    memset(&player, 0, sizeof(Player));
    for (int i = 0; i < MAX_ENTITIES; i++) {
        memset(&G_doom.E_doom_ctx.entity[i], 0, sizeof(Entity));
    }

    memset(&player, 0, sizeof(Player));

    // loop status variable
    G_doom.L_doom_ctx.gun_fired = false;
    G_doom.L_doom_ctx.walkSoundToggle = false;
    G_doom.L_doom_ctx.gun_pos = 0;
    G_doom.L_doom_ctx.fade = GRADIENT_COUNT - 1;
    G_doom.L_doom_ctx.jogging = 0.0;
    G_doom.L_doom_ctx.old_dir_x = 0.0;
    G_doom.L_doom_ctx.old_plane_x = 0.0;
    G_doom.L_doom_ctx.rot_speed = 0.0;
    G_doom.L_doom_ctx.view_height = 0.0;
    delta = 100.0 / FRAME_TIME;
    lastFrameTime = 0;

    // input reset
    reset_input();
    initializeLevel(sto_level_1);
}