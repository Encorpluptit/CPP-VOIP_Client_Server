package BabelNetwork

import (
	"encoding/gob"
	"io"
)

type Encoder interface {
	Encode(data interface{}) error
}

type Decoder interface {
	Decode(data interface{}) error
}

type EncodeDecoder interface {
	Encoder
	Decoder
}

type GobEncoder struct {
	Enc *gob.Encoder
}

func (e *GobEncoder) Encode(data interface{}) error {
	return e.Enc.Encode(data)
}

func NewEncoder(conn io.Writer) Encoder {
	return &GobEncoder{
		Enc: gob.NewEncoder(conn),
	}
}

type GobDecoder struct {
	Dec *gob.Decoder
}

func (d *GobDecoder) Decode(data interface{}) error {
	return d.Dec.Decode(data)
}

func NewDecoder(conn io.Reader) Decoder {
	return &GobDecoder{
		Dec: gob.NewDecoder(conn),
	}
}

type GobEncodeDecoder struct {
	Encoder
	Decoder
}

func RegisterInterfaces() {
	gob.Register(&TestDatas{})
	gob.Register(&UserDatas{})
	gob.Register(&CallDatas{})
}

func NewEncodeDecoder(conn io.ReadWriter) EncodeDecoder {
	return &GobEncodeDecoder{
		NewEncoder(conn),
		NewDecoder(conn),
	}
}
