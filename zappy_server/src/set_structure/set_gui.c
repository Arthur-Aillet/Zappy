/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_gui.c
*/

#include "gui.h"

static map_t set_map(int height, int width)
{
    map_t map;
    map.height = height;
    map.width = width;
    map.tiles = malloc(sizeof(tile_t *) * height);
    for (int i = 0; i < height; i++) {
        map.tiles[i] = malloc(sizeof(tile_t) * width);
        for (int j = 0; j < width; j++) {
            memset(map.tiles[i][j].ressources, 0, 8);
        }
    }
    return map;
}

gui_t *set_gui(void)
{
    gui_t *gui = malloc(sizeof(gui_t));
    return gui;
}