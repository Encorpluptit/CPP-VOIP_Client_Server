package main

import (
	"BabelGo/Common/BabelUtils"
	"BabelGo/Server/Server"
	"fmt"
	"log"
	"os"
)

func main() {
	arguments := os.Args

	if len(arguments) != 3 {
		fmt.Println("Please provide an address and a port number!")
		return
	}
	serv, serverCloser := Server.NewServer(arguments[1], arguments[2])
	if logger, err, loggerCloser := BabelUtils.NewLogger(BabelUtils.ServerLog); err == nil {
		log.SetOutput(logger)
		defer loggerCloser()
	}
	defer serverCloser()
	if err := serv.Start(); err != nil {
		log.Fatal("Error in main() from Server.Core.Start()", err)
	}
}
