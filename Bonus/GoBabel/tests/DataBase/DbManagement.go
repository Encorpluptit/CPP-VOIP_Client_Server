package DataBaseTest

import (
	"BabelGo/Server/Database"
	"BabelGo/ent"
	"log"
	"os"
)

var TestUsersDatas = []*ent.User{
	{Login: "damien.bernard@epitech.eu", Password: "1234AB_cd666"},
	{Login: "gregoire.brasseur@epitech.eu", Password: "1234AB_cd666"},
	{Login: "arthur.benard@epitech.eu", Password: "1234AB_cd666"},
	{Login: "ugo.levi-cescutti@epitech.eu", Password: "1234AB_cd666"},
}

func PopulateDb() {
	for _, user := range TestUsersDatas {
		_, err := Database.CreateUser(user)
		if err != nil {
			log.Printf("failed creating user: %v\ns", err)
		}
	}
}

func InitDb() func() {
	dbCloser := Database.Init(Database.TestDBFile)
	TestDbCloser := func() {
		dbCloser()
		err := os.Remove(Database.TestDBFile)
		if err != nil {
			log.Fatal(err)
		}
	}
	return TestDbCloser
}

func setup() {
	PopulateDb()
}


