/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_look_ressources_one
*/

#include "zappy.h"

/**
 @brief check if there are thystame on the tile
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param int x: position x of tile
 @param int y: position y of tile
 @return void
**/
static void to_take_ressources_response_ia_thystame(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < C_RESSOURCES(y, x)[6]; j++) {
        SIZE += 9;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "thystame ");
    }
    SIZE = strlen(OCTETS) + 1;
    OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
    if (OCTETS[SIZE - 2] == ',') {
        SIZE += 1;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
    }
    OCTETS[SIZE - 2] = ',';
    OCTETS[SIZE - 1] = '\0';
}

/**
 @brief check if there are phiras on the tile
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param int x: position x of tile
 @param int y: position y of tile
 @return void
**/
static void to_take_ressources_response_ia_phiras(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < C_RESSOURCES(y, x)[5]; j++) {
        SIZE += 7;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "phiras ");
    }
    to_take_ressources_response_ia_thystame(ia, com, x, y);
}

/**
 @brief check if there are mendiane on the tile
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param int x: position x of tile
 @param int y: position y of tile
 @return void
**/
static void to_take_ressources_response_ia_mendiane(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < C_RESSOURCES(y, x)[4]; j++) {
        SIZE += 9;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "mendiane ");
    }
    to_take_ressources_response_ia_phiras(ia, com, x, y);
}

/**
 @brief check if there are sibur on the tile
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param int x: position x of tile
 @param int y: position y of tile
 @return void
**/
static void to_take_ressources_response_ia_sibur(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < C_RESSOURCES(y, x)[SIBUR]; j++) {
        SIZE += 6;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "sibur ");
    }
    to_take_ressources_response_ia_mendiane(ia, com, x, y);
}

/**
 @brief check if there are deraumere on the tile
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param int x: position x of tile
 @param int y: position y of tile
 @return void
**/
void to_take_ressources_response_ia_deraumere(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < C_RESSOURCES(y, x)[2]; j++) {
        SIZE += 10;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "deraumere ");
    }
    to_take_ressources_response_ia_sibur(ia, com, x, y);
}
