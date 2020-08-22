package main

import (
	"BabelGo/Common/BabelUtils"
	"BabelGo/Server/Database"
	"BabelGo/Server/Server"
	"BabelGo/ent"
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

	dbCloser := Database.Init(Database.ProdDBFile)
	defer dbCloser()

	err := PopulateDb()
	if err != nil {
		log.Fatal(err)
	}
	if err := serv.Start(); err != nil {
		log.Println("Error in main() from Server.Core.Start()", err)
	}
}

func PopulateDb() error {
	users := []*ent.User{
		{Login: "damien.bernard@epitech.eu", Password: "1234AB_cd666"},
		{Login: "gregoire.brasseur@epitech.eu", Password: "1234AB_cd666"},
		{Login: "arthur.benard@epitech.eu", Password: "1234AB_cd666"},
		{Login: "ugo.levi-cescutti@epitech.eu", Password: "1234AB_cd666"},
	}
	for _, user := range users {
		_, err := Database.CreateUser(user)
		if err != nil {
			log.Printf("failed creating user: %v\ns", err)
		}
	}
	return nil
}
