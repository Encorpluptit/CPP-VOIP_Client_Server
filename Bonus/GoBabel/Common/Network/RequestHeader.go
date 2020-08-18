package BabelNetwork

import (
	"encoding/binary"
	"unsafe"
)

const (
	Unknown = iota
	User
	Friend
)

const (
	RqLogin  = iota
	RqLogout = iota
	LoginOK
	LoginNOK
	LogoutOK
	LogoutNOK
)

type RequestHeader struct {
	RqType        uint16
	DataInfosSize uint16
	Code          uint16
}

const HeaderSize = unsafe.Sizeof(RequestHeader{})

func (rh RequestHeader) getType() uint16 {
	return rh.RqType
}

func (rh RequestHeader) getCode() uint16 {
	return rh.Code
}

func (rh RequestHeader) Encode() []byte {
	b := make([]byte, HeaderSize)
	binary.LittleEndian.PutUint16(b[0:], rh.RqType)
	binary.LittleEndian.PutUint16(b[2:], rh.DataInfosSize)
	binary.LittleEndian.PutUint16(b[4:], rh.Code)
	return b
}

func (rh *RequestHeader) Decode(b []byte) {
	rh.RqType = binary.LittleEndian.Uint16(b[0:])
	rh.DataInfosSize = binary.LittleEndian.Uint16(b[2:])
	rh.Code = binary.LittleEndian.Uint16(b[4:])
}
