/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_inventory
*/

#include "zappy.h"

/**
 @brief check phiras on the inventory of ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: the ia structure
 @return void
**/
static void inventory_phiras(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[PHIRAS]);
    SIZE += 10 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "phiras ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, ", ");
}

/**
 @brief check thystame on the inventory of ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: the ia structure
 @return void
**/
static void inventory_thystame(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[THYSTAME]);
    SIZE += 12 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "thystame ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, ", ");
}

/**
 @brief check egg on the inventory of ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: the ia structure
 @return void
**/
static void inventory_egg(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[EGG]);
    SIZE += 7 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "egg ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, "]\n\0");
    SIZE = strlen(OCTETS);
}

/**
 @brief prepare reponse for the ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: the ia structure
 @return void
**/
static void funct_result_response_ia_inventory(ia_t *ia)
{
    OCTETS = realloc(OCTETS, sizeof(char));
    OCTETS[0] = '\0';
    inventory_food(ia);
    inventory_linemate(ia);
    inventory_deraumere(ia);
    inventory_sibur(ia);
    inventory_mendiane(ia);
    inventory_phiras(ia);
    inventory_thystame(ia);
    inventory_egg(ia);
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
}

/**
 @brief inventory command response to ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the ia structure
 @return void
**/
void funct_response_ia_inventory(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    (void)args;
    (void)com;
    funct_result_response_ia_inventory(ia);
    basic_log("Check his inventory", C, 0);
}
