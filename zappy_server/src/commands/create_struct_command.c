/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** create_struct_command
*/

#include "zappy.h"

static int compt_nbr_args_on_command(char **command)
{
    int nbr_args = 0;

    for (; command[nbr_args] != NULL; nbr_args++);
    return nbr_args;
}

static void create_args_client_gui(char **command, int nbr_args,
                                client_gui_t *gui)
{
    int i;
    gui->args = calloc(sizeof(char *), nbr_args + 1);
    if (gui->args == NULL)
        return;
    for (i = 1; i < nbr_args; i++) {
        gui->args[i - 1] = malloc(sizeof(char) * (strlen(command[i]) + 1));
        gui->args[i - 1][0] = '\0';
        strcat(gui->args[i - 1], command[i]);
    }
    gui->args[i] = NULL;
}

client_gui_t create_struct_client_gui(char **command)
{
    client_gui_t gui;
    int nbr_args = compt_nbr_args_on_command(command);

    if (command[0] == NULL) {
        return gui;
    } else {
        gui.comd = malloc(sizeof(char) * (strlen(command[0]) + 1));
        if (gui.comd == NULL) {
            return gui;
        }
        gui.comd[0] = '\0';
        gui.comd = strcat(gui.comd, command[0]);
        create_args_client_gui(command, nbr_args, &gui);
    }
    return gui;
}

static void create_args_client_ia(char **command, int nbr_args,
                                server_ia_t *ia)
{
    int i = 1;
    ia->args = calloc(sizeof(char *), nbr_args + 1);
    if (ia->args == NULL) {
        return;
    }
    for (; i < nbr_args; i++) {
        ia->args[i - 1] = malloc(sizeof(char) * (strlen(command[i]) + 1));
        ia->args[i - 1][0] = '\0';
        strcat(ia->args[i - 1], command[i]);
    }
    ia->args[i] = NULL;
}

server_ia_t create_struct_client_ia(char **command)
{
    server_ia_t ia;
    ia.comd = NULL;
    ia.args = NULL;
    int nbr_args = compt_nbr_args_on_command(command);

    if (command[0] == NULL) {
        return ia;
    }
    ia.comd = malloc(sizeof(char) * (strlen(command[0]) + 1));
    if (ia.comd == NULL) {
        return ia;
    }
    ia.comd[0] = (char)'\0';
    ia.comd = strcat(ia.comd, command[0]);
    create_args_client_ia(command, nbr_args, &ia);
    return ia;
}
