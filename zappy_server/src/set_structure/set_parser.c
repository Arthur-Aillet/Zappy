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

/**
 * @brief Set structure parser_t
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param void
 * @return parser_t *
*/
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

/**
 * @brief Free the strucutur parser
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param parser_t *parser:
 * @param int width: the width of the map
 * @param int freq: the frequency of all actions of ia
 * @return gui_t *
*/
void free_parser(parser_t *parser)
{
    free(parser->teams_name);
    free(parser);
    basic_log("Free parser", B, 0);
}
