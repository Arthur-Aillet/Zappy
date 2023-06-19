/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_all_bct
*/

#include "zappy.h"

static void funct_ressources_on_tiles(gui_t *gui, uint8_t **args,
                                    char *buffer_x)
{
    for (int i = 0; i < 7; i++) {
        sprintf(buffer_x, "%ld", gui->map.tiles[atoi((char*)args[0])]
                                        [atoi((char*)args[1])].ressources[i]);
        gui->buffer.bufferWrite.usedSize += strlen(buffer_x) + 1;
        gui->buffer.bufferWrite.octets =
        realloc(gui->buffer.bufferWrite.octets,
        sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, buffer_x);
        strcat((char*)gui->buffer.bufferWrite.octets, " ");
    }
}

static void funct_post_tiles(char *buffer_x, char *buffer_y, gui_t *gui)
{
    gui->buffer.bufferWrite.usedSize += 6 + strlen(buffer_x) +
                                        strlen(buffer_y);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat((char*)gui->buffer.bufferWrite.octets, "bct");
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buffer_x);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buffer_y);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
}

static void funct_for_on_tiles(gui_t *gui, uint8_t **args)
{
    char buffer_y[256];
    char buffer_x[256];

    for (size_t nbr_tiles_width = 0; nbr_tiles_width
                            < gui->map.width; nbr_tiles_width++) {
        for (size_t nbr_tiles_height = 0; nbr_tiles_height
                    < gui->map.height; nbr_tiles_height++) {
            sprintf(buffer_x, "%ld", nbr_tiles_width);
            sprintf(buffer_y, "%ld", nbr_tiles_height);
            funct_post_tiles(buffer_x, buffer_y, gui);
            funct_ressources_on_tiles(gui, args, buffer_x);
            gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize]
                                                                    = '\n';
        }
    }
}

void funct_server_all_bct(uint8_t **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    gui->buffer.bufferWrite.usedSize = 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    funct_for_on_tiles(gui, args);
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
            gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_all_bct\n");
}
