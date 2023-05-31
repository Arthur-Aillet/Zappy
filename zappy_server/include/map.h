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
    size_t width;
    size_t height;
} map_t;

#endif /* !MAP_H_ */
