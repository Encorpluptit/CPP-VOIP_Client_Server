package BabelNetwork

import (
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"time"
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

var timeLoc = func(t *time.Time) {
	t.Local()
}

const (
	CallInfosSize   = unsafe.Sizeof(CallDatasInfos{})
	TimestampSize   = unsafe.Sizeof(time.Time{})
	MaxSenderSize   = 256
	MaxReceiverSize = 256
)

type CallDatasInfos struct {
	SenderSize, ReceiverSize, CallIdSize, TimestampSize uint16
}

type CallDatas struct {
	CallDatasInfos
	Sender, Receiver string
	CallId           uint16
	Timestamp        time.Time
}

func NewCallRequest(conn io.ReadWriter, code, callId uint16, sender, receiver string) (*Request, error) {
	senderSz, receiverSz := uint16(len(sender)), uint16(len(receiver))

	if senderSz > MaxSenderSize || receiverSz > MaxReceiverSize {
		err := fmt.Sprintf(
			"sender or receiver too long: %d [%d] <==> %d [%d]",
			senderSz, MaxSenderSize, receiverSz, MaxReceiverSize,
		)
		return nil, errors.New(err)
	}

	rq := NewRequest(conn)
	rq.Header.RqType = RqCall
	rq.Header.Code = code
	rq.Header.DataInfosSize = uint16(CallInfosSize)
	rq.Datas = &CallDatas{
		CallDatasInfos: CallDatasInfos{
			SenderSize:    senderSz,
			ReceiverSize:  receiverSz,
			TimestampSize: uint16(TimestampSize),
		},
		Sender:    sender,
		Receiver:  receiver,
		CallId:    callId,
		Timestamp: time.Now(),
	}
	return rq, nil
}

func EmptyCallRequest() EncodeDecoder {
	return &CallDatas{}
}

func (r CallDatas) Encode() []byte {
	b := make([]byte, uint16(CallInfosSize)+r.CallIdSize)
	binary.LittleEndian.PutUint16(b[0:], r.SenderSize)
	binary.LittleEndian.PutUint16(b[2:], r.ReceiverSize)
	binary.LittleEndian.PutUint16(b[4:], r.CallIdSize)
	binary.LittleEndian.PutUint16(b[6:], r.CallId)
	b = append(b, []byte(r.Sender)...)
	b = append(b, []byte(r.Receiver)...)
	return b
}

func (r *CallDatas) DecodeInfos(b []byte) {
	r.SenderSize = binary.LittleEndian.Uint16(b[0:])
	r.ReceiverSize = binary.LittleEndian.Uint16(b[2:])
	r.CallIdSize = binary.LittleEndian.Uint16(b[4:])
}

func (r *CallDatas) DecodeDatas(b []byte) {
	r.CallId = binary.LittleEndian.Uint16(b[r.SenderSize+r.ReceiverSize : r.SenderSize+r.ReceiverSize+r.CallIdSize])
	r.Sender = string(b[0:r.SenderSize])
	r.Receiver = string(b[r.SenderSize : r.SenderSize+r.ReceiverSize])
}

func (r CallDatas) GetSize() uint32 {
	return uint32(r.SenderSize + r.ReceiverSize)

}
