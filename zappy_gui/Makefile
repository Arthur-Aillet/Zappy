##
## EPITECH PROJECT, 2023
## Zappy Gui
## File description:
## Makefile
##

NAME = zappy_gui

all:
	cargo build --release
	mv ./target/release/$(NAME) .

re: fclean all

clean:
	cargo clean

fclean: clean
	rm -f $(NAME)

doc:
	cargo doc

doc-f:
	cargo doc
	firefox --new-window target/doc/rend_ox/index.html

.PHONY: all re clean fclean
