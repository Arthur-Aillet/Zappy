/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** funct_response_ia_broadcast_bis.c
*/

#include <math.h>
#include "zappy.h"

static void orientation_vector(player_t *player, float *x, float *y)
{
    switch (player->orientation) {
    case Est:
        *y = *x;
        *x = *y;
        break;
    case Sud:
        *y = -(*y);
        break;
    case West:
        *x = *y;
        *y = -(*x);
        break;
    default:
        break;
    }
}

static void normalizing_vector(float *x, float *y)
{
    float tang = sqrt(pow((*x), 2) + pow((*y), 2));
    *x = *x / tang;
    *y = *y / tang;
}

static int calc_angle(ia_t *ia, player_t *player, map_t map)
{
    static int const idxes[3][3] = {{2, 1, 8},{3, 0, 7},{4, 5, 6}};
    float x = ia->player->x - player->x;
    float y = ia->player->y - player->y;
    if (ia->player->x == player->x && ia->player->y == player->y)
        return idxes[1][1];
    x = (x < 0) ? x + map.width : x;
    x = (x > map.width / 2) ? x - map.width : x;
    y = (y < 0) ? y + map.height : y;
    y = (y > map.height / 2) ? y - map.height : y;
    normalizing_vector(&x, &y);
    orientation_vector(player, &x, &y);

    x = (2 * x > 1) ? 1 : x;
    x = (2 * x < -1) ? -1 : x;
    y = (2 * y < -1) ? -1 : y;
    y = (2 * y > 1) ? 1 : y;
    x++;
    y++;
    return idxes[(int)x][(int)y];
}

static size_t calculate_buffer_size(ia_t *ia, char **args)
{
    char buf[256];
    size_t buffer_size;

    sprintf(buf,"%d", ia->player->id);
    buffer_size = 12 + strlen(buf);
    for (int i = 0; args[i] != NULL; i++)
        buffer_size += (strlen(args[i]) + 1);
    return buffer_size;
}

void send_message_to_player(common_t *com, ia_t *ia, int i, char **args)
{
    player_t *player;
    char *buffer = malloc(sizeof(char) * calculate_buffer_size(ia, args));

    if (com->client[i].type == UNDEFINED)
            return;
    if (com->client[i].type == IA) {
        player = (player_t*)com->client[i].str_cli;
        if (player->id == ia->player->id)
            return;
        sprintf(buffer, "message %d,", calc_angle(ia, player, com->gui->map));
    } else
        sprintf(buffer, "pbc %d", ia->player->id);
    for (int j = 0; args[j] != NULL; j++) {
        strcat(buffer, " ");
        strcat(buffer, args[j]);
    }
    strcat(buffer, "\n");
    write(com->client[i].socket, buffer, strlen(buffer));
    free(buffer);
}
