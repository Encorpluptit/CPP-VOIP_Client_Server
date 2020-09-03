package Save

import (
	"GoBabel/Common/ent"
	"GoBabel/Server/Database"
	"GoBabel/tests"
	"testing"
)

func TestConferenceCreation(t *testing.T) {
	for _, exp := range tests.TestConfDataset {
		conf, err := Database.CreateConference(exp.Edges.Users...)
		if err != nil {
			t.Error(err)
			continue
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
