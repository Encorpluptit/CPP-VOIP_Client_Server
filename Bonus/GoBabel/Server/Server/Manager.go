package Server

import (
	BabelNetwork "BabelGo/Common/Network"
	"BabelGo/Common/Requests"
	"errors"
)

type RequestManager struct {
	Func  func(*Core, *BabelNetwork.Client, *Requests.Request) error
	NewRq func() Requests.EncodeDecoder
}

var ServerRqTypeManager = map[uint16]RequestManager{
	Requests.RqUser: {Func: ManageUser, NewRq: Requests.EmptyUser},
}

func getRequestManager(request *Requests.Request) (*RequestManager, error) {
	//c.Mutex.Lock()
	manager, ok := ServerRqTypeManager[request.Header.RqType]
	//c.Mutex.Unlock()
	if !ok {
		return nil, errors.New("RequestType not found")
	}
	return &manager, nil
}
