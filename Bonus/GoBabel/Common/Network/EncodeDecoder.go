package BabelNetwork

import (
	"encoding/gob"
	"io"
	"log"
)

type Encoder interface {
	Encode() []byte
}

type Decoder interface {
	DecodeInfos([]byte)
	DecodeDatas([]byte)
	GetSize() uint32
}

type EncodeDecoder interface {
	Encoder
	Decoder
}

func ReceiveDecodeDatas(infosSz uint16, decoder Decoder, reader io.Reader) error {
	//if infosSz == 0 {
	//	return errors.New("size of data info is null")
	//}
	dec := gob.NewDecoder(reader) // Will read from network.
	err := dec.Decode(decoder)
	if err != nil {
		log.Fatal("decode error:", err)
	}
	//b := make([]byte, infosSz)
	//if _, err := reader.Read(b); err != nil {
	//	return err
	//}
	//decoder.DecodeInfos(b)
	//
	//dataSz := decoder.GetSize()
	//if dataSz == 0 {
	//	return errors.New("no data to read")
	//}
	//
	//b = make([]byte, dataSz)
	//if _, err := reader.Read(b); err != nil {
	//	return err
	//}
	//decoder.DecodeDatas(b)
	return nil
}
