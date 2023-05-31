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

typedef struct msg_queue_s {
    time_t time;
    uint8_t **msg;
    void (*handler)(uint8_t **args, buffered_socket_t *client, void *info); //FIXME - check arguments
    //NOTE - pointeur sur fonctione qu'on doit executer
    msg_queue_s *next_msg;
} msg_queue_t;

typedef struct error_handling_s {
    int error_code;
    uint8_t *msg_error;
} error_handling_t;

typedef struct buffer_s {
    u_int8_t *bytes;
    size_t usedSize;
} buffer_t;

typedef struct sock_s {
    int sockfd;
    struct sockaddr_in addr;
} sock_t;

typedef struct buffered_socket_s {
    buffer_t read_buffer;
    buffer_t writte_buffer;
    sock_t sock;
} buffered_socket_t;

#endif /* !COMMON_H_ */

