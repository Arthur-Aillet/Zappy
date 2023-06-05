/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** check_command
*/

#include "zappy.h"

static int is_valid_opt_gui(client_gui_t const *arg, size_t i,
            gui_t *gui, client_gui_t *client_gui)
{
    if (strcmp((const char *)client_gui->comd[0], arg->comd) == 0) {
        COMMAND_GESTION_CLIENT_GUI[i].handler(gui, client_gui->args);
        return 1;
    }
    return 0;
}

static int is_valid_opt_ia(server_ia_t const *arg, size_t i,
            ia_t *ia, server_ia_t *server_ia)
{
    if (strcmp((const char *)server_ia->comd[0], arg->comd) == 0) {
        COMMAND_GESTION_IA[i].handler(ia, server_ia->args);
        return 1;
    }
    return 0;
}

void to_check_command_exist_gui(client_gui_t *client_gui, gui_t *gui)
{
    int value = 0;

    for (size_t i = 0; i < ARRAY_SIZE(COMMAND_GESTION_CLIENT_GUI); i++) {
        if (value != 1) {
            value = is_valid_opt_gui(&COMMAND_GESTION_CLIENT_GUI[i], i,
            gui, client_gui);
        }
    }
    if (value == 0) {
        printf("500 Unknow command.\r\n");
    }
}

void to_check_command_exist_ia(server_ia_t *server_ia, ia_t *ia)
{
    int value = 0;

    for (size_t i = 0; i < ARRAY_SIZE(COMMAND_GESTION_IA); i++) {
        if (value != 1) {
            value = is_valid_opt_ia(&COMMAND_GESTION_IA[i], i,
            ia, server_ia);
        }
    }
    if (value == 0) {
        printf("500 Unknow command.\r\n");
    }
}
