/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** zappy.h
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #include "ia.h"
    #include "gui.h"
    #include "teams.h"

typedef struct common_s {
    gui_t *gui;
    ia_t *ia;
    team_t *teams;
    size_t port;
    size_t freq; //NOTE: - time unit
} common_t;

common_t set_common(int ac, char *av[]);

#endif /* !ZAPPY_H_ */