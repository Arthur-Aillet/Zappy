/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** check_command
*/

#include "zappy.h"
#include <string.h>

static int is_valid_opt_gui(size_t i, gui_t *gui,
            client_gui_t *client_gui, common_t *com)
{
    if (strcmp(client_gui->comd, COMMAND_GESTION_CLIENT_GUI[i].comd) == 0) {
        COMMAND_GESTION_CLIENT_GUI[i].handler(gui, client_gui->args, com);
        return 1;
    }
    return 0;
}

static int is_valid_opt_ia(size_t i, ia_t *ia,
        server_ia_t *server_ia, common_t *com)
{
    int count = 0;
    msg_queue_t *msg = ia->msg_queue;
    while (msg != NULL) {
        count++;
        msg = msg->next_msg;
    }
    if (count == 10) {
        return error("the maximum number of orders possible is reached", 1);
    }
    if (strcmp(server_ia->comd, COMMAND_GESTION_IA[i].comd) == 0) {
        COMMAND_GESTION_IA[i].handler(ia, server_ia->args, com);
        return 1;
    }
    return 0;
}

void to_check_command_exist_gui(client_gui_t *client_gui,
                                gui_t *gui, common_t *com)
{
    int value = 0;

    for (size_t i = 0; i < ARRAY_SIZE(COMMAND_GESTION_CLIENT_GUI); i++) {
        if (value != 1) {
            value = is_valid_opt_gui(i, gui, client_gui, com);
        }
    }
    if (value == 0) {
        funct_server_suc(NULL, gui, com);
    }
    free(client_gui->comd);
    free_array((void**)client_gui->args);
}

void to_check_command_exist_ia(server_ia_t *server_ia, ia_t *ia,
                                common_t *com)
{
    int value = 0;
    if (ia == NULL) {
        error("ia player ID's is not the same as the client's player", 0);
        return;
    }
    for (size_t i = 0; i < ARRAY_SIZE(COMMAND_GESTION_IA); i++) {
        if (value != 1) {
            value = is_valid_opt_ia(i, ia, server_ia, com);
        }
    }
    if (value == 0) {
        printf("%sInvalid command: %s%s%s\n", R, G, server_ia->comd, N);
    }
    free(server_ia->comd);
    free_array((void**)server_ia->args);
}
