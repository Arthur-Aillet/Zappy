/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** gui
*/

#ifndef GUI_H_
    #define GUI_H_

    #include "map.h"
    #include "common.h"

typedef struct gui_s {
    msg_queue_t *msg_queue;
    map_t map;
    error_handling_t *error; //FIXME - chaque protocole à sa propre error handlig ? ou on crrer une seul error handling (on devra rajouter un pointeur) ?
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
    void (*handler)(gui_t *gui);
} client_gui_t;

void funct_client_msz(gui_t *gui);
void funct_client_mct(gui_t *gui);
void funct_client_tna(gui_t *gui);
void funct_client_ppo(gui_t *gui);
void funct_client_plv(gui_t *gui);
void funct_client_pin(gui_t *gui);
void funct_client_sgt(gui_t *gui);
void funct_client_sst(gui_t *gui);

static const client_gui_t COMMAND_GESTION_CLIENT_GUI[] = {
    {"msz", funct_client_msz},
    {"mct", funct_client_mct},
    {"tna", funct_client_tna},
    {"ppo", funct_client_ppo},
    {"plv", funct_client_plv},
    {"pin", funct_client_pin},
    {"sgt", funct_client_sgt},
    {"sst", funct_client_sst},
};

gui_t *set_gui(void);

#endif /* !GUI_H_ */
