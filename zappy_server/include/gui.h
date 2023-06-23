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

typedef struct common_s common_t;
typedef struct msg_queue_s msg_queue_t;

typedef struct gui_s {
    msg_queue_t *msg_queue;
    buffered_socket_t buffer;
    map_t map;
    error_handling_t *error;
} gui_t;

typedef struct client_gui_s {
    uint8_t *comd;
    uint8_t **args;
    void (*handler)(gui_t *gui, uint8_t **args, common_t *com);
} client_gui_t;

void funct_client_msz(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_bct(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_mct(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_tna(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_ppo(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_plv(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_pin(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_sgt(gui_t *gui, uint8_t **args, common_t *com);
void funct_client_sst(gui_t *gui, uint8_t **args, common_t *com);

static const client_gui_t COMMAND_GESTION_CLIENT_GUI[] = {
    {(uint8_t*)"msz", NULL, funct_client_msz},
    {(uint8_t*)"bct", NULL, funct_client_bct},
    {(uint8_t*)"mct", NULL, funct_client_mct},
    {(uint8_t*)"tna", NULL, funct_client_tna},
    {(uint8_t*)"ppo", NULL, funct_client_ppo},
    {(uint8_t*)"plv", NULL, funct_client_plv},
    {(uint8_t*)"pin", NULL, funct_client_pin},
    {(uint8_t*)"sgt", NULL, funct_client_sgt},
    {(uint8_t*)"sst", NULL, funct_client_sst},
};

gui_t *set_gui(int height, int wigth, int freq);
void free_gui(gui_t *gui);
void update_density(size_t *density, size_t *ressources, int value);
void check_msg_queue_gui(common_t *com);

void funct_prepare_response(gui_t *gui, size_t x, size_t y);

#endif /* !GUI_H_ */
