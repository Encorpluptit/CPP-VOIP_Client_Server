package Requests

import (
	"encoding/binary"
	"io"
	"unsafe"
)

const HeaderSize = unsafe.Sizeof(RequestHeader{})

const (
	UnknownCode = iota
	RqUnknown
	RqUser
	RqFriend
)

type RequestHeader struct {
	RqType        uint16
	DataInfosSize uint16
	Code          uint16
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

type Request struct {
	Conn   io.ReadWriter
	Header RequestHeader
	Datas  EncodeDecoder
}

func NewRequest(conn io.ReadWriter) *Request {
	return &Request{
		Conn:   conn,
		Header: RequestHeader{Code: UnknownCode, RqType: RqUnknown},
	}
}

func (r *Request) ReceiveHeader() error {
	b := make([]byte, HeaderSize)

	if _, err := r.Conn.Read(b); err != nil {
		return err
	}

	r.Header.Decode(b)
	return nil
}

func (r *Request) ReceiveDatas() error {
	if err := ReceiveAndDecodeDatas(r.Header.DataInfosSize, r.Datas, r.Conn); err != nil {
		return err
	}
	return nil
}

func (r Request) Send() error {
	b := r.Header.Encode()
	b = append(b, r.Datas.Encode()...)
	if _, err := r.Conn.Write(b); err != nil {
		return err
	}
	return nil
}

func (r Request) Write(p []byte) (n int, err error) {
	return r.Conn.Write(p)
}

func (r Request) Read(p []byte) (n int, err error) {
	return r.Conn.Read(p)
}
