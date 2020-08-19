package BabelNetwork

import (
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"log"
	"unsafe"
)

const (
	RqUserLogin = iota
	RqUserLogout
	RqUserLoginOK
	RqUserLoginNOK
	RqUserLogoutOK
	RqUserLogoutNOK
)

const (
	UserInfosSIze   = unsafe.Sizeof(UserDatasInfos{})
	MaxLoginSize    = 256
	MaxPasswordSize = 256
)

type UserDatasInfos struct {
	LoginSize, PasswordSize uint16
}

type UserDatas struct {
	UserDatasInfos
	Login, Password string
}

func NewUserRequest(conn io.ReadWriter, code uint16, login, password string) (*Request, error) {
	loginSz, passwordSz := uint16(len(login)), uint16(len(password))

	if loginSz > MaxLoginSize || passwordSz > MaxPasswordSize {
		err := fmt.Sprintf(
			"login or password too long: %d [%d] <==> %d [%d]",
			loginSz, MaxLoginSize, passwordSz, MaxPasswordSize,
		)
		return nil, errors.New(err)
	}

	rq := NewRequest(conn)
	rq.Header.RqType = RqUser
	rq.Header.Code = code
	rq.Header.DataInfosSize = uint16(UserInfosSIze)
	rq.Datas = &UserDatas{
		UserDatasInfos: UserDatasInfos{
			LoginSize:    loginSz,
			PasswordSize: passwordSz,
		},
		Login:    login,
		Password: password,
	}
	return rq, nil
}

func EmptyUser() EncodeDecoder {
	return &UserDatas{}
}

func (r UserDatas) Encode() []byte {
	b := make([]byte, UserInfosSIze)
	binary.LittleEndian.PutUint16(b[0:], r.LoginSize)
	binary.LittleEndian.PutUint16(b[2:], r.PasswordSize)
	b = append(b, []byte(r.Login)...)
	b = append(b, []byte(r.Password)...)
	return b
}

func (r *UserDatas) DecodeInfos(b []byte) {
	r.LoginSize = binary.LittleEndian.Uint16(b[0:])
	r.PasswordSize = binary.LittleEndian.Uint16(b[2:])
	log.Println(r.LoginSize, r.PasswordSize)
}

func (r *UserDatas) DecodeDatas(b []byte) {
	r.Login = string(b[0:r.LoginSize])
	r.Password = string(b[r.LoginSize:])
	log.Println(r.Login, r.Password)
}

func (r UserDatas) GetSize() uint32 {
	return uint32(r.LoginSize + r.PasswordSize)

}
