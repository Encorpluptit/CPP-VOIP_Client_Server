package main

import (
	"GoBabel/Common/BabelUtils"
	"GoBabel/Common/tests/DataBase"
	"GoBabel/Server/Database"
	"GoBabel/Server/Server"
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

	// TODO: load Env to prod or test db
	dbCloser := Database.Init(Database.ProdDBFile)
	defer dbCloser()

	DataBaseTest.PopulateDb()
	if err := serv.Start(); err != nil {
		log.Println("Error in main() from Server.Core.Start()", err)
	}
}
