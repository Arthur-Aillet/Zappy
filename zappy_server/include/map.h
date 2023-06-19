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
} tile_t;

typedef struct map_s {
    time_t start;
    double time;
    size_t width;
    size_t height;
    tile_t **tiles;
} map_t;

void update_map(map_t *map);

#endif /* !MAP_H_ */
