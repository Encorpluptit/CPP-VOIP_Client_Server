package Server

import (
	BabelNetwork "GoBabel/Common/Network"
	"errors"
	"log"
)

var WrongCallDatas = errors.New("wrong callDatas")

var callManager = map[uint16]func(*BabelNetwork.Client, *BabelNetwork.CallDatas) error{
	BabelNetwork.CallRqCall: RequestCall,
}

func CallManager(client *BabelNetwork.Client, request *BabelNetwork.Request) error {
	fn, ok := callManager[request.Header.Code]
	if !ok {
		return errors.New("in UserManager(): Code not found")
	}
	callDatas, ok := request.Datas.(*BabelNetwork.CallDatas)
	if !ok {
		return WrongCallDatas
	}
	return fn(client, callDatas)
}

func RequestCall(client *BabelNetwork.Client, datas *BabelNetwork.CallDatas) error {
	log.Println("Call users Requested")
	log.Println(datas)
	return nil
}
