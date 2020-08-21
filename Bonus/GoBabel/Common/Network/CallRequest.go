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
//RqUserLogin = iota
//RqUserLogout
//RqUserLoginOK
//RqUserLoginNOK
//RqUserLogoutOK
//RqUserLogoutNOK
)

const (
	CallInfosSIze   = unsafe.Sizeof(CallDatasInfos{})
	MaxSenderSize   = 256
	MaxReceiverSize = 256
)

type CallDatasInfos struct {
	SenderSize, ReceiverSize uint16
}

type CallDatas struct {
	CallDatasInfos
	Sender, Receiver string
}

func NewCallRequest(conn io.ReadWriter, code uint16, login, password string) (*Request, error) {
	loginSz, passwordSz := uint16(len(login)), uint16(len(password))

	if loginSz > MaxSenderSize || passwordSz > MaxReceiverSize {
		err := fmt.Sprintf(
			"login or password too long: %d [%d] <==> %d [%d]",
			loginSz, MaxSenderSize, passwordSz, MaxReceiverSize,
		)
		return nil, errors.New(err)
	}

	rq := NewRequest(conn)
	rq.Header.RqType = RqUser
	rq.Header.Code = code
	rq.Header.DataInfosSize = uint16(UserInfosSIze)
	rq.Datas = &CallDatas{
		CallDatasInfos: CallDatasInfos{
			SenderSize:   loginSz,
			ReceiverSize: passwordSz,
		},
		Sender:   login,
		Receiver: password,
	}
	return rq, nil
}

func EmptyCall() EncodeDecoder {
	return &UserDatas{}
}

func (r CallDatas) Encode() []byte {
	b := make([]byte, UserInfosSIze)
	binary.LittleEndian.PutUint16(b[0:], r.SenderSize)
	binary.LittleEndian.PutUint16(b[2:], r.ReceiverSize)
	b = append(b, []byte(r.Sender)...)
	b = append(b, []byte(r.Receiver)...)
	return b
}

func (r *CallDatas) DecodeInfos(b []byte) {
	r.SenderSize = binary.LittleEndian.Uint16(b[0:])
	r.ReceiverSize = binary.LittleEndian.Uint16(b[2:])
	log.Println(r.SenderSize, r.ReceiverSize)
}

func (r *CallDatas) DecodeDatas(b []byte) {
	r.Sender = string(b[0:r.SenderSize])
	r.Receiver = string(b[r.SenderSize:])
	log.Println(r.Sender, r.Receiver)
}

func (r CallDatas) GetSize() uint32 {
	return uint32(r.SenderSize + r.ReceiverSize)

}
