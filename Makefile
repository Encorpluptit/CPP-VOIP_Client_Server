##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

################################################################################
# Config Vars

NAME					=	babel


# Client
CLIENT_BIN				=	babel_client

CLIENT_DIR				=	client

CLIENT_BUILD_DIR		=	.babel_client_build


# Server
SERVER_BIN				=	babel_server

SERVER_DIR				=	server

SERVER_BUILD_DIR		=	.babel_server_build


MOULI_BUILD_DIR			=	build

################################################################################
.DEFAULT: all

all: $(NAME)

$(NAME): server client

log: OPTIONS +=-DUSE_LOG=ON
log: $(NAME)

debug: OPTIONS +=-DUSE_DEBUG=ON
debug: $(NAME)


################################################################################
# SERVER RULES
server:
	@mkdir -p $(SERVER_BUILD_DIR)
	@cmake $(OPTIONS) -B $(SERVER_BUILD_DIR)
	@$(MAKE) -j `nproc` --no-print-directory -C $(SERVER_BUILD_DIR)

server_clean:
	@$(RM) -r $(SERVER_BUILD_DIR)

server_fclean:
	@$(RM) -r $(SERVER_BIN)



################################################################################
# CLIENTS RULES
client:
	@mkdir -p $(CLIENT_BUILD_DIR)
	@cmake $(OPTIONS) -B $(CLIENT_BUILD_DIR)
	@$(MAKE) -j `nproc` --no-print-directory -C $(CLIENT_BUILD_DIR)

client_clean:
	@$(RM) -r $(CLIENT_BUILD_DIR)

client_fclean:
	@$(RM) -r $(CLIENT_BIN)



################################################################################
# OTHERS RULES

mouli:
	#mkdir -p build && cd build && conan install .. && cmake .. && cmake –build .
	mkdir -p $(MOULI_BUILD_DIR) && cd $(MOULI_BUILD_DIR) && cmake .. && cmake –build .

clean: server_clean client_clean

fclean: clean server_fclean client_fclean
	@$(RM) -r $(MOULI_BUILD_DIR)

tests_run:

re: fclean all

.PHONY: all $(NAME) server client tests_run mouli
.PHONY: server_clean server_fclean client_clean client_fclean clean fclean re
