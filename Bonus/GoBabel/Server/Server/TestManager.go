package Server

import (
	BabelNetwork "BabelGo/Common/Network"
	"errors"
	"log"
)

var WrongTestDatas = errors.New("wrong callDatas")

func TestManager(client *BabelNetwork.Client, request *BabelNetwork.Request) error {
	testDatas, ok := request.Datas.(*BabelNetwork.TestDatas)
	if !ok {
		return WrongTestDatas
	}
	log.Println(testDatas)
	return nil
}
