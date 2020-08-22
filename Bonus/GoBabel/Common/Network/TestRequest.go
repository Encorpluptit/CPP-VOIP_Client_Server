package BabelNetwork

import "time"

type TestDatas struct {
	Lol             uint16
	Mdr             uint8
	Login, Password string
	Timestamp       time.Time
}

func NewTestRequest(code uint16, login, password string) (*Request, error) {
	rq := NewRequest()
	rq.Header.RqType = RqTest
	rq.Header.Code = code
	rq.Datas = &TestDatas{
		Lol:       300,
		Mdr:       200,
		Login:     login,
		Password:  password,
		Timestamp: time.Now(),
	}
	return rq, nil
}
