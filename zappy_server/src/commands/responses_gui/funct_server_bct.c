/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_bct
*/

#include "zappy.h"

static void funct_ressources_on_tiles(gui_t *gui, size_t x,
                                        size_t y, char *buf_x)
{
    for (int i = 0; i < 7; i++) {
        sprintf(buf_x, "%ld", gui->map.tiles[x][y].ressources[i]);
        gui->buffer.bufferWrite.usedSize += strlen(buf_x) + 3;
        gui->buffer.bufferWrite.octets =
        realloc(gui->buffer.bufferWrite.octets,
        sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, buf_x);
        strcat((char*)gui->buffer.bufferWrite.octets, " ");
    }
    strcat((char*)gui->buffer.bufferWrite.octets, "\n");
}

static void funct_post_tiles(char *buf_x, char *buf_y, gui_t *gui)
{
    gui->buffer.bufferWrite.usedSize += 7 + strlen(buf_x) + strlen(buf_y);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat((char*)gui->buffer.bufferWrite.octets, "bct");
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buf_x);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buf_y);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
}

void funct_prepare_response(gui_t *gui, size_t x, size_t y)
{
    char buf_y[256];
    char buf_x[256];

    sprintf(buf_x, "%ld", x);
    sprintf(buf_y, "%ld", y);
    funct_post_tiles(buf_x, buf_y, gui);
    funct_ressources_on_tiles(gui, x, y, buf_x);
}

void funct_server_bct(uint8_t **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;
    if (args == NULL || args[0] == NULL || args[1] == NULL) {
        error("Invalid arguments", 0);
        return;
    }
    gui->buffer.bufferWrite.usedSize = 6 + strlen((char*)args[0]) +
                                        strlen((char*)args[1]);
    free(gui->buffer.bufferWrite.octets);
    gui->buffer.bufferWrite.octets = malloc(sizeof(uint8_t) *
                                    (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    funct_prepare_response(gui, atoi((char*)args[0]), atoi((char*)args[1]));
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        strlen((char*)gui->buffer.bufferWrite.octets));
    printf("rentrer dans la fonctions funct_server_bct\n");
}
