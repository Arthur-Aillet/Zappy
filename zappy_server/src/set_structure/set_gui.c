/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_gui.c
*/

#include "gui.h"
#include <stdlib.h>
#include <string.h>

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

void set_gui(gui_t *gui)
{
    gui = malloc(sizeof(gui_t));
    gui->map = set_map(0, 0);
}

static void free_map(map_t *map)
{
    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            free(map->tiles[i][j].ressources);
        }
        free(map->tiles[i]);
    }
    free(map->tiles);
}

//FIXME - segmentation fault when we could free the map
void free_gui(gui_t *gui)
{
    // free_map(&gui->map);
}