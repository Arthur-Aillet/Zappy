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
    u_int8_t msg_error;
} error_handling_t;

typedef struct player_s {
    size_t pos_x;
    size_t pos_y;
    size_t level;
    size_t life;
    size_t satiety;
    size_t *resources;
} player_t;

typedef struct teams_s {
    u_int8_t *teams;
    size_t slot;
    player_t *player;
} teams_t;

typedef struct gui_s {
    map_t map;
    error_handling_t error;
    teams_t *teams;
} gui_t;

typedef struct server_gui_s {
    const u_int8_t *comd;
    void (*handler)(u_int8_t **args, gui_t *gui);
} server_gui_t;

static const server_gui_t COMMAND_GESTION[] = {
    {"msz", funct_server_msz},
    {"bct", funct_server_bct},
    {"tna", funct_server_tna},
    {"pnw", funct_server_pnw},
    {"ppo", funct_server_ppo},
    {"plv", funct_server_plv},
    {"pin", funct_server_pin},
    {"pex", funct_server_pex},
    {"pbc", funct_server_pbc},
    {"pic", funct_server_pic},
    {"pie", funct_server_pie},
    {"pfk", funct_server_pfk},
    {"pdr", funct_server_pdr},
    {"pgt", funct_server_pgt},
    {"pdi", funct_server_pdi},
    {"enw", funct_server_enw},
    {"ebo", funct_server_ebo},
    {"edi", funct_server_edi},
    {"sgt", funct_server_sgt},
    {"sst", funct_server_sst},
    {"seg", funct_server_seg},
    {"smg", funct_server_smg},
    {"suc", funct_server_suc},
    {"sbp", funct_server_sbp},
};

typedef struct client_gui_s {
    const u_int8_t *comd;
    void (*handler)(u_int8_t **args);
} client_gui_t;

static const client_gui_t COMMAND_GESTION[] = {
    {"msz", funct_client_msz},
    {"mct", funct_client_mct},
    {"tna", funct_client_tna},
    {"ppo", funct_client_ppo},
    {"plv", funct_client_plv},
    {"pin", funct_client_pin},
    {"sgt", funct_client_sgt},
    {"sst", funct_client_sst},
};

#endif /* !GUI_H_ */
