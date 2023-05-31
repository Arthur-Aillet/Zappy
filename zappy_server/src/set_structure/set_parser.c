/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_parser.c
*/

#include "parser.h"
#include <stdlib.h>

parser_t *set_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t));
    parser->teams_name = NULL;
    parser->client_nb = 0;
    parser->port = 0;
    parser->freq = 100;
    parser->height = 10;
    parser->width = 10;

    return parser;
}