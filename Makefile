##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

################################################################################
# Config Vars
NAME					=	babel

BUILD_DIR				=	.build


#################################################
# Client
CLIENT_BIN				=	babel_client

CLIENT_DIR				=	client


#################################################
# Server
SERVER_BIN				=	babel_server

SERVER_DIR				=	server

#################################################
# Tests
CRITERION_BIN			=	unit_tests


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
	@cmake $(OPTIONS) -B $(BUILD_DIR)
	@$(MAKE) -j `nproc` --no-print-directory -C $(BUILD_DIR) $(SERVER_BIN)

server_fclean:
	@$(RM) -r $(SERVER_BIN)



################################################################################
# CLIENTS RULES
client:
	@cmake $(OPTIONS) -B $(BUILD_DIR)
	@$(MAKE) -j `nproc` --no-print-directory -C $(BUILD_DIR) $(CLIENT_BIN)

client_fclean:
	@$(RM) -r $(CLIENT_BIN)



################################################################################
# TESTS RULES
tests_run: fclean setup-build-tree
	@$(MAKE) -j `nproc` --no-print-directory -C $(BUILD_DIR) $(CRITERION_BIN)
	-@cp $(BUILD_DIR)/bin/$(CRITERION_BIN) .
	@./$(CRITERION_BIN)
	@gcovr -r . -s --exclude='tests|lib' --exclude='BabelCommon/Utils/Runnable|BabelCommon/Utils/Logger|BabelCommon/Network/Sockets'
	@gcovr -b . -s --exclude='tests|lib'



################################################################################
# OTHERS RULES

setup-build-tree:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && conan install ..
	@cmake $(OPTIONS) -B $(BUILD_DIR)


mouli-install: fclean
	-conan remote add tech-repo https://api.bintray.com/conan/epitech/public-conan
	-conan remote add public-repo https://api.bintray.com/conan/bincrafters/public-conan
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && conan install .. --build=missing

clean:
	@$(RM) -r $(BUILD_DIR)

fclean: clean server_fclean client_fclean
	@$(RM) -r $(BUILD_DIR) $(CRITERION_BIN)

re: fclean all

.PHONY: all $(NAME) server client tests_run mouli
.PHONY: server_fclean client_fclean clean fclean re
