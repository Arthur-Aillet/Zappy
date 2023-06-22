/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** map.h
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "common.h"

    #include <stdio.h>

typedef struct tile_s {
    size_t *ressources;
    size_t *nb_player_incantations;
} tile_t;

typedef struct map_s {
    time_t start;
    double time;
    size_t width;
    size_t height;
    tile_t **tiles;
    size_t *density;
} map_t;

#endif /* !MAP_H_ */
