/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** ia
*/

#ifndef IA_H_
    #define IA_H_

    #define OCTETS      ia->buffer.bufferWrite.octets
    #define SIZE        ia->buffer.bufferWrite.usedSize

    #include "common.h"
    #include "teams.h"
    #include "error_handling.h"

typedef struct common_s common_t;
typedef struct msg_queue_s msg_queue_t;
typedef struct ia_s {
    player_t *player;
    buffered_socket_t buffer;
    msg_queue_t *msg_queue;
    error_handling_t *error;
} ia_t;

typedef struct common_s common_t;
void funct_response_ia_forward(char **args, void *info, common_t *com);
void funct_response_ia_right(char **args, void *info, common_t *com);
void funct_response_ia_left(char **args, void *info, common_t *com);
void funct_response_ia_look(char **args, void *info, common_t *com);
void funct_response_ia_inventory(char **args, void *info, common_t *com);
void funct_response_ia_broadcast(char **args, void *info, common_t *com);
void funct_response_ia_msg(char **args, void *info, common_t *com);
void funct_response_ia_connect_nbr(char **args, void *info, common_t *com);
void funct_response_ia_fork(char **args, void *info, common_t *com);
void funct_response_ia_eject(char **args, void *info, common_t *com);
void funct_response_ia_death(char **args, void *info, common_t *com);
void funct_response_ia_take_obj(char **args, void *info, common_t *com);
void funct_response_ia_set_obj(char **args, void *info, common_t *com);
void funct_response_ia_incantation(char **args, void *info, common_t *com);
void funct_response_ia_connect_bar(char **args, void *info, common_t *com);

typedef struct server_ia_s {
    char *comd;
    char **args;
    void (*handler)(ia_t *ia, char **args, common_t *com);
} server_ia_t;

void funct_client_ia_forward(ia_t *ia, char **args, common_t *com);
void funct_client_ia_right(ia_t *ia, char **args, common_t *com);
void funct_client_ia_left(ia_t *ia, char **args, common_t *com);
void funct_client_ia_look(ia_t *ia, char **args, common_t *com);
void funct_client_ia_inventory(ia_t *ia, char **args, common_t *com);
void funct_client_ia_broadcast(ia_t *ia, char **args, common_t *com);
void funct_client_ia_msg(ia_t *ia, char **args, common_t *com);
void funct_client_ia_connect_nbr(ia_t *ia, char **args, common_t *com);
void funct_client_ia_fork(ia_t *ia, char **args, common_t *com);
void funct_client_ia_eject(ia_t *ia, char **args, common_t *com);
void funct_client_ia_take_obj(ia_t *ia, char **args, common_t *com);
void funct_client_ia_set_obj(ia_t *ia, char **args, common_t *com);
void funct_client_ia_incantation(ia_t *ia, char **args, common_t *com);
void funct_client_ia_connect_bar(ia_t *ia, char **args, common_t *com);

static const server_ia_t COMMAND_GESTION_IA[] = {
    {"Forward", NULL, funct_client_ia_forward},
    {"Right", NULL, funct_client_ia_right},
    {"Left", NULL, funct_client_ia_left},
    {"Look", NULL, funct_client_ia_look},
    {"Inventory", NULL, funct_client_ia_inventory},
    {"Broadcast", NULL, funct_client_ia_broadcast},
    {"message", NULL, funct_client_ia_msg},
    {"Connect_nbr", NULL, funct_client_ia_connect_nbr},
    {"Fork", NULL, funct_client_ia_fork},
    {"Eject", NULL, funct_client_ia_eject},
    {"Take", NULL, funct_client_ia_take_obj},
    {"Set", NULL, funct_client_ia_set_obj},
    {"Incantation", NULL, funct_client_ia_incantation},
    {"Connect_nbr", NULL, funct_client_ia_connect_bar},
};

ia_t *set_ia(void);
void close_ia(ia_t *ia);
void free_ia(ia_t *ia);

#endif /* !IA_H_ */
