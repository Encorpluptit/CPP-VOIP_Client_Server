package BabelNetwork

import "time"

const (
	CallRqCall = iota
	CallAccept
	CallRefuse
	CallAccepted
	CallRefused
	Call
)

const (
	MaxSenderSize   = 256
	MaxReceiverSize = 256
)

type CallDatas struct {
	Sender    string
	Targets   []string
	CallID    uint32
	Timestamp time.Time
}

func NewCallRequest(code uint16, sender string, targets []string, callId uint32) (*Request, error) {
	rq := NewRequest()
	rq.Header.RqType = RequestCall
	rq.Header.Code = code
	rq.Datas = &CallDatas{
		Sender:    sender,
		Targets:   targets,
		CallID:    callId,
		Timestamp: time.Now(),
	}
	return rq, nil
}

func CallTest() (*Request, error) {
	targets := []string{
		"lol", "mdr", "XD",
	}
	return NewCallRequest(CallRqCall, "damdam", targets, 8456)
}
