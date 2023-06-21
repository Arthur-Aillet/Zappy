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
    if (strcmp((char*)client_gui->comd,
        (char*)COMMAND_GESTION_CLIENT_GUI[i].comd) == 0) {
        COMMAND_GESTION_CLIENT_GUI[i].handler(gui, client_gui->args, com);
        return 1;
    }
    return 0;
}

static int is_valid_opt_ia(size_t i, ia_t *ia,
        server_ia_t *server_ia, common_t *com)
{
    if (strcmp((char*)server_ia->comd,
        (char*)COMMAND_GESTION_IA[i].comd) == 0) {
        COMMAND_GESTION_IA[i].handler(ia, server_ia->args, com);
        player_t *player = (player_t*)ia->player;
        printf("%sPlayer\n\tposition:%s%d %d%s\n\torientation: %s%ld%s\n", CYAN, R, player->x, player->y, CYAN, R, player->orientation, N);
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
}

void to_check_command_exist_ia(server_ia_t *server_ia, ia_t *ia,
                                common_t *com)
{
    for (int i = 0; server_ia->args[i] != NULL; i++)
        printf("%d: %s\n", i, (char *)server_ia->args[i]);
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
        error("500 Unknow command.\r\n", 0);
    }
}
