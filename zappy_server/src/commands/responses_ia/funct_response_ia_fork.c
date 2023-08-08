/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_fork
*/

#include "zappy.h"

/**
 @brief add new egg in the team
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param team_t *team: team structure
 @param ia_t *ia: the ia structure
 @return void
**/
static void to_add_new_egg(ia_t *ia, team_t *team)
{
    team->egg = realloc(team->egg, sizeof(egg_t) * (team->nb_eggs + 1));
    if (team->egg == NULL) {
        return;
    }
    team->egg[team->nb_eggs] = set_egg(ia->player->x, ia->player->y);
}

/**
 @brief prepare reponse for the ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param team_t *team: team structure
 @param ia_t *ia: the ia structure
 @return void
**/
static void funct_prepare_res(team_t *team, ia_t *ia)
{
    team->egg = realloc(team->egg, sizeof(egg_t) * (team->nb_eggs + 1));
    if (team->egg == NULL) {
        return;
    }
    to_add_new_egg(ia, team);
    team->nb_eggs += 1;
    team->nb_slot += 1;
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, "ok\n\0");
}

/**
 @brief create response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param int arg: argument to put in the response sent to the gui
 @return char *
**/
static char *create_args_for_response_gui(int arg)
{
    char *new_args;
    char buffer_args[256];

    sprintf(buffer_args, "%d", arg);
    new_args = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (new_args == NULL) {
        return NULL;
    }
    new_args[0] = '\0';
    strcat(new_args, buffer_args);
    return new_args;
}

/**
 @brief fork command response to ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the ia structure
 @return void
**/
void funct_response_ia_fork(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    team_t *team = to_find_team_by_int(ia->player->id, com);
    args = malloc(sizeof(char *) * 5);

    if (args == NULL || team == NULL)
        return;
    funct_prepare_res(team, ia);
    args[0] = create_args_for_response_gui(team->egg[team->nb_eggs - 1].egg_id);
    args[1] = create_args_for_response_gui(ia->player->id);
    args[2] = create_args_for_response_gui(ia->player->x);
    args[3] = create_args_for_response_gui(ia->player->y);
    args[4] = NULL;
    funct_server_enw(args, com->gui, com);
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    printf("%sPlayer %s%d%s lay an egg in %s%d %d%s\n", P, R, ia->player->id,
            P, B, ia->player->x, ia->player->y, N);
    free_array((void **)args);
}
