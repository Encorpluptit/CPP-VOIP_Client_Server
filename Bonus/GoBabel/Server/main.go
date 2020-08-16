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
	if logger, err, loggerClosure := BabelUtils.NewLogger(); err == nil {
		log.SetOutput(logger)
		defer loggerClosure()
	}
	serv, closure := Server.NewServer(arguments[1], arguments[2])
	defer closure()
	if err := serv.Start(); err != nil {
		log.Fatal("Error in main() from Server.Core.Start()", err)
	}
}
