/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** gui
*/

#ifndef GUI_H_
    #define GUI_H_

    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#include <stdio.h>
#include <stdint.h>
#include <time.h>

enum Resource {
    food,
    linemate,
    deraumere,
    sibur,
    mendiane,
    phiras,
    thystame,
    egg
};

enum orientation {
    Nord = 1,
    Est = 2,
    Sud = 3,
    West = 4,
};

typedef struct tile_s {
    size_t *resources;
} tile_t;

typedef struct map_s {
    tile_t **tiles;
    size_t width;
    size_t height;
} map_t;

typedef struct error_handling_s {
    int error;
    uint8_t *msg_error;
} error_handling_t;

typedef struct egg_s {
    size_t egg_id;
    size_t x;
    size_t y;
} egg_t;

typedef struct player_s {
    int id;
    size_t x;
    size_t y;
    size_t orientation;
    size_t level;
    size_t life;
    size_t satiety; //NOTE - if satiety == 0 then decrease life
    size_t *inventory;
    egg_t egg;
} player_t;

typedef struct teams_s {
    char *team_name;
    size_t nb_slot; //NOTE - nbr de joueur dans la teams
    size_t actif_player;
    player_t *player;
} teams_t;

typedef struct msg_queue_s {
    time_t time;
    uint8_t **msg;
    void (*handler)(uint8_t **args); //FIXME - check parameters
    //NOTE - pointeur sur fonctione qu'on doit executer
    msg_queue_s *next_msg;
} msg_queue_t;

typedef struct gui_s {
    map_t map;
    msg_queue_t *msg_queue;
    error_handling_t error; //FIXME - chaque protocole à sa propre error handlig ? ou on crrer une seul error handling (on devra rajouter un pointeur) ?
} gui_t;

typedef struct server_gui_s {
    const uint8_t *comd;
    void (*handler)(uint8_t **args, gui_t *gui);
} server_gui_t;

// static const server_gui_t COMMAND_GESTION[] = {
//     {"msz", funct_server_msz},
//     {"bct", funct_server_bct},
//     {"tna", funct_server_tna},
//     {"pnw", funct_server_pnw},
//     {"ppo", funct_server_ppo},
//     {"plv", funct_server_plv},
//     {"pin", funct_server_pin},
//     {"pex", funct_server_pex},
//     {"pbc", funct_server_pbc},
//     {"pic", funct_server_pic},
//     {"pie", funct_server_pie},
//     {"pfk", funct_server_pfk},
//     {"pdr", funct_server_pdr},
//     {"pgt", funct_server_pgt},
//     {"pdi", funct_server_pdi},
//     {"enw", funct_server_enw},
//     {"ebo", funct_server_ebo},
//     {"edi", funct_server_edi},
//     {"sgt", funct_server_sgt},
//     {"sst", funct_server_sst},
//     {"seg", funct_server_seg},
//     {"smg", funct_server_smg},
//     {"suc", funct_server_suc},
//     {"sbp", funct_server_sbp},
// };

typedef struct client_gui_s {
    const uint8_t *comd;
    void (*handler)(uint8_t **args);
} client_gui_t;

// static const client_gui_t COMMAND_GESTION[] = {
//     {"msz", funct_client_msz},
//     {"mct", funct_client_mct},
//     {"tna", funct_client_tna},
//     {"ppo", funct_client_ppo},
//     {"plv", funct_client_plv},
//     {"pin", funct_client_pin},
//     {"sgt", funct_client_sgt},
//     {"sst", funct_client_sst},
// };

typedef struct ia_s {
    uint8_t *msg_queue;
    error_handling_t error; //FIXME - same question that in struct gui_t
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

typedef struct common_s {
    gui_t *gui;
    ia_t *ia;
    uint8_t *teams;
    size_t port;
    size_t freq; //NOTE: - time unit
} common_t;

#endif /* !GUI_H_ */
