/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pic_next
*/

#include "zappy.h"

void funct_server_pic_send_message(uint8_t **args, gui_t *gui)
{
    if (atoi((char *)args[2]) == 4 || atoi((char *)args[2]) == 5) {
        funct_server_pic_level_four_five(args, gui);
    } else if (atoi((char *)args[2]) == 6 || atoi((char *)args[2]) == 7) {
        funct_server_pic_level_other(args, gui);
    }
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
    gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pic\n");
}
