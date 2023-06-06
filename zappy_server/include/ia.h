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

typedef struct ia_s {
    player_t *player;
    msg_queue_t *queue;
    error_handling_t *error; //FIXME - chaque protocole à sa propre error handlig ? ou on crrer une seul error handling (on devra rajouter un pointeur) ?
} ia_t;

typedef struct server_ia_s {
    const uint8_t *comd;
    uint8_t **args;
    void (*handler)(ia_t *ia, uint8_t **args);
} server_ia_t;

void funct_client_ia_msz(ia_t *ia, uint8_t **args);
void funct_client_ia_mct(ia_t *ia, uint8_t **args);
void funct_client_ia_tna(ia_t *ia, uint8_t **args);
void funct_client_ia_ppo(ia_t *ia, uint8_t **args);
void funct_client_ia_plv(ia_t *ia, uint8_t **args);
void funct_client_ia_pin(ia_t *ia, uint8_t **args);
void funct_client_ia_sgt(ia_t *ia, uint8_t **args);
void funct_client_ia_sst(ia_t *ia, uint8_t **args);
void funct_client_ia_fork(ia_t *ia, uint8_t **args);
void funct_client_ia_eject(ia_t *ia, uint8_t **args);
void funct_client_ia_death(ia_t *ia, uint8_t **args);
void funct_client_ia_take_obj(ia_t *ia, uint8_t **args);
void funct_client_ia_set_obj(ia_t *ia, uint8_t **args);
void funct_client_ia_incantation(ia_t *ia, uint8_t **args);
void funct_client_ia_connect_bar(ia_t *ia, uint8_t **args);

// static const server_ia_t COMMAND_GESTION_IA[] = {
//     {"Forward", funct_client_ia_msz},
//     {"Right", funct_client_ia_mct},
//     {"Left", funct_client_ia_tna},
//     {"Look", funct_client_ia_ppo},
//     {"Inventory", funct_client_ia_plv},
//     {"Broadcast", funct_client_ia_pin},
//     {"message", funct_client_ia_sgt},
//     {"Connect_nbr", funct_client_ia_sst},
//     {"Fork", funct_client_ia_fork},
//     {"Eject", funct_client_ia_eject},
//     {"death", funct_client_ia_death},
//     {"Take object", funct_client_ia_take_obj},
//     {"Set object", funct_client_ia_set_obj},
//     {"Incantation", funct_client_ia_incantation},
//     {"Connect_nbr", funct_client_ia_connect_bar},
// };

ia_t *set_ia(void);
void free_ia(ia_t *ia);

#endif /* !IA_H_ */
