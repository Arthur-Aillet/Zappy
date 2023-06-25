/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_parser.c
*/

#include "parser.h"
#include <stdlib.h>
#include "error_handling.h"
#include "common.h"

parser_t *set_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t));

    parser->teams_name = NULL;
    parser->nb_teams = 0;
    parser->client_nb = 2;
    parser->port = 4242;
    parser->freq = 100;
    parser->height = 10;
    parser->width = 10;

    return parser;
}

void free_parser(parser_t *parser)
{
    free(parser->teams_name);
    free(parser);
    basic_log("Free parser", B, 0);
}
