package BabelNetwork

import (
	"fmt"
	"io"
)

const (
	MagicByte = 0xff
)

type Request struct {
	Header RequestHeader

	Conn   io.ReadWriter
	Reader io.Reader
	Writer io.Writer
}

func NewRequest(conn io.ReadWriter) *Request {
	return &Request{
		Header: RequestHeader{},
		Writer: conn,
		Reader: conn,
		Conn:   conn,
	}
}

func (r *Request) Receive() error {
	b := make([]byte, HeaderSize)

	if _, err := r.Reader.Read(b); err != nil {
		return err
	}

	r.Header.Decode(b)
	return nil
}

func (r Request) Send() error {
	b := r.Header.Encode()
	if _, err := r.Writer.Write(b); err != nil {
		return err
	}
	return nil
}

func (r Request) Write(p []byte) (n int, err error) {
	return r.Writer.Write(p)
}

func (r Request) Read(p []byte) (n int, err error) {
	return r.Reader.Read(p)
}

func (r Request) GetType() uint16 {
	return r.Header.getType()
}

func (r Request) GetCode() uint16 {
	return r.Header.getCode()
}

func (r Request) Encode() {
	fmt.Println("ENCODING TO DO")
}

func (r Request) Decode() {
	fmt.Println("DECODING TO DO")
}
