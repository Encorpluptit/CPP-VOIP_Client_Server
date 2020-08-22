package BabelNetwork

import (
	"log"
	"unsafe"
)

const HeaderSize = unsafe.Sizeof(RequestHeader{})

const (
	UnknownCode = iota
	RequestUnknown
	RequestUser
	RequestCall
	RequestFriend
	RequestMessage
	RequestTest
)

type RequestHeader struct {
	RqType uint16
	Code   uint16
}

type Request struct {
	Header RequestHeader
	Datas  interface{}
}

func NewRequest() *Request {
	return &Request{
		Header: RequestHeader{Code: UnknownCode, RqType: RequestUnknown},
	}
}

func (r *Request) Receive(dec Decoder) error {
	if err := dec.Decode(r); err != nil {
		log.Fatal("decode error:", err)
	}
	return nil
}

func (r *Request) Send(enc Encoder) error {
	if err := enc.Encode(r); err != nil {
		log.Println("In gob.Encode(): ", err)
		return err
	}
	return nil
}
