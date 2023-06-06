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
    #include "error_handling.h"

typedef struct gui_s {
    msg_queue_t *msg_queue;
    map_t map;
    error_handling_t *error; //FIXME - chaque protocole à sa propre error handlig ? ou on crrer une seul error handling (on devra rajouter un pointeur) ?
} gui_t;

void funct_server_msz(uint8_t **args, gui_t *gui);
void funct_server_bct(uint8_t **args, gui_t *gui);
void funct_server_all_bct(uint8_t **args, gui_t *gui);
void funct_server_tna(uint8_t **args, gui_t *gui);
void funct_server_pnw(uint8_t **args, gui_t *gui);
void funct_server_ppo(uint8_t **args, gui_t *gui);
void funct_server_plv(uint8_t **args, gui_t *gui);
void funct_server_pin(uint8_t **args, gui_t *gui);
void funct_server_pex(uint8_t **args, gui_t *gui);
void funct_server_pbc(uint8_t **args, gui_t *gui);
void funct_server_pic(uint8_t **args, gui_t *gui);
void funct_server_pie(uint8_t **args, gui_t *gui);
void funct_server_pfk(uint8_t **args, gui_t *gui);
void funct_server_pdr(uint8_t **args, gui_t *gui);
void funct_server_pgt(uint8_t **args, gui_t *gui);
void funct_server_pdi(uint8_t **args, gui_t *gui);
void funct_server_enw(uint8_t **args, gui_t *gui);
void funct_server_ebo(uint8_t **args, gui_t *gui);
void funct_server_edi(uint8_t **args, gui_t *gui);
void funct_server_sgt(uint8_t **args, gui_t *gui);
void funct_server_sst(uint8_t **args, gui_t *gui);
void funct_server_seg(uint8_t **args, gui_t *gui);
void funct_server_smg(uint8_t **args, gui_t *gui);
void funct_server_suc(uint8_t **args, gui_t *gui);
void funct_server_sbp(uint8_t **args, gui_t *gui);

typedef struct client_gui_s {
    const uint8_t *comd;
    uint8_t **args;
    void (*handler)(gui_t *gui, uint8_t **args);
} client_gui_t;

void funct_client_msz(gui_t *gui, uint8_t **args);
void funct_client_bct(gui_t *gui, uint8_t **args);
void funct_client_mct(gui_t *gui, uint8_t **args);
void funct_client_tna(gui_t *gui, uint8_t **args);
void funct_client_ppo(gui_t *gui, uint8_t **args);
void funct_client_plv(gui_t *gui, uint8_t **args);
void funct_client_pin(gui_t *gui, uint8_t **args);
void funct_client_sgt(gui_t *gui, uint8_t **args);
void funct_client_sst(gui_t *gui, uint8_t **args);

static const client_gui_t COMMAND_GESTION_CLIENT_GUI[] = {
    {"msz", funct_client_msz},
    {"bct", funct_client_bct},
    {"mct", funct_client_mct},
    {"tna", funct_client_tna},
    {"ppo", funct_client_ppo},
    {"plv", funct_client_plv},
    {"pin", funct_client_pin},
    {"sgt", funct_client_sgt},
    {"sst", funct_client_sst},
};

gui_t set_gui(int height, int wigth, int freq);
void free_gui(gui_t *gui);

#endif /* !GUI_H_ */
