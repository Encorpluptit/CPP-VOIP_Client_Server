package tests

import (
	"GoBabel/Common/ent"
	"GoBabel/Server/Database"
	"errors"
	"fmt"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/suite"
	"log"
	"testing"
)

var TestUsersDataset = []*ent.User{
	{ID: 1, Login: "damien.bernard@epitech.eu", Password: "1234AB_cd666"},
	{ID: 2, Login: "gregoire.brasseur@epitech.eu", Password: "1234AB_cd666"},
	{ID: 3, Login: "arthur.benard@epitech.eu", Password: "1234AB_cd666"},
	{ID: 4, Login: "ugo.levi-cescutti@epitech.eu", Password: "1234AB_cd666"},
}

var TestCallDataset = []*ent.Call{
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDataset[UDam], TestUsersDataset[UArthur]}}},
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDataset[UDam], TestUsersDataset[UGreg]}}},
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDataset[UDam], TestUsersDataset[UUgo]}}},
	{Edges: ent.CallEdges{Participants: []*ent.User{TestUsersDataset[UDam], TestUsersDataset[UArthur]}}},
}

var TestConfDataset = []*ent.Conference{
	{Edges: ent.ConferenceEdges{
		Users: []*ent.User{TestUsersDataset[UDam], TestUsersDataset[UArthur], TestUsersDataset[UGreg]},
		Calls: []*ent.Call{TestCallDataset[0], TestCallDataset[1]},
	}},
	{Edges: ent.ConferenceEdges{
		Users: []*ent.User{TestUsersDataset[UDam], TestUsersDataset[UArthur], TestUsersDataset[UUgo]},
		Calls: []*ent.Call{TestCallDataset[2], TestCallDataset[3]},
	}},
	//{Edges: ent.ConferenceEdges{
	//	Users: nil,
	//	Calls: nil,
	//}},
}


// Define the suite, and absorb the built-in basic suite
// functionality from testify - including a T() method which
// returns the current testing context
type DatabaseTestSuite struct {
	suite.Suite
	closer func()
	VariableThatShouldStartAtFive int
}

func (suite *DatabaseTestSuite) SetupTest() {
	suite.closer = InitDb()
	log.Println("Setup Suite")
	suite.VariableThatShouldStartAtFive = 5
}

func (suite *DatabaseTestSuite) TearDownTest() {
	log.Println("Teardown")
	suite.closer()
}

//// Make sure that VariableThatShouldStartAtFive is set to five
//// before each test
//func (suite *DatabaseTestSuite) SetupTest() {
//	suite.VariableThatShouldStartAtFive = 5
//}

// All methods that begin with "Test" are run as tests within a
// suite.
func (suite *DatabaseTestSuite) TestAUser() {
	for _, user := range TestUsersDataset {
		u, err := Database.CreateUser(user)
		if err != nil {
			suite.Error(err)
		}
		if !checkUser(user, u) {
			suite.Error(errors.New("user datas not valids"))
		}
	}
	for _, user := range TestUsersDataset {
		err := Database.DeleteUser(user)
		if err != nil {
			suite.Error(err)
		}
	}
}

func checkUser(exp, res *ent.User) bool {
	return exp.Login == res.Login && exp.ID == res.ID && exp.Password == res.Password
}

func (suite *DatabaseTestSuite) TestBConference() {
	createUsers()
	for _, exp := range TestConfDataset {
		conf, err := Database.CreateConference(exp.Edges.Users...)
		if err != nil {
			suite.Error(err)
			continue
		}
		if !checkConference(exp, conf) {
			suite.Error(fmt.Errorf("user Datas not valids %v", exp))
		}
	}
	assert.Equal(suite.T(), 5, suite.VariableThatShouldStartAtFive)
	suite.Equal(5, suite.VariableThatShouldStartAtFive)
}

func checkConference(exp, res *ent.Conference) bool {
	for idx, user := range res.Edges.Users {
		if !checkUser(exp.Edges.Users[idx], user) {
			return false
		}
	}
	return true
}


// In order for 'go test' to run this suite, we need to create
// a normal test function and pass our suite to suite.Run
func TestExampleTestSuite(t *testing.T) {
	suite.Run(t, new(DatabaseTestSuite))
}
