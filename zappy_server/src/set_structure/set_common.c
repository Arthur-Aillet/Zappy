/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_common.c
*/

#include "zappy.h"
#include "parser.h"

common_t set_common(int ac, char *av[])
{
    parser_t *parser = set_parser();
    get_parameters(ac, av, parser);
    common_t com;
    com.gui = set_gui();
    com.ia = set_ia();

    for (size_t i = 0; i < parser->nb_teams; i++)
        com.teams[i] = (uint8_t)set_team(parser->teams_name[i], parser->client_nb);
    com.port = parser->port;
    com.freq = parser->freq;

    free(parser);
    return com;
}
