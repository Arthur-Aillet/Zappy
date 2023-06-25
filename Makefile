##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

all:
	make -C zappy_server all
	make -C zappy_gui all

clean:
	make -C zappy_server clean
	make -C zappy_gui clean

fclean:
	make -C zappy_server fclean
	make -C zappy_gui fclean

re: fclean all
