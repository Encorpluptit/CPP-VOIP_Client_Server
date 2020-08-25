package DataBaseTest

import (
	"BabelGo/Common/ent"
	"BabelGo/Server/Database"
	"testing"
)

func TestUsers(t *testing.T) {
	DbTearDown := InitDb()
	defer DbTearDown()
	users := []*ent.User{
		{ID: 1, Login: "damien.bernard@epitech.eu", Password: "1234AB_cd666"},
		{ID: 2, Login: "gregoire.brasseur@epitech.eu", Password: "1234AB_cd666"},
		{ID: 3, Login: "arthur.benard@epitech.eu", Password: "1234AB_cd666"},
		{ID: 4, Login: "ugo.levi-cescutti@epitech.eu", Password: "1234AB_cd666"},
	}
	for _, user := range users {
		u, err := Database.CreateUser(user)
		if err != nil {
			t.Error(err)
		}
		if !checkUser(user, u) {
			t.Errorf("")
		}
	}
}

func checkUser(exp, res *ent.User) bool {
	return exp.Login == res.Login && exp.ID == res.ID && exp.Password == res.Password
}
