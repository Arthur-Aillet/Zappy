/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** ia
*/

#ifndef IA_H_
    #define IA_H_

    #include "common.h"

typedef struct ia_s {
    uint8_t **arg;
    msg_queue_t *queue;
    error_handling_t *error; //FIXME - chaque protocole à sa propre error handlig ? ou on crrer une seul error handling (on devra rajouter un pointeur) ?
} ia_t;

typedef struct server_ia_s {
    const uint8_t *cmd_name;
    void (*handler)(ia_t *ia); //FIXME - same question that in struct gui_t
} server_ia_t;

static const client_ia_t COMMAND_GESTION_IA[] = {
    {"Forward", funct_client_msz},
    {"Right", funct_client_mct},
    {"Left", funct_client_tna},
    {"Look", funct_client_ppo},
    {"Inventory", funct_client_plv},
    {"Broadcast", funct_client_pin},
    {"message", funct_client_sgt},
    {"Connect_nbr", funct_client_sst},
    {"Fork", funct_client_sst},
    {"Eject", funct_client_sst},
    {"death", funct_client_sst},
    {"Take object", funct_client_sst},
    {"Set object", funct_client_sst},
    {"Incantation", funct_client_sst},
    {"Connect_nbr", funct_client_sst},
};

ia_t *set_ia(void);

#endif /* !IA_H_ */
