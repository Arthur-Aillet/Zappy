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
    #include "team.h"

typedef struct common_s {
    gui_t *gui;
    ia_t *ia;
    uint8_t *teams;
    size_t port;
    size_t freq; //NOTE: - time unit
} common_t;

#endif /* !ZAPPY_H_ */