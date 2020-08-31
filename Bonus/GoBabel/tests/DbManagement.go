package tests

import (
	"GoBabel/Common/ent"
	"GoBabel/Server/Database"
	"log"
	"os"
)

const (
	UDam = iota
	UGreg
	UArthur
	UUgo
)

var TestUsersDatas = []*ent.User{
	{Login: "damien.bernard@epitech.eu", Password: "1234AB_cd666"},
	{Login: "gregoire.brasseur@epitech.eu", Password: "1234AB_cd666"},
	{Login: "arthur.benard@epitech.eu", Password: "1234AB_cd666"},
	{Login: "ugo.levi-cescutti@epitech.eu", Password: "1234AB_cd666"},
}

var TestCallDatas = []*ent.Call{
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UArthur]}}},
}

var TestConfDatas = []*ent.Conference{
	{Edges: ent.ConferenceEdges{
		Users: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UArthur]},
		Calls: nil,
	}},
	{Edges: ent.ConferenceEdges{}},
	{Edges: ent.ConferenceEdges{}},
}

func PopulateDb() {
	for _, user := range TestUsersDatas {
		_, err := Database.CreateUser(user)
		if err != nil {
			log.Printf("failed creating user: %v\ns", err)
		}
	}
}

func createUsers() {
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
