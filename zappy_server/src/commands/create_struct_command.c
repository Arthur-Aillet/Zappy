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

static void create_args_client_gui(uint8_t **command, int nbr_args,
                                client_gui_t *gui)
{
    int i;
    for (i = 1; i < nbr_args; i++) {
        gui->args = realloc(gui->args, sizeof(uint8_t *) * i);
        if (gui->args == NULL) {
            gui->args = NULL;
            return;
        }
        gui->args[i - 1] = (uint8_t *)strcat((char *)gui->args[i - 1],
                            (char *)command[i]);
    }
    gui->args[i] = NULL;
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
    int i = 1;
    ia->args = calloc(sizeof(uint8_t *), nbr_args + 1);
    if (ia->args == NULL) {
        ia->args = NULL;
        return;
    }
    for (; i < nbr_args; i++) {
        ia->args[i - 1] = malloc(sizeof(uint8_t) *
                        (strlen((char*)command[i]) + 1));
        ia->args[i - 1][0] = '\0';
        ia->args[i - 1] = (uint8_t *)strcat((char *)ia->args[i - 1],
                        (char *)command[i]);
    }
    ia->args[i] = NULL;
}

server_ia_t create_struct_client_ia(uint8_t **command)
{
    server_ia_t ia;
    ia.comd = NULL;
    ia.args = NULL;
    int nbr_args = compt_nbr_args_on_command(command);

    if (command[0] == NULL) {
        return ia;
    }
    ia.comd = malloc(sizeof(uint8_t) * (strlen((char *)command[0]) + 1));
    if (ia.comd == NULL) {
        return ia;
    }
    ia.comd[0] = (uint8_t)'\0';
    ia.comd = (uint8_t *)strcat((char *)ia.comd, (char *)command[0]);
    create_args_client_ia(command, nbr_args, &ia);
    return ia;
}
