package main

import (
	"BabelGo/Common/BabelUtils"
	"BabelGo/Server/Database"
	"BabelGo/Server/Server"
	"BabelGo/ent"
	"context"
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

	dbCloser := Database.Init()
	defer dbCloser()

	_, err := CreateUser(context.Background(), Database.ServerDb.Client)
	if err != nil {
		log.Fatal(err)
	}
	if err := serv.Start(); err != nil {
		//log.Fatal("Error in main() from Server.Core.Start()", err)
		log.Println("Error in main() from Server.Core.Start()", err)
	}
}

func CreateUser(ctx context.Context, client *ent.Client) (*ent.User, error) {
	u, err := client.User.
		Create().
		SetLogin("damienbernard@epitech.eu").
		SetPassword("1234AB_cd666").
		Save(ctx)
	if err != nil {
		return nil, fmt.Errorf("failed creating user: %v", err)
	}
	log.Println("user was created: ", u)
	return u, nil
}
