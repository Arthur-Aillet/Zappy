/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** my_str_to_word_array
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int nb_word(char *str, char c)
{
    int i = 0;

    for (int e = 0; str[e] != '\0'; e++)
        if (str[e] == c)
            i++;
    i++;
    return i;
}

static char *my_strncpy2(int count, int start, char *str, int size_arg)
{
    int i = 0;
    char *dest = malloc(sizeof(char) * (count + size_arg + 3));

    if (dest == NULL)
        return NULL;
    for (i = 0; i < count; i++) {
        dest[i] = str[start];
        start++;
    }
    dest[i] = '\0';
    return dest;
}

char **my_str_to_word_array(char *str, char **seg, char c)
{
    size_t i = 0;
    int d = 0;
    int count = 0;
    int start = 0;
    seg = malloc(sizeof(char *) * (nb_word(str, c) + 3));
    if (seg == NULL)
        return NULL;
    for (; i <= strlen(str); i++) {
        count++;
        if ((str[i] == c || str[i] == '\0')) {
            seg[d] = my_strncpy2((count - 1), start, str, 0);
            count = 1;
            start = (i += 1);
            d++;
        }
    }
    seg[d] = NULL;
    if (d == 1)
        seg[d + 1] = NULL;
    return seg;
}

void free_array(void **arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}
