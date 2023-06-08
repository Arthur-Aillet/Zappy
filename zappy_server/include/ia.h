/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** ia
*/

#ifndef IA_H_
    #define IA_H_

    #include "common.h"

    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct ia_s {
    msg_queue_t *queue;
    error_handling_t *error; //FIXME - chaque protocole à sa propre error handlig ? ou on crrer une seul error handling (on devra rajouter un pointeur) ?
} ia_t;

typedef struct server_ia_s {
    const uint8_t *cmd_name;
    void (*handler)(uint8_t **args); //FIXME - same question that in struct gui_t
} server_ia_t;

// static const client_gui_t COMMAND_GESTION[] = {
//     {"Forward", funct_client_msz},
//     {"Right", funct_client_mct},
//     {"Left", funct_client_tna},
//     {"Look", funct_client_ppo},
//     {"Inventory", funct_client_plv},
//     {"Broadcast", funct_client_pin},
//     {"message", funct_client_sgt},
//     {"Connect_nbr", funct_client_sst},
//     {"Fork", funct_client_sst},
//     {"Eject", funct_client_sst},
//     {"death", funct_client_sst},
//     {"Take object", funct_client_sst},
//     {"Set object", funct_client_sst},
//     {"Incantation", funct_client_sst},
//     {"Connect_nbr", funct_client_sst},
// };

#endif /* !IA_H_ */

