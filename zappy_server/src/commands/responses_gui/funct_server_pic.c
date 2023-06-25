/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pic
*/

#include "zappy.h"

void funct_server_pic_level_four_five(char **args, gui_t *gui)
{
    for (int i = 0; i < 4; i++) {
        GUI_SIZE += strlen(args[i + 3]) + 1;
        GUI_OCTETS =
                    realloc(GUI_OCTETS,
                    sizeof(char) * (GUI_SIZE + 1));
        if (GUI_OCTETS == NULL) {
            return;
        }
        strcat(GUI_OCTETS, args[i + 3]);
        strcat(GUI_OCTETS, " ");
    }
    GUI_OCTETS[GUI_SIZE] = '\n';
    GUI_SIZE += 1;
    GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[GUI_SIZE] = '\0';
}

void funct_server_pic_level_other(char **args, gui_t *gui)
{
    for (int i = 0; i < 6; i++) {
        GUI_SIZE += strlen(args[i + 3]) + 1;
        GUI_OCTETS =
                    realloc(GUI_OCTETS,
                    sizeof(char) * (GUI_SIZE + 1));
        if (GUI_OCTETS == NULL) {
            return;
        }
        strcat(GUI_OCTETS, args[i + 3]);
        strcat(GUI_OCTETS, " ");
    }
    GUI_OCTETS[GUI_SIZE] = '\n';
    GUI_SIZE += 1;
    GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[GUI_SIZE] = '\0';
}

static void funct_server_pic_level_two_three(char **args, gui_t *gui)
{
    for (int i = 0; i < 2; i++) {
        GUI_SIZE += strlen(args[i + 3]) + 1;
        GUI_OCTETS =
                    realloc(GUI_OCTETS,
                    sizeof(char) * (GUI_SIZE + 1));
        if (GUI_OCTETS == NULL) {
            return;
        }
        strcat(GUI_OCTETS, args[i + 3]);
        strcat(GUI_OCTETS, " ");
    }
    GUI_OCTETS[GUI_SIZE] = '\n';
    GUI_SIZE += 1;
    GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[GUI_SIZE] = '\0';
}

static void funct_server_pic_next(char **args, gui_t *gui)
{
    if (atoi(args[2]) == 1) {
        GUI_SIZE += strlen(args[3]) + 2;
        GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE + 1));
        if (GUI_OCTETS == NULL) {
            return;
        }
        strcat(GUI_OCTETS, args[3]);
        strcat(GUI_OCTETS, "\n\0");
    } else if (atoi(args[2]) == 2 || atoi(args[2]) == 3) {
        funct_server_pic_level_two_three(args, gui);
    }
    funct_server_pic_send_message(args, gui);
}

void funct_server_pic(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;

    (void)args;
    (void)common;
    GUI_SIZE = strlen(args[0]) + strlen(args[1]) + strlen(args[2]) + 7;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "pic ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[1]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[2]);
    strcat(GUI_OCTETS, " ");
    funct_server_pic_next(args, gui);
    free(GUI_OCTETS);
}
