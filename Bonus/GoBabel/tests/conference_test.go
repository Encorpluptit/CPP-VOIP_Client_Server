package tests

import (
	"GoBabel/Common/ent"
	"GoBabel/Server/Database"
	"testing"
)

func TestConferenceCreation(t *testing.T) {
	DbTearDown := InitDb()
	defer DbTearDown()
	createUsers()
	for _, exp := range TestConfDatas {
		conf, err := Database.CreateConference(exp.Edges.Users...)
		if err != nil {
			t.Error(err)
		}
		if !checkConference(exp, conf) {
			t.Errorf("User Datas not valids %v", exp)
		}
	}
}

func checkConference(exp, res *ent.Conference) bool {
	for idx, user := range res.Edges.Users {
		if !checkUser(exp.Edges.Users[idx], user) {
			return false
		}
	}
	return true
}
