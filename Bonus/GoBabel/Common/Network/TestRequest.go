package BabelNetwork

import (
	"BabelGo/ent"
	"time"
)

type TestDatas struct {
	Lol             uint16
	Mdr             uint8
	Login, Password string
	Timestamp       time.Time
	User            *ent.User
}

func NewTestRequest(code uint16, login, password string) (*Request, error) {
	rq := NewRequest()
	rq.Header.RqType = RequestTest
	rq.Header.Code = code
	rq.Datas = &TestDatas{
		Lol:       300,
		Mdr:       200,
		Login:     login,
		Password:  password,
		Timestamp: time.Now(),
		User: &ent.User{
			ID:       1,
			Login:    "LOl",
			Password: "mdr",
		},
	}
	return rq, nil
}
