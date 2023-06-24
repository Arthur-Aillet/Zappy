/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_common.c
*/

#include "zappy.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>

static void set_sockaddr(server_t *server, int port)
{
    int flag = fcntl(server->socket, F_GETFL, 0);

    fcntl(server->socket,F_SETFL, flag | O_NONBLOCK);
    bzero(&server->addr, sizeof(server->addr));
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(port);
    server->size = sizeof(server->addr);
}

static int set_server(int port, server_t *server)
{
    if ((server->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return error("Couldn't create server socket", 0);
    printf("%sServer socket created%s\n", G, N);
    set_sockaddr(server, port);
    server->maxsd = server->socket;
    if (bind(server->socket, (struct sockaddr *)&server->addr,
    server->size) < 0)
        return error("Couldn't bind: Use a good port", 0);
    printf("%sServer bind%s\n", G, N);
    if (listen(server->socket, MAX_CLIENTS) < 0)
        return error("Couldn't listen", 0);
    printf("%sServer listen port%s %d%s\n", G, B, port, N);
    FD_ZERO(&server->read_fd);
    FD_SET(server->socket, &server->read_fd);
    return 1;
}

static void set_structures(common_t *com, parser_t *parser)
{
    com->teams = malloc(sizeof(team_t) * parser->nb_teams);
    for (size_t i = 0; i < parser->nb_teams; i++)
        com->teams[i] = set_team(parser->teams_name[i],
                        parser->client_nb, parser->freq);
    com->client = set_all_clients();
    com->gui = set_gui(parser->height, parser->width, parser->freq);
    com->ia = set_ia();
    if (!set_server(com->port, &com->server)) {
        free_parser(parser);
        free_common(com);
        exit(84);
    }
}

common_t set_common(int ac, char *av[])
{
    common_t com;
    parser_t *parser = set_parser();

    get_parameters(ac, av, parser);
    com.port = parser->port;
    com.freq = parser->freq;
    com.nb_teams = parser->nb_teams;
    com.timer = time(NULL);
    com.nb_ia = 0;
    set_structures(&com, parser);
    free_parser(parser);
    return com;
}

void free_common(common_t *com)
{
    free_gui(com->gui);
    for (int i = 0; i < MAX_CLIENTS; i++)
        free_ia(&com->ia[1]);
    free_all_teams(com->teams, com->nb_teams);
    free_clients(com->client, &com->server);
}
