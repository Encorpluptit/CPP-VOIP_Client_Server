package BabelNetwork

import (
	"errors"
	"fmt"
	"io"
	"log"
	"time"
)

type TestDatas struct {
	Login, Password string
	Lol             uint16
	Mdr             uint8
	Timestamp       time.Time
}

func NewTestRequest(conn io.ReadWriter, code uint16, login, password string) (*Request, error) {
	loginSz, passwordSz := uint16(len(login)), uint16(len(password))

	if loginSz > MaxLoginSize || passwordSz > MaxPasswordSize {
		err := fmt.Sprintf(
			"login or password too long: %d [%d] <==> %d [%d]",
			loginSz, MaxLoginSize, passwordSz, MaxPasswordSize,
		)
		return nil, errors.New(err)
	}

	rq := NewRequest(conn)
	rq.Header.RqType = RqTest
	rq.Header.Code = code
	rq.Header.DataInfosSize = uint16(UserInfosSize)
	TIMER := time.Now()
	rq.Datas = &TestDatas{
		Login:     login,
		Password:  password,
		Lol:       3000,
		Mdr:       200,
		Timestamp: TIMER,
	}
	log.Println(TIMER)
	return rq, nil
}

func EmptyTestRequest() EncodeDecoder {
	return &TestDatas{}
}

func (r TestDatas) Encode() []byte {
	b := make([]byte, UserInfosSize)
	b = append(b, []byte(r.Login)...)
	b = append(b, []byte(r.Password)...)
	return b
}

func (r *TestDatas) DecodeInfos(b []byte) {
	//r.LoginSize = binary.LittleEndian.Uint16(b[0:])
	//r.PasswordSize = binary.LittleEndian.Uint16(b[2:])
}

func (r *TestDatas) DecodeDatas(b []byte) {
	//r.Login = string(b[0:r.LoginSize])
	//r.Password = string(b[r.LoginSize:])
}

func (r TestDatas) GetSize() uint32 {
	//return uint32(r.LoginSize + r.PasswordSize)
	return 0
}
