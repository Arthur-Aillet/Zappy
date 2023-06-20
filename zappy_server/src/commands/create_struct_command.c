/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** create_struct_command
*/

#include "zappy.h"

static int compt_nbr_args_on_command(uint8_t **command)
{
    int nbr_args = 0;

    for (; command[nbr_args] != NULL; nbr_args++);
    return nbr_args;
}

static void create_args_client_gui(uint8_t **command, int nbr_args, client_gui_t *gui)
{
    for (int i = 1; i < nbr_args; i++) {
        gui->args = realloc(gui->args, sizeof(uint8_t *) * i);
        if (gui->args == NULL) {
            gui->args = NULL;
            return;
        }
        gui->args[i - 1] = (uint8_t *)strcat((char *)gui->args[i - 1], (char *)command[i]);
    }
}

client_gui_t create_struct_client_gui(uint8_t **command)
{
    client_gui_t gui;
    int nbr_args = compt_nbr_args_on_command(command);

    if (command[0] == NULL) {
        return gui;
    } else {
        gui.comd = malloc(sizeof(uint8_t) * strlen((char *)command[0]));
        if (gui.comd == NULL) {
            return gui;
        }
        gui.comd = (uint8_t *)strcat((char *)gui.comd, (char *)command[0]);
        create_args_client_gui(command, nbr_args, &gui);
    }
    return gui;
}

static void create_args_client_ia(uint8_t **command, int nbr_args,
                                server_ia_t *ia)
{
    for (int i = 1; i < nbr_args; i++) {
        ia->args = realloc(ia->args, sizeof(uint8_t *) * i);
        if (ia->args == NULL) {
            ia->args = NULL;
            return;
        }
        ia->args[i - 1] = (uint8_t *)strcat((char *)ia->args[i - 1],
                        (char *)command[i]);
    }
}

server_ia_t create_struct_client_ia(uint8_t **command)
{
    server_ia_t ia;
    int nbr_args = compt_nbr_args_on_command(command);

    if (command[0] == NULL) {
        return ia;
    } else {
        ia.comd = malloc(sizeof(uint8_t) * strlen((char *)command[0]));
        if (ia.comd == NULL) {
            return ia;
        }
        ia.comd = (uint8_t *)strcat((char *)ia.comd, (char *)command[0]);
        create_args_client_ia(command, nbr_args, &ia);
    }
    return ia;
}

ia_t *to_find_ia_for_command(common_t *com, client_t client)
{
    player_t *player = (player_t *)client.str_cli;

    for (size_t tmp = 0; tmp < com->nb_ia; tmp++) {
        if (com->ia[tmp].player->id == player->id) {
            return &com->ia[tmp];
        }
    }
    return NULL;
}
