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
        gui->buffer.bufferWrite.usedSize += strlen(args[i + 3]) + 1;
        gui->buffer.bufferWrite.octets =
                    realloc(gui->buffer.bufferWrite.octets,
                    sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat(gui->buffer.bufferWrite.octets, args[i + 3]);
        strcat(gui->buffer.bufferWrite.octets, " ");
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
    gui->buffer.bufferWrite.usedSize += 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
}

void funct_server_pic_level_other(char **args, gui_t *gui)
{
    for (int i = 0; i < 6; i++) {
        gui->buffer.bufferWrite.usedSize += strlen(args[i + 3]) + 1;
        gui->buffer.bufferWrite.octets =
                    realloc(gui->buffer.bufferWrite.octets,
                    sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat(gui->buffer.bufferWrite.octets, args[i + 3]);
        strcat(gui->buffer.bufferWrite.octets, " ");
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
    gui->buffer.bufferWrite.usedSize += 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
}

static void funct_server_pic_level_two_three(char **args, gui_t *gui)
{
    for (int i = 0; i < 2; i++) {
        gui->buffer.bufferWrite.usedSize += strlen(args[i + 3]) + 1;
        gui->buffer.bufferWrite.octets =
                    realloc(gui->buffer.bufferWrite.octets,
                    sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat(gui->buffer.bufferWrite.octets, args[i + 3]);
        strcat(gui->buffer.bufferWrite.octets, " ");
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
    gui->buffer.bufferWrite.usedSize += 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
}

static void funct_server_pic_next(char **args, gui_t *gui)
{
    if (atoi(args[2]) == 1) {
        gui->buffer.bufferWrite.usedSize += strlen(args[3]) + 2;
        gui->buffer.bufferWrite.octets =
                    realloc(gui->buffer.bufferWrite.octets,
                    sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat(gui->buffer.bufferWrite.octets, args[3]);
        strcat(gui->buffer.bufferWrite.octets, "\n\0");
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
    gui->buffer.bufferWrite.usedSize = strlen(args[0]) +
                strlen(args[1]) + strlen(args[2]) + 7;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "pic ");
    strcat(gui->buffer.bufferWrite.octets, args[0]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[1]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[2]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    funct_server_pic_next(args, gui);
}
