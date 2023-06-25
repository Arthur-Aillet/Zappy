/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parser.c
*/

#include "parser.h"

#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>


static void set_teams_name(parser_t *p, int ac, char *av[])
{
    p->teams_name = malloc((ac - optind + 2) * sizeof(char*));
    p->teams_name[p->nb_teams] = av[optind - 1];
    p->nb_teams++;
    while (optind < ac && av[optind][0] != '-') {
        p->teams_name[p->nb_teams] = av[optind];
        p->nb_teams++;
        optind++;
    }
    p->teams_name[p->nb_teams] = NULL;
}

static void get_one_parametes(parser_t *p, int opt, int ac, char *av[])
{
    switch (opt) {
        case 'p':
                sscanf(optarg, "%zu", &p->port);
                break;
        case 'x':
                sscanf(optarg, "%zu", &p->width);
                break;
        case 'y': sscanf(optarg, "%zu", &p->height);
                break;
        case 'c': sscanf(optarg, "%zu", &p->client_nb);
                break;
        case 'f': sscanf(optarg, "%zu", &p->freq);
                break;
        case 'n':
                set_teams_name(p, ac, av);
                break;
        default:
            fprintf(stderr, "\e[1;31mInvalid option!!\n\e[0;m");
            exit(84);
    }
}

static void default_teams(parser_t *parser)
{
    parser->nb_teams = 4;
    parser->teams_name = malloc(sizeof(char *) * (parser->nb_teams + 1));
    parser->teams_name[0] = "Team1";
    parser->teams_name[1] = "Team2";
    parser->teams_name[2] = "Team3";
    parser->teams_name[3] = "Team4";
    parser->teams_name[4] = NULL;
}

void get_parameters(int ac, char *av[], parser_t *parser)
{
    int opt;

    while ((opt = getopt(ac, av, "p:x:y:n:c:f:")) != -1)
        get_one_parametes(parser, opt, ac, av);
    if (parser->nb_teams == 0)
        default_teams(parser);
    if (parser->port == 0 || parser->height == 0 || parser->width == 0
        || parser->client_nb == 0 || parser->freq == 0) {
        fprintf(stderr, "Bad argument for one flag.\n");
        exit(84);
    }
}
