/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parser.h
*/

#ifndef PARSER_H_
    #define PARSER_H_
    #include <stdio.h>

typedef struct parser_s {
    size_t port;
    size_t height;
    size_t width;
    size_t client_nb;
    size_t freq;
    char **teams_name;
} parser_t;

parser_t *set_parser(void);

#endif /* !PARSER_H_ */