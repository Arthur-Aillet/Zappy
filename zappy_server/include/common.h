/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** common
*/

#ifndef COMMON_H_
    #define COMMON_H_
    #include <stdint.h>
    #include <time.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/stat.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <sys/time.h>
    #include <stdio.h>
    #include <stdlib.h>

enum resources {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    EGG
};

typedef struct buffer_s {
    char *octets;
    size_t usedSize;
} buffer_t;

typedef struct sock_s {
    int sockfd;
    struct sockaddr_in addr;
} sock_t;

typedef struct buffered_socket_s {
    buffer_t bufferRead;
    buffer_t bufferWrite;
    sock_t sock;
} buffered_socket_t;

typedef struct error_handling_s {
    int error_code;
    char *msg_error;
} error_handling_t;

//------------ LIB -------------------------------------------------//

char **my_str_to_word_array(char *str, char **seg, char c);
void free_array(void **arr);

//-----------------------------------------------------------------//
#endif /* !COMMON_H_ */
