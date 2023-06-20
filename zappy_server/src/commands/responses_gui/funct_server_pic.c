/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pic
*/

#include "zappy.h"

void funct_server_pic(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;

    (void)args;
    (void)common;
    gui->buffer.bufferWrite.usedSize = strlen((char*)args[0]) + strlen((char*)args[1]) + strlen((char*)args[2]) + 7;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pic ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[1]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[2]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    if (atoi((char *)args[2]) == 1) {
        gui->buffer.bufferWrite.usedSize += strlen((char*)args[3]) + 2;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[3]);
        strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
    } else if (atoi((char *)args[2]) == 2 || atoi((char *)args[2]) == 3) {
        for (int i = 0; i < 2; i++) {
            gui->buffer.bufferWrite.usedSize += strlen((char*)args[i + 3]) + 1;
            gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
            if (gui->buffer.bufferWrite.octets == NULL) {
                return;
            }
            strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[i + 3]);
            strcat((char*)gui->buffer.bufferWrite.octets, " ");
        }
        gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
        gui->buffer.bufferWrite.usedSize += 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
    } else if (atoi((char *)args[2]) == 4 || atoi((char *)args[2]) == 5) {
        for (int i = 0; i < 4; i++) {
            gui->buffer.bufferWrite.usedSize += strlen((char*)args[i + 3]) + 1;
            gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
            if (gui->buffer.bufferWrite.octets == NULL) {
                return;
            }
            strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[i + 3]);
            strcat((char*)gui->buffer.bufferWrite.octets, " ");
        }
        gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
        gui->buffer.bufferWrite.usedSize += 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
    } else {
        for (int i = 0; i < 6; i++) {
            gui->buffer.bufferWrite.usedSize += strlen((char*)args[i + 3]) + 1;
            gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
            if (gui->buffer.bufferWrite.octets == NULL) {
                return;
            }
            strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[i + 3]);
            strcat((char*)gui->buffer.bufferWrite.octets, " ");
        }
        gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
        gui->buffer.bufferWrite.usedSize += 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
    }
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pic\n");
}
