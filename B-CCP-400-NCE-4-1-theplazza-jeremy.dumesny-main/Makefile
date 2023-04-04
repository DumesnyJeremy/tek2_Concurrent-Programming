##
## EPITECH PROJECT, 2021
## plazza [WSL: Ubuntu]
## File description:
## Makefile
##

all:
			mkdir -p build
			cd build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && cmake --build . --config Release

debug:
			mkdir -p build
			cd build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug && cmake --build . --config Debug

clean:
			rm -rf build/

fclean: 	clean
			$(RM) plazza

re:			fclean all

.PHONY:		all clean fclean re