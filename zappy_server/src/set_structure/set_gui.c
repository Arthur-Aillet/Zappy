/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_gui.c
*/

#include "gui.h"
#include <stdlib.h>
#include <string.h>
#include "error_handling.h"

static size_t *set_ressources(void)
{
    size_t *resources = malloc(sizeof(size_t) * 8);
    if (resources == NULL)
        exit(error("Failed to allocate resources for a tile", 84));
    for (int i = 0; i < 8; i++)
        resources[i] = 0;
    return resources;
}

static map_t set_map(int height, int width, int freq)
{
    map_t map;
    map.height = height;
    map.width = width;
    map.start = time(NULL);
    map.time = 20 / freq;
    map.tiles = malloc(sizeof(tile_t *) * height);
    if (map.tiles == NULL)
        exit(error("Failed to allocate tiles map", 84));
    for (int i = 0; i < height; i++) {
        map.tiles[i] = malloc(sizeof(tile_t) * width);
        if (map.tiles == NULL)
            exit(error("Failed to allocate tiles map", 84));
        for (int j = 0; j < width; j++) {
            map.tiles[i][j].ressources = set_ressources();
        }
    }
    return map;
}

gui_t *set_gui(int height, int width, int freq)
{
    gui_t *gui = malloc(sizeof(gui_t));
    gui->map = set_map(height, width, freq);
    return gui;
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

void free_gui(gui_t *gui)
{
    free_map(&gui->map);
    basic_log("Map free", BLUE, 0);
    free(gui);
    basic_log("GUI free", BLUE, 0);
}