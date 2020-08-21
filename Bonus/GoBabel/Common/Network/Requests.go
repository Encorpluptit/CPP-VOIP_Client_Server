package BabelNetwork

import (
	"encoding/binary"
	"encoding/gob"
	"io"
	"log"
	"unsafe"
)

const HeaderSize = unsafe.Sizeof(RequestHeader{})

const (
	UnknownCode = iota
	RqUnknown
	RqUser
	RqCall
	RqTest
	RqFriend
)

type RequestHeader struct {
	RqType        uint16
	DataInfosSize uint16
	Code          uint16
}

type Request struct {
	Conn   io.ReadWriter
	Header RequestHeader
	Datas  interface{}
}

type RequestManager struct {
	ManagerFunc func(*Client, *Request) error
	EmptyDatas  func() EncodeDecoder
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
	dec := gob.NewDecoder(r.Conn) // Will read from network.
	err := dec.Decode(r.Datas)
	if err != nil {
		log.Fatal("decode error:", err)
	}
	return nil
	//return ReceiveDecodeDatas(r.Header.DataInfosSize, r.Datas, r.Conn)
}

func (r Request) Send() error {
	b := r.Header.Encode()
	//b = append(b, r.Datas.Encode()...)
	if _, err := r.Conn.Write(b); err != nil {
		return err
	}
	enc := gob.NewEncoder(r.Conn)
	err := enc.Encode(r.Datas)
	if err != nil {
		log.Fatal("encode error:", err)
	}
	return nil
}

func (r Request) Write(p []byte) (n int, err error) {
	return r.Conn.Write(p)
}

func (r Request) Read(p []byte) (n int, err error) {
	return r.Conn.Read(p)
}
