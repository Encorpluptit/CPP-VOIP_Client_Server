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
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UGreg]}}},
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UUgo]}}},
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UArthur]}}},
	//{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UArthur]}, Conference: TestConfDatas[0]}},
	//{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UGreg]}, Conference: TestConfDatas[0]}},
	//{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UUgo]}, Conference: TestConfDatas[1]}},
	//{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UArthur]}, Conference: TestConfDatas[1]}},
}

var TestConfDatas = []*ent.Conference{
	{Edges: ent.ConferenceEdges{
		Users: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UArthur], TestUsersDatas[UGreg]},
		Calls: []*ent.Call{TestCallDatas[0], TestCallDatas[1]},
	}},
	{Edges: ent.ConferenceEdges{
		Users: []*ent.User{TestUsersDatas[UDam], TestUsersDatas[UArthur], TestUsersDatas[UUgo]},
		Calls: []*ent.Call{TestCallDatas[2], TestCallDatas[3]},
	}},
	{Edges: ent.ConferenceEdges{
		Users: nil,
		Calls: nil,
	}},
}

func init() {
	log.Println("TESTING INI FCT")
}

func PopulateDb() {
	createUsers()
}

func createUsers() {
	for _, user := range TestUsersDatas {
		_, err := Database.CreateUser(user)
		if err != nil {
			log.Printf("failed creating user: %v (user: %v)\n", err, user)
		}
	}
}

func createConfs() {
	for _, conf := range TestConfDatas {
		_, err := Database.CreateConference(conf.Edges.Users...)
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

func setup() {
	PopulateDb()
}
