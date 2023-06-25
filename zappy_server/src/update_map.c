/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update_map.c
*/

#include "zappy.h"
#include "error_handling.h"
#include <stdlib.h>

void update_density(size_t *density, size_t *ressources, int value)
{
    *density = (*density + value > 0) ? *density + value : 0;
    *ressources = (*ressources + value > 0) ? *ressources + value : 0;
}

static size_t *new_ressource(int height, int width)
{
    size_t *resources = malloc(sizeof(size_t) * 7);

    if (!resources)
        return NULL;
    resources[FOOD] = height * width * 0.5;
    resources[LINEMATE] = height * width * 0.3;
    resources[DERAUMERE] = height * width * 0.15;
    resources[SIBUR] = height * width * 0.1;
    resources[MENDIANE] = height * width * 0.1;
    resources[PHIRAS] = height * width * 0.08;
    resources[THYSTAME] = height * width * 0.05;
    return resources;
}

static void random_resource_position(map_t *map, int resource)
{
    int x = rand() % map->height;
    int y = rand() % map->width;

    map->tiles[x][y].ressources[resource]++;
}

static void update_tiles_ressources(map_t *map)
{
    size_t *resources = new_ressource(map->height, map->width);

    for (int i = 0; i < 7; i++) {
        if (resources[i] < map->density[i])
            continue;
        resources[i] -= map->density[i];
        while (resources[i] > 0) {
            random_resource_position(map, i);
            resources[i]--;
            map->density[i]++;
        }
    }
    free(resources);
}

void update_map(common_t *com)
{
    time_t now = time(NULL);


    if (difftime(now, com->gui->map.start) >= com->gui->map.time) {
        com->gui->map.start = time(NULL);
        update_tiles_ressources(&com->gui->map);
        funct_server_all_bct(NULL, com->gui, NULL);
        if (com->gui->map.time >= 0.5)
            basic_log("update map resources", G, 0);
    }
}
