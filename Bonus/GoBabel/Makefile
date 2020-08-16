

CLIENT_DIR						=	Client

SERVER_BIN						=	Server

MAIN_FILE						=	main.go

SERVER_DIR						=	Server

SERVER_BIN						=	BabelServer

CLIENT_BIN						=	BabelClient

server:
	go build -o $(SERVER_BIN) $(SERVER_DIR)/$(MAIN)

run-server: server
	@./$(CLIENT_BIN)


client:
	go build -o $(CLIENT_BIN) $(CLIENT_DIR)/$(MAIN)

clean:

fclean: clean
	-$(RM)