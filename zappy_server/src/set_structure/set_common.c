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
    if ((server->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Couldn't create server socket\n");
        return 0;
    }
    set_sockaddr(server, port);
    server->maxsd = server->socket;
    if (bind(server->socket, (struct sockaddr *)&server->addr,
    server->size) < 0) {
        fprintf(stderr, "Couldn't bind: You must used a good port\n");
        return 0;
    }
    if (listen(server->socket, MAX_CLIENTS) < 0) {
        fprintf(stderr, "Couldn't listen\n");
        return 0;
    }
    FD_ZERO(&server->read_fd);
    FD_SET(server->socket, &server->read_fd);
    return 1;
}

common_t set_common(int ac, char *av[])
{
    parser_t *parser = set_parser();
    get_parameters(ac, av, parser);
    common_t com;
    com.gui = set_gui();
    com.ia = set_ia();
    com.teams = malloc(sizeof(team_t) * parser->nb_teams);
    for (size_t i = 0; i < parser->nb_teams; i++)
        com.teams[i] = set_team(parser->teams_name[i], parser->client_nb);
    com.port = parser->port;
    com.freq = parser->freq;
    com.client = set_clients(com.client);
    com.nb_teams = parser->nb_teams;
    if (!set_server(com.port, &com.server)) { //FIXME - if != 1
        free(parser);
        free_common(&com);
        exit(84);
    }
    free(parser);
    return com;
}

void free_common(common_t *com)
{
    free_clients(com->client, &com->server);
    free_all_teams(com->teams, com->nb_teams);
    free_gui(com->gui);
    free_ia(com->ia);
}
