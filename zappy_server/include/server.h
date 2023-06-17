/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

        #include <sys/select.h>
        #include <sys/time.h>
        #include <sys/types.h>
        #include <netinet/in.h>
        #include <unistd.h>

        #include "teams.h"

        #define MAX_CLIENTS     MAX_PLAYER

enum client_type {
    UNDEFINED,
    IA,
    GUI,
};

typedef struct server_s {
    int socket;
    int maxsd;
    struct sockaddr_in addr;
    fd_set read_fd;
    socklen_t size;
} server_t;

typedef struct client_s {
    int type;
    int socket;
    struct sockaddr_in addr;
    void *str_cli;
} client_t;

client_t *set_all_clients(void);
int close_client(int client_socket, server_t *server);
void free_clients(client_t *cli, server_t *server);

#endif /* !SERVER_H_ */
