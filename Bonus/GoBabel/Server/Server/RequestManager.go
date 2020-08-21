package Server

import (
	"BabelGo/Common/Network"
	"errors"
)

var RequestManager = map[uint16]BabelNetwork.RequestManager{
	BabelNetwork.RqUser: {ManagerFunc: UserManager, EmptyDatas: BabelNetwork.EmptyUserRequest},
	BabelNetwork.RqTest: {ManagerFunc: TestManager, EmptyDatas: BabelNetwork.EmptyTestRequest},
}

func getRequestManager(request *BabelNetwork.Request) (*BabelNetwork.RequestManager, error) {
	//return nil, errors.New("RequestType not found")
	manager, ok := RequestManager[request.Header.RqType]
	if !ok {
		return nil, errors.New("RequestType not found")
	}
	return &manager, nil
}
