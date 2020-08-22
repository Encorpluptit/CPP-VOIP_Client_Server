package BabelNetwork

import "time"

type MessageDatas struct {
	Sender    string
	Targets   []string
	Id        uint32
	Timestamp time.Time
	Delivered bool
}
