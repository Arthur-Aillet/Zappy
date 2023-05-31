/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** listening_socket.c
*/

#include "zappy.h"
#include <errno.h>

// static void new_client(void)
// {
//     struct sockaddr_in a_cli;
//     int acc = accept(server_socket, (struct sockaddr *)&a_cli, socklen_t_server_size);
//     if (acc < 0) {
//         if (errno != EWOULDBLOCK && errno != EAGAIN) {
//             exit(84);
//         }
//         return;
//     }
//     create_new_client();
// }

// static void check_incoming_data(void) //NOTE - Transforms this function for create threads
// {
//     while (auto& client : clients) {
//         if (FD_ISSET(socket_client, READ_FDS))
//             search_command();
//     }
// }

// void listening_socket(void)
// {
//     (FD_ISSET()) ? new_client() : check_incomming_data();
// }