/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_client.c
*/

#include "zappy.h"
#include <stdlib.h>

/**
 * @brief set value of a client_t structure
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param void
 * @return client_t
*/
static client_t set_client(void)
{
    client_t cli;

    cli.socket = 0;
    cli.type = UNDEFINED;
    cli.str_cli = NULL;
    return cli;
}

/**
 * @brief set the array of client_t
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param void
 * @return client_t *client
*/
client_t *set_all_clients(void)
{
    client_t *client = malloc(sizeof(client_t) * (MAX_CLIENTS + 1));

    if (client == NULL)
        exit(error("Malloc error: Set clients", 84));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client[i] = set_client();
    }
    return client;
}

/**
 * @brief close the connection to the server of the specified client
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param int client_socket: the socket descriptor
 * @param server_t *server: used for disconnect all clients connections
 * @return int: 0 (used for reset socket descriptor)
 */
int close_client(int client_socket, server_t *server)
{
    if (client_socket != 0) {
        FD_CLR(client_socket, &server->read_fd);
        shutdown(client_socket, SHUT_RDWR);
        close(client_socket);
    }
    return 0;
}

/**
 * @brief close all connections socket and free the array of client_t
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param client_t *cli: free this array of client_t
 * @param server_t *server: used for disconnect all clients connections
 * @return void
 */
void free_clients(client_t *cli, server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (cli[i].socket != 0) {
            cli[i].type = UNDEFINED;
            cli[i].socket = close_client(cli[i].socket, server);
        }
    }
    free(cli);
}
