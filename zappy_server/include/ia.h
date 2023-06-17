/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** ia
*/

#ifndef IA_H_
    #define IA_H_

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
void funct_response_ia_forward(uint8_t **args, void *info, common_t *com);
void funct_response_ia_right(uint8_t **args, void *info, common_t *com);
void funct_response_ia_left(uint8_t **args, void *info, common_t *com);
void funct_response_ia_look(uint8_t **args, void *info, common_t *com);
void funct_response_ia_inventory(uint8_t **args, void *info, common_t *com);
void funct_response_ia_broadcast(uint8_t **args, void *info, common_t *com);
void funct_response_ia_msg(uint8_t **args, void *info, common_t *com);
void funct_response_ia_connect_nbr(uint8_t **args, void *info, common_t *com);
void funct_response_ia_fork(uint8_t **args, void *info, common_t *com);
void funct_response_ia_eject(uint8_t **args, void *info, common_t *com);
void funct_response_ia_death(uint8_t **args, void *info, common_t *com);
void funct_response_ia_take_obj(uint8_t **args, void *info, common_t *com);
void funct_response_ia_set_obj(uint8_t **args, void *info, common_t *com);
void funct_response_ia_incantation(uint8_t **args, void *info, common_t *com);
void funct_response_ia_connect_bar(uint8_t **args, void *info, common_t *com);

typedef struct server_ia_s {
    const uint8_t *comd;
    uint8_t **args;
    void (*handler)(ia_t *ia, uint8_t **args, common_t *com);
} server_ia_t;

void funct_client_ia_forward(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_right(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_left(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_look(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_inventory(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_broadcast(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_msg(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_connect_nbr(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_fork(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_eject(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_take_obj(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_set_obj(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_incantation(ia_t *ia, uint8_t **args, common_t *com);
void funct_client_ia_connect_bar(ia_t *ia, uint8_t **args, common_t *com);

static const server_ia_t COMMAND_GESTION_IA[] = {
    {(const uint8_t*)"Forward", NULL, funct_client_ia_forward},
    {(const uint8_t*)"Right", NULL, funct_client_ia_right},
    {(const uint8_t*)"Left", NULL, funct_client_ia_left},
    {(const uint8_t*)"Look", NULL, funct_client_ia_look},
    {(const uint8_t*)"Inventory", NULL, funct_client_ia_inventory},
    {(const uint8_t*)"Broadcast", NULL, funct_client_ia_broadcast},
    {(const uint8_t*)"message", NULL, funct_client_ia_msg},
    {(const uint8_t*)"Connect_nbr", NULL, funct_client_ia_connect_nbr},
    {(const uint8_t*)"Fork", NULL, funct_client_ia_fork},
    {(const uint8_t*)"Eject", NULL, funct_client_ia_eject},
    {(const uint8_t*)"Take object", NULL, funct_client_ia_take_obj},
    {(const uint8_t*)"Set object", NULL, funct_client_ia_set_obj},
    {(const uint8_t*)"Incantation", NULL, funct_client_ia_incantation},
    {(const uint8_t*)"Connect_nbr", NULL, funct_client_ia_connect_bar},
};

ia_t *set_ia(void);
void free_ia(ia_t *ia);

#endif /* !IA_H_ */
