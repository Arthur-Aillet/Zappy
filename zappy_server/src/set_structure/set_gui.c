/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_gui.c
*/

#include <stdlib.h>
#include <string.h>
#include "zappy.h"

/**
 * @brief Set tthe array of possible ressources for one tiles of the map
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param void
 * @return size_t *
*/
static size_t *set_ressources(void)
{
    size_t *resources = malloc(sizeof(size_t) * 7);
    if (resources == NULL)
        exit(error("Failed to allocate resources for a tile", 84));
    for (int i = 0; i < 7; i++)
        resources[i] = 0;
    return resources;
}

/**
 * @brief Set the map structure and all these values
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param int height: the height of the map
 * @param int width: the width of the map
 * @param int freq: the frequency of all actions of ia
 * @return map_t
*/
static map_t set_map(int height, int width, int freq)
{
    map_t map;

    map.height = height;
    map.width = width;
    map.start = time(NULL);
    map.time = (double)(20. / (double)freq);
    map.tiles = malloc(sizeof(tile_t *) * height);
    map.density = (size_t*)calloc(7, sizeof(size_t));
    if (map.tiles == NULL)
        exit(error("Failed to allocate tiles map", 84));
    for (int i = 0; i < height; i++) {
        map.tiles[i] = malloc(sizeof(tile_t) * width);
        if (map.tiles == NULL)
            exit(error("Failed to allocate tiles map", 84));
        for (int j = 0; j < width; j++) {
            map.tiles[i][j].ressources = set_ressources();
            map.tiles[i][j].nb_player_incantations = set_ressources();
        }
    }
    return map;
}

/**
 * @brief Set the gui_t structure and all these values
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param int height: the height of the map
 * @param int width: the width of the map
 * @param int freq: the frequency of all actions of ia
 * @return gui_t *
*/
gui_t *set_gui(int height, int width, int freq)
{
    gui_t *gui = malloc(sizeof(gui_t));

    gui->map = set_map(height, width, freq);
    gui->buffer.bufferRead.octets = NULL;
    gui->buffer.bufferRead.usedSize = 0;
    GUI_OCTETS = NULL;
    GUI_SIZE = 0;
    gui->buffer.sock.sockfd = 0;
    gui->msg_queue = NULL;
    gui->error = NULL;
    return gui;
}

/**
 * @brief Free the map of the game
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param map_t *map: The map to free
 * @return void
*/
static void free_map(map_t *map)
{
    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            free(map->tiles[i][j].ressources);
            free(map->tiles[i][j].nb_player_incantations);
        }
        free(map->tiles[i]);
    }
    free(map->tiles);
    free(map->density);
}

//FIXME - free message queue
/**
 * @brief Free the structure gui_t*
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param gui_t *gui: contain all specified data for the graphique
 * @return void
*/
void free_gui(gui_t *gui)
{
    free_msg_queue(gui->msg_queue);
    free_map(&gui->map);
    basic_log("Map free", B, 0);
    if (gui->buffer.bufferRead.octets != NULL)
        free(gui->buffer.bufferRead.octets);
    free(gui);
    basic_log("GUI free", B, 0);
}
