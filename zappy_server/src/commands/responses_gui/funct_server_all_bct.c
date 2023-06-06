/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_all_bct
*/

#include "zappy.h"

void funct_server_all_bct(uint8_t **args, gui_t *gui, common_t *common)
{
    char buffer_x[256];
    char buffer_y[256];

    gui->buffer.bufferWrite.usedSize = 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
            if (gui->buffer.bufferWrite.octets == NULL) {
                //error
                return;
            }
    gui->buffer.bufferWrite.octets[0] = '\0';
    for (int nbr_tiles_width = 0; nbr_tiles_width < gui->map.width; nbr_tiles_width++) {
        for (int nbr_tiles_height = 0; nbr_tiles_height < gui->map.height; nbr_tiles_height++) {
            sprintf(buffer_x, "%d", nbr_tiles_width);
            sprintf(buffer_y, "%d", nbr_tiles_height);
            gui->buffer.bufferWrite.usedSize += 6 + strlen(buffer_x) + strlen(buffer_y);
            gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
            if (gui->buffer.bufferWrite.octets == NULL) {
                //error
                return;
            }
            strcat(gui->buffer.bufferWrite.octets, "bct");
            strcat(gui->buffer.bufferWrite.octets, " ");
            strcat(gui->buffer.bufferWrite.octets, buffer_x);
            strcat(gui->buffer.bufferWrite.octets, " ");
            strcat(gui->buffer.bufferWrite.octets, buffer_y);
            strcat(gui->buffer.bufferWrite.octets, " ");
            for (int i = 0; i < 7; i++) {
                sprintf(buffer_x, "%d", gui->map.tiles[atoi(args[0])][atoi(args[1])].ressources[i]);
                gui->buffer.bufferWrite.usedSize += strlen(buffer_x) + 1;
                gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
                if (gui->buffer.bufferWrite.octets == NULL) {
                    //error
                    return;
                }
                strcat(gui->buffer.bufferWrite.octets, buffer_x);
                strcat(gui->buffer.bufferWrite.octets, " ");
            }
            gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
        }
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_all_bct\n");
}
