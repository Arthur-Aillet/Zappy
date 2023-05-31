/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main
*/

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>

//FIXME - create getopt for revcover arguments


static void getparameters(int ac, char *av[])
{
    parser_t *parser = set_parser();
    int opt;
    int nbr_teams_name = 0;

    while ((opt = getopt(ac, av, "p:x:y:n:c:f:")) != -1) {
        switch (opt) {
            case 'p': printf("p\n");
                    sscanf(optarg, "%zu", &parser->port);
                    break;
            case 'x': printf("x\n");
                    sscanf(optarg, "%zu", &parser->width);
                    break;
            case 'y': sscanf(optarg, "%zu", &parser->height);
                    printf("y\n");
                    break;
            case 'c': sscanf(optarg, "%zu", &parser->client_nb);
                    printf("c\n");
                    break;
            case 'f': sscanf(optarg, "%zu", &parser->freq);
                    printf("f\n");
                    break;
            case 'n':
                    printf("n\n");
                    parser->teams_name = malloc((ac - optind + 1) * sizeof(char*)); // Allouer de la mémoire pour les noms d'équipe
                    parser->teams_name[nbr_teams_name] = av[optind - 1];
                    nbr_teams_name++;
                    while (optind < ac && av[optind][0] != '-') {
                        parser->teams_name[nbr_teams_name] = av[optind];
                        nbr_teams_name++;
                        optind++;
                    }
                    parser->teams_name[nbr_teams_name] = NULL;
                    break;
            default:
                fprintf(stderr, "\e[1;31mInvalid option!!\n\e[0;m");
                exit(84);
        }
    }
    if (parser->port == 0 || parser->height == 0 || parser->width == 0
    || parser->client_nb == 0 || parser->freq == 0) {
        fprintf(stderr, "Bad argument for one flag.\n");
        exit(84);
    }
    printf("port: %ld || height: %ld || width: %ld\n", parser->port, parser->height, parser->width);
    printf("client_nb: %ld || freq: %ld\n", parser->client_nb, parser->freq);
    for (int i = 0; i < nbr_teams_name; i++) {
        printf("%s ", parser->teams_name[i]);
    }
    free(parser);
}

// static void set_new_loop(void)
// {
// }

int main(int ac, char *av[])
{
    getparameters(ac, av);
    // while (1) {
    //     set_new_loop();
    //     if (/* select(MAX_SD, READ_FDS, NULL, NULL, NULL) < 0*/) {
    //         exit(84);
    //     }
    //     listening_sockets();
    // }
    return (0);
}
