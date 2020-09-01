package tests

import (
	"GoBabel/Common/ent"
	"GoBabel/Server/Database"
	"testing"
)

var TestsUsers = []*ent.User{
	{ID: 1, Login: "damien.bernard@epitech.eu", Password: "1234AB_cd666"},
	{ID: 2, Login: "gregoire.brasseur@epitech.eu", Password: "1234AB_cd666"},
	{ID: 3, Login: "arthur.benard@epitech.eu", Password: "1234AB_cd666"},
	{ID: 4, Login: "ugo.levi-cescutti@epitech.eu", Password: "1234AB_cd666"},
}

func TestUserCreation(t *testing.T) {
	DbTearDown := InitDb()
	defer DbTearDown()
	for _, user := range TestsUsers {
		u, err := Database.CreateUser(user)
		if err != nil {
			t.Error(err)
		}
		if !checkUser(user, u) {
			t.Errorf("User Datas not valids")
		}
	}
}

func checkUser(exp, res *ent.User) bool {
	return exp.Login == res.Login && exp.ID == res.ID && exp.Password == res.Password
}
