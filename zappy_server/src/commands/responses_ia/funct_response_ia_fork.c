/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_fork
*/

#include "zappy.h"

static void to_add_new_egg(ia_t *ia, team_t *team)
{
    team->egg = realloc(team->egg, sizeof(egg_t) * (team->nb_eggs + 1));
    if (team->egg == NULL) {
        return;
    }
    team->egg[team->nb_eggs] = set_egg(ia->player->x, ia->player->y);
}

static void funct_prepare_res(team_t *team, ia_t *ia)
{
    team->egg = realloc(team->egg, sizeof(egg_t) * (team->nb_eggs + 1));
    if (team->egg == NULL) {
        return;
    }
    to_add_new_egg(ia, team);
    team->nb_eggs += 1;
    team->nb_slot += 1;
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(char) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
}

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

void funct_response_ia_fork(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    team_t *team = to_find_team_by_int(ia->player->id, com);
    char **arg = malloc(sizeof(char *) * 4);

    (void)args;
    (void)com;
    if (arg == NULL || team == NULL) {
        return;
    }
    funct_prepare_res(team, ia);
    arg[0] = create_args_for_response_gui(team->egg[team->nb_eggs - 1].egg_id);
    arg[1] = create_args_for_response_gui(ia->player->id);
    arg[2] = create_args_for_response_gui(ia->player->x);
    arg[3] = create_args_for_response_gui(ia->player->y);
    funct_server_enw(arg, com->gui, com);
    free_arg(4, arg);
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
    printf("Lay an egg\n");
}
