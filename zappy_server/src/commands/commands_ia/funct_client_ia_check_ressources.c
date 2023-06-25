/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_check_ressources
*/

#include "zappy.h"

/**
 @brief check the resources it takes to get to level 7
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param common_t *com: the arguments receive with the command ia
 @param int x: position ressources x on the map
 @param int y: position ressources y on the map
 @return void
**/
static int to_check_ressources_six(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 7) {
        if (C_RESSOURCES(y, x)[1] > 1 &&
        C_RESSOURCES(y, x)[2] > 1 &&
        C_RESSOURCES(y, x)[3] > 1 &&
        C_RESSOURCES(y, x)[4] > 1 &&
        C_RESSOURCES(y, x)[5] > 1 &&
        C_RESSOURCES(y, x)[6] > 0) {
            update_density(&C_DENSITY[1], &C_RESSOURCES(y, x)[1], -2);
            update_density(&C_DENSITY[2], &C_RESSOURCES(y, x)[2], -2);
            update_density(&C_DENSITY[3], &C_RESSOURCES(y, x)[3], -2);
            update_density(&C_DENSITY[4], &C_RESSOURCES(y, x)[4], -2);
            update_density(&C_DENSITY[5], &C_RESSOURCES(y, x)[5], -2);
            update_density(&C_DENSITY[6], &C_RESSOURCES(y, x)[6], -1);
            return 0;
        }
    }
    return -1;
}

/**
 @brief check the resources it takes to get to level 6
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param common_t *com: the arguments receive with the command ia
 @param int x: position ressources x on the map
 @param int y: position ressources y on the map
 @return void
**/
static int to_check_ressources_five(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 6) {
        if (C_RESSOURCES(y, x)[1] > 0 &&
        C_RESSOURCES(y, x)[2] > 1 &&
        C_RESSOURCES(y, x)[3] > 2 &&
        C_RESSOURCES(y, x)[5] > 0) {
            update_density(&C_DENSITY[1], &C_RESSOURCES(y, x)[1], -1);
            update_density(&C_DENSITY[2], &C_RESSOURCES(y, x)[2], -2);
            update_density(&C_DENSITY[3], &C_RESSOURCES(y, x)[3], -3);
            update_density(&C_DENSITY[5], &C_RESSOURCES(y, x)[5], -1);
            return 0;
        }
    }
    return to_check_ressources_six(ia, com, x, y);
}

/**
 @brief check the resources it takes to get to level 5
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param common_t *com: the arguments receive with the command ia
 @param int x: position ressources x on the map
 @param int y: position ressources y on the map
 @return void
**/
static int to_check_ressources_four(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 5) {
        if (C_RESSOURCES(y, x)[1] > 0 &&
        C_RESSOURCES(y, x)[2] > 1 &&
        C_RESSOURCES(y, x)[3] > 0 &&
        C_RESSOURCES(y, x)[4] > 2) {
            update_density(&C_DENSITY[1], &C_RESSOURCES(y, x)[1], -1);
            update_density(&C_DENSITY[2], &C_RESSOURCES(y, x)[2], -2);
            update_density(&C_DENSITY[3], &C_RESSOURCES(y, x)[3], -1);
            update_density(&C_DENSITY[4], &C_RESSOURCES(y, x)[4], -3);
            return 0;
        }
    }
    return to_check_ressources_five(ia, com, x, y);
}

/**
 @brief check the resources it takes to get to level 4
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param common_t *com: the arguments receive with the command ia
 @param int x: position ressources x on the map
 @param int y: position ressources y on the map
 @return void
**/
static int to_check_ressources_tree(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 4) {
        if (C_RESSOURCES(y, x)[1] > 0 &&
        C_RESSOURCES(y, x)[2] > 0 &&
        C_RESSOURCES(y, x)[3] > 1 &&
        C_RESSOURCES(y, x)[5] > 0) {
            update_density(&C_DENSITY[1], &C_RESSOURCES(y, x)[1], -1);
            update_density(&C_DENSITY[2], &C_RESSOURCES(y, x)[2], -1);
            update_density(&C_DENSITY[3], &C_RESSOURCES(y, x)[3], -2);
            update_density(&C_DENSITY[5], &C_RESSOURCES(y, x)[5], -1);
            return 0;
        }
    }
    return to_check_ressources_four(ia, com, x, y);
}

/**
 @brief check the resources it takes to get to level 3
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param common_t *com: the arguments receive with the command ia
 @param int x: position ressources x on the map
 @param int y: position ressources y on the map
 @return void
**/
int to_check_ressources_bis(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 3) {
        if (C_RESSOURCES(y, x)[1] > 1 &&
        C_RESSOURCES(y, x)[3] > 0 &&
        C_RESSOURCES(y, x)[5] > 1) {
            update_density(&C_DENSITY[1], &C_RESSOURCES(y, x)[1], -2);
            update_density(&C_DENSITY[3], &C_RESSOURCES(y, x)[3], -1);
            update_density(&C_DENSITY[5], &C_RESSOURCES(y, x)[5], -2);
            return 0;
        }
    }
    return to_check_ressources_tree(ia, com, x, y);
}
