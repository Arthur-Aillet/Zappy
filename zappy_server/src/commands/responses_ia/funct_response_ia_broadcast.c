/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_broadcast
*/

#include <math.h>
#include "zappy.h"

//envoyer le message à tout les joueurs

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

static int calculate_broadcast_angle(ia_t *ia, player_t *player, map_t map)
{
    static int const idxes[3][3] = {{2, 1, 8},{3, 0, 7},{4, 5, 6}};
    float x = ia->player->x - player->x;
    float y = ia->player->y - player->y;

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

static void send_message_to_players(common_t *com, uint8_t **args, ia_t *ia)
{
    player_t *player;
    size_t buffer_size = 12;
    char *buffer;

    for (int i = 0; args[i] != NULL; i++)
        buffer_size += (strlen((char*)args[i]) + 1);
    buffer = malloc(sizeof(char) * buffer_size);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (com->client[i].type != IA)
            continue;
        player = (player_t*)com->client[i].str_cli;
        if (player->id == ia->player->id)
            continue;
        int k = calculate_broadcast_angle(ia, player, com->gui->map);
        sprintf(buffer, "message %d,", k);
        for (int j = 0; args[j] != NULL; j++) {
            printf(" %s", (char*)args[j]);
            strcat(buffer, " ");
            strcat(buffer, (char*)args[j]);
        }
        strcat(buffer, "\n");
        write(com->client[i].socket, buffer, strlen(buffer));
    }
    free(buffer);
}

void funct_response_ia_broadcast(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL)
        return;
    send_message_to_players(com, args, ia);
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
    basic_log("rentrer dans la fonctions funct_response_ia_broadcast", CYAN, 0);
}
