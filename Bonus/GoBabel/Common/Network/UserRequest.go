package BabelNetwork

import (
	"GoBabel/Common/ent"
	"fmt"
)

const (
	UserRqLogin = iota
	UserRqLogout
	UserLoggedIn
	UserLoggedOut
	UserRqRegister
	UserRqDeleteAccount
	UserRegistered
	UserAccountDeleted

	UserNotLoggedIn
	UserWrongLogin
	UserWrongPassword
	UserLoginNotValid
	UserPasswordNotValid
	UserAlreadyLoggedIn
	UserUnknownError
)

const (
	MaxLoginSize    = 50
	MaxPasswordSize = 20
)

const (
	UserWrongLoginFmt      = "Wrong login: %s !"
	UserWrongPasswordFmt   = "Wrong password !"
	UserAlreadyLoggedInFmt = "Already Logged in as %s."
	UserNotLoggedInFmt     = "Already Not Logged in."
)

type UserDatas struct {
	*ent.User
	Err string
}

func (u UserDatas) String() string {
	if u.User == nil {
		return EmptyUser + " : " + u.Err
	}
	return u.User.String() + " : " + u.Err
}

func checkUserDatasSizes(login, password string) error {
	loginSz, passwordSz := uint16(len(login)), uint16(len(password))

	if loginSz > MaxLoginSize {
		return fmt.Errorf(
			"your login is too long (%d), maximum: %d",
			loginSz, MaxLoginSize,
		)
	}
	if passwordSz > MaxPasswordSize {
		return fmt.Errorf(
			"your password is too long (%d), maximum: %d",
			passwordSz, MaxPasswordSize,
		)
	}
	return nil
}

func newUserRequest(code uint16) *Request {
	rq := NewRequest()
	rq.Header.RqType = RequestUser
	rq.Header.Code = code
	return rq
}

func NewUserDatas(code uint16, login, password string) (*Request, error) {
	rq := newUserRequest(code)
	rq.Datas = &UserDatas{
		User: &ent.User{
			Login:    login,
			Password: password,
		},
		Err: "",
	}
	return rq, nil
}

func NewUserErrorResponse(code uint16, errMsg string) *Request {
	rq := newUserRequest(code)
	rq.Datas = &UserDatas{
		User: nil,
		Err:  errMsg,
	}
	return rq
}

func NewUserLoginRequest(login, password string) (*Request, error) {
	if err := checkUserDatasSizes(login, password); err != nil {
		return nil, err
	}
	return NewUserDatas(UserRqLogin, login, password)
}

func NewUserRegisterRequest(login, password string) (*Request, error) {
	if err := checkUserDatasSizes(login, password); err != nil {
		return nil, err
	}
	return NewUserDatas(UserRqRegister, login, password)
}

func NewUserAccountDeletionRequest(login string) (*Request, error) {
	if err := checkUserDatasSizes(login, ""); err != nil {
		return nil, err
	}
	return NewUserDatas(UserRqLogin, login, "")
}

func NewUserLoggedInResponse(user *ent.User) *Request {
	rq := newUserRequest(UserLoggedIn)
	rq.Datas = &UserDatas{
		User: user,
		Err:  "",
	}
	return rq
}
func NewUserLoggedOutResponse() *Request {
	return newUserRequest(UserLoggedOut)
}

func NewUserRegisteredResponse(user *ent.User) *Request {
	rq := newUserRequest(UserRegistered)
	rq.Datas = &UserDatas{
		User: user,
		Err:  "",
	}
	return rq
}

func NewUserWrongLoginResponse(login string) *Request {
	return NewUserErrorResponse(UserWrongLogin, fmt.Sprintf(UserWrongLoginFmt, login))
}

func NewUserWrongPasswordResponse() *Request {
	return NewUserErrorResponse(UserWrongPassword, UserWrongPasswordFmt)
}

func NewUserLoginNotValid(err error) *Request {
	return NewUserErrorResponse(UserLoginNotValid, err.Error())
}

func NewUserPasswordNotValid(err error) *Request {
	return NewUserErrorResponse(UserWrongPassword, err.Error())
}

func NewUserAlreadyLoggedInResponse(login string) *Request {
	return NewUserErrorResponse(UserAlreadyLoggedIn, fmt.Sprintf(UserAlreadyLoggedInFmt, login))
}
func NewUserNotLoggedInResponse() *Request {
	return NewUserErrorResponse(UserNotLoggedIn, UserNotLoggedInFmt)
}
