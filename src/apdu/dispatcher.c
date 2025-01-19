/*****************************************************************************
 *   Ledger App Boilerplate.
 *   (c) 2020 Ledger SAS.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#include "dispatcher.h"

int apdu_dispatcher(const command_t *cmd) {
    LEDGER_ASSERT(cmd != NULL, "NULL cmd");

    if (cmd->cla != CLA) {
        return io_send_sw(SW_CLA_NOT_SUPPORTED);
    }

    switch (cmd->ins) {
        case GET_VERSION:
            if (cmd->p1 != 0 || cmd->p2 != 0) {
                return io_send_sw(SW_WRONG_P1P2);
            }

            return handler_get_version();
        case GET_APP_NAME:
            if (cmd->p1 != 0 || cmd->p2 != 0) {
                return io_send_sw(SW_WRONG_P1P2);
            }

            return handler_get_app_name();

        case DOOM:
            if (cmd->p1 == 0) {
                return io_send_sw(SW_WRONG_P1P2);
            }

            return handler_doom_command(cmd);
        default:
            return io_send_sw(SW_INS_NOT_SUPPORTED);
    }
}

void handle_apdu() {
    // Length of APDU command received in G_io_apdu_buffer
    int input_len = 0;
    // Structured APDU command
    command_t cmd;

    if ((input_len = io_recv_command()) < 0) {
        PRINTF("=> io_recv_command failure\n");
        return;
    }

    // Parse APDU command from G_io_apdu_buffer
    if (!apdu_parser(&cmd, G_io_apdu_buffer, input_len)) {
        PRINTF("=> /!\\ BAD LENGTH: %.*H\n", input_len, G_io_apdu_buffer);
        io_send_sw(SW_WRONG_DATA_LENGTH);
        return;
    }

    PRINTF("=> CLA=%02X | INS=%02X | P1=%02X | P2=%02X | Lc=%02X | CData=%.*H\n",
           cmd.cla,
           cmd.ins,
           cmd.p1,
           cmd.p2,
           cmd.lc,
           cmd.lc,
           cmd.data);

    // Dispatch structured APDU command to handler
    int ret = apdu_dispatcher(&cmd);
    PRINTF("RET %d", ret);
    if (ret < 0) {
        PRINTF("=> apdu_dispatcher failure\n");
        return;
    }
}