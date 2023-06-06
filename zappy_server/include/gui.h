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
    buffered_socket_t buffer;
    map_t map;
    error_handling_t *error; //FIXME - chaque protocole à sa propre error handlig ? ou on crrer une seul error handling (on devra rajouter un pointeur) ?
} gui_t;

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

void set_gui(gui_t *gui);
void free_gui(gui_t *gui);

#endif /* !GUI_H_ */
