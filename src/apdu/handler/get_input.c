#include "get_input.h"

int handler_doom_command(const command_t *cmd) {

    switch (cmd->p1) {
        case DOOMIT: // play/resume the game
            ui_init_game_flow();
            break;
        case QUIT: // pause/quit the game
            if (player.health < 1)
                G_doom.G_doom_ctx.game_initialised = false;
            ui_menu_main();
            break;
        case INPUT: // fire & moving inputs
            handler_doom_input(cmd);
            break;
        default:
            break;
    }

    return io_send_sw(SW_OK);
}


void handler_doom_input(const command_t *cmd) {

    for(uint8_t i = 0; i < cmd->lc; i++){
        uint8_t data = (cmd->data[i]);
        switch (data) {
            case FIRE:
                G_doom.I_doom_ctx.fired = true;
                break;
            case UP:
                G_doom.I_doom_ctx.up = true;
                break;
            case DOWN:
                G_doom.I_doom_ctx.down = true;
                break;
            case LEFT:
                G_doom.I_doom_ctx.left = true;
                break;
            case RIGHT:
                G_doom.I_doom_ctx.right = true;
                break;
            default:
                break;
        }
    }
       
}
