/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** gui
*/

#ifndef GUI_H_
    #define GUI_H_
    #define GUI_OCTETS          gui->buffer.bufferWrite.octets
    #define GUI_SIZE            gui->buffer.bufferWrite.usedSize

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
    char *comd;
    char **args;
    void (*handler)(gui_t *gui, char **args, common_t *com);
} client_gui_t;

void funct_client_msz(gui_t *gui, char **args, common_t *com);
void funct_client_bct(gui_t *gui, char **args, common_t *com);
void funct_client_mct(gui_t *gui, char **args, common_t *com);
void funct_client_tna(gui_t *gui, char **args, common_t *com);
void funct_client_ppo(gui_t *gui, char **args, common_t *com);
void funct_client_plv(gui_t *gui, char **args, common_t *com);
void funct_client_pin(gui_t *gui, char **args, common_t *com);
void funct_client_sgt(gui_t *gui, char **args, common_t *com);
void funct_client_sst(gui_t *gui, char **args, common_t *com);

static const client_gui_t COMMAND_GESTION_CLIENT_GUI[] = {
    {"msz", NULL, funct_client_msz},
    {"bct", NULL, funct_client_bct},
    {"mct", NULL, funct_client_mct},
    {"tna", NULL, funct_client_tna},
    {"ppo", NULL, funct_client_ppo},
    {"plv", NULL, funct_client_plv},
    {"pin", NULL, funct_client_pin},
    {"sgt", NULL, funct_client_sgt},
    {"sst", NULL, funct_client_sst},
};

gui_t *set_gui(int height, int wigth, int freq);
void free_gui(gui_t *gui);
void update_density(size_t *density, size_t *ressources, int value);
void check_msg_queue_gui(common_t *com);

void funct_prepare_response(gui_t *gui, size_t x, size_t y);

#endif /* !GUI_H_ */
