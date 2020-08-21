package Server

import (
	"BabelGo/Common/Network"
	"errors"
)

var RequestManager = map[uint16]BabelNetwork.RequestManager{
	BabelNetwork.RqUser: {ManagerFunc: UserManager, EmptyDatas: BabelNetwork.EmptyUserRequest},
}

func getRequestManager(request *BabelNetwork.Request) (*BabelNetwork.RequestManager, error) {
	manager, ok := RequestManager[request.Header.RqType]
	if !ok {
		return nil, errors.New("RequestType not found")
	}
	return &manager, nil
}
