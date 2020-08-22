package BabelNetwork

import (
	"errors"
	"fmt"
)

const (
	UserRqLogin = iota
	UserRqLogout
	UserLoggedIn
	UserLoggedOut

	UserWrongLogin
	UserWrongPassword
	UserAlreadyLoggedIn
	UserNotLoggedIn
)

const (
	MaxLoginSize    = 256
	MaxPasswordSize = 256
)

type UserDatas struct {
	Login, Password string
}

func NewUserRequest(code uint16, login, password string) (*Request, error) {
	loginSz, passwordSz := uint16(len(login)), uint16(len(password))

	if loginSz > MaxLoginSize || passwordSz > MaxPasswordSize {
		err := fmt.Sprintf(
			"login or password too long: %d [%d] <==> %d [%d]",
			loginSz, MaxLoginSize, passwordSz, MaxPasswordSize,
		)
		return nil, errors.New(err)
	}

	rq := NewRequest()
	rq.Header.RqType = RequestUser
	rq.Header.Code = code
	rq.Datas = &UserDatas{
		Login:    login,
		Password: password,
	}
	return rq, nil
}
