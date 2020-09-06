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

func PopulateDb() {
	InitDb()
	createUsers()
	createConfs()
}

type UserPtr struct {
	Ptr **ent.User
}

var TestUsers = []*ent.User{
	{Login: "damien.bernard@epitech.eu", Password: "1234AB_cd666"},
	{Login: "gregoire.brasseur@epitech.eu", Password: "1234AB_cd666"},
	{Login: "arthur.benard@epitech.eu", Password: "1234AB_cd666"},
	{Login: "ugo.levi-cescutti@epitech.eu", Password: "1234AB_cd666"},
}

var TestConf = []*ent.Conference{
	{Edges: ent.ConferenceEdges{
		Users: []*ent.User{TestUsers[UDam], TestUsers[UArthur], TestUsers[UGreg]},
		//Calls: []*ent.Call{TestCallDataset[0], TestCallDataset[1]},
	}},
	{Edges: ent.ConferenceEdges{
		Users: []*ent.User{TestUsers[UDam], TestUsers[UArthur], TestUsers[UUgo]},
		//Calls: []*ent.Call{TestCallDataset[2], TestCallDataset[3]},
	}},
	//{Edges: ent.ConferenceEdges{
	//	Users: nil,
	//	Calls: nil,
	//}},
}

func createUsers() {
	for idx, user := range TestUsers {
		u, err := Database.CreateUser(user)
		if err != nil {
			log.Printf("failed creating user: %v (user: %v)\n", err, user)
		} else {
			TestUsers[idx] = u
		}
	}
}

func createConfs() {
	for _, conf := range TestConf {
		conf, err := Database.CreateConference(conf.Edges.Users...)
		if err != nil {
			log.Printf("failed creating conference: %v (conf: %v)\n", err, conf)
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
//
//func setup() {
//	PopulateDb()
//}
