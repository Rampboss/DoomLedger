#include "ui/bagl_doom.h"

unsigned int DOOM_COLORS[2];

unsigned char DOOM_BITMAP1[DOOM_BITMAP_LEN];
unsigned char DOOM_BITMAP2[DOOM_BITMAP_LEN];
unsigned char DOOM_BITMAP3[DOOM_BITMAP_LEN];
unsigned char DOOM_BITMAP4[DOOM_BITMAP_LEN];
uint8_t zbuffer[ZBUFFER_SIZE];

bagl_icon_details_t DOOM_BUFFER1;
bagl_icon_details_t DOOM_BUFFER2;
bagl_icon_details_t DOOM_BUFFER3;
bagl_icon_details_t DOOM_BUFFER4;

char health[30];
char entities[30];
char keys[30];


/**
 * End step of the loop flow, this is used to loop
*/
UX_STEP_INIT(step_looper, NULL, NULL, { ui_dynamic_flow(); });
UX_FLOW(looper_flow, &step_looper);

/**
 * Render step which used a custom bagl extension to display all the bitmap of the game
 * The timeout is used to avoid user 
*/
 
UX_STEP_TIMEOUT(step_render,
                doom,
                1,
                looper_flow,
                {&DOOM_BUFFER1, &DOOM_BUFFER2, &DOOM_BUFFER3, &DOOM_BUFFER4, health, keys, entities});


void display_next_state() {
    memset(DOOM_BITMAP1, 0, DOOM_BITMAP_LEN);
    memset(DOOM_BITMAP2, 0, DOOM_BITMAP_LEN);
    memset(DOOM_BITMAP3, 0, DOOM_BITMAP_LEN);
    memset(DOOM_BITMAP4, 0, DOOM_BITMAP_LEN);
    loopGamePlay();
    render_doom();
    snprintf(health, 30, "H %d", (int) player.health);
    snprintf(keys, 30, "K %d", (int) player.keys);
    snprintf(entities, 30, "E %d", (int) G_doom.E_doom_ctx.num_entities);
    ux_flow_next();
}

/**
 * Step to get the next state of the game before rendering
*/
UX_STEP_INIT(step_next_state, NULL, NULL, { display_next_state(); });
UX_FLOW(dynamic_flow, &step_next_state, &step_render, FLOW_LOOP);

void ui_dynamic_flow() {
    //enable going back to intro scene when player dies
    if (G_doom.G_doom_ctx.scene == INTRO && G_doom.G_doom_ctx.exit_scene) {
        ui_menu_main();
        return;
    }

    ux_flow_init(0, dynamic_flow, NULL);
}

/**
 * @brief Init one of the game buffer to render with bagl custom layout
 * 
 * @param buffer The Buffer to init.
 * @param bitmap The bitmap of this buffer.
 */
void init_buffer(bagl_icon_details_t *buffer, unsigned char *bitmap) {
    memset(bitmap, 0, DOOM_BITMAP_LEN);
    memset(buffer, 0, sizeof(bagl_icon_details_t));
    buffer->width = DOOM_BITMAP_WIDTH;
    buffer->height = RENDER_HEIGHT;
    buffer->bpp = DOOM_BITMAP_BPP;
    buffer->colors = DOOM_COLORS;
    buffer->bitmap = bitmap;
}

void ui_init_game_flow() {
    if (!G_doom.G_doom_ctx.game_initialised)
    {
        initDoom();
        DOOM_COLORS[0] = 0x00000000;
        DOOM_COLORS[1] = 0x00ffffff;

        init_buffer(&DOOM_BUFFER1, DOOM_BITMAP1);
        init_buffer(&DOOM_BUFFER2, DOOM_BITMAP2);
        init_buffer(&DOOM_BUFFER3, DOOM_BITMAP3);
        init_buffer(&DOOM_BUFFER4, DOOM_BITMAP4);

        memset(zbuffer, 0xFF, ZBUFFER_SIZE);
        memset(health, 0, 30);
        memset(entities, 0, 30);
        memset(keys, 0, 30);
    }
        
    ui_dynamic_flow();
}