
NAME							=	Babel

CLIENT_DIR						=	Client

SERVER_BIN						=	Server

MAIN_FILE						=	main.go

SERVER_DIR						=	Server

SERVER_BIN						=	BabelServer

CLIENT_BIN						=	BabelClient

.DEFAULT: $(NAME)

$(NAME): server client

server:
	@go build -o $(SERVER_BIN) $(SERVER_DIR)/$(MAIN_FILE)

client:
	@go build -o $(CLIENT_BIN) $(CLIENT_DIR)/$(MAIN_FILE)

run-server: server
	@./$(SERVER_BIN) $(filter-out $@,$(MAKECMDGOALS))

run-client: client
	@./$(CLIENT_BIN) $(filter-out $@,$(MAKECMDGOALS))

tests_run:
	@go test -v -coverpkg=./... ./tests

clean:

fclean: clean
	@-$(RM) $(SERVER_BIN) $(CLIENT_BIN)

re: fclean $(NAME)

.PHONY: $(NAME) server client run-server run-client clean fclean re