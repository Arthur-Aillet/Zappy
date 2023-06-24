/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pic_next
*/

#include "zappy.h"

void funct_server_pic_send_message(char **args, gui_t *gui)
{
    if (atoi(args[2]) == 4 || atoi(args[2]) == 5) {
        funct_server_pic_level_four_five(args, gui);
    } else if (atoi(args[2]) == 6 || atoi(args[2]) == 7) {
        funct_server_pic_level_other(args, gui);
    }
    write(gui->buffer.sock.sockfd, GUI_OCTETS, GUI_SIZE);
    basic_log("pic send", C, 0);
}
