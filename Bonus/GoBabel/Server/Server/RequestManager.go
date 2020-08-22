package Server

import (
	nw "BabelGo/Common/Network"
	"errors"
)

var RequestManager = map[uint16]func(*nw.Client, *nw.Request) error{
	nw.RqUser: UserManager,
}

func getRequestManager(request *nw.Request) (func(*nw.Client, *nw.Request) error, error) {
	//return nil, errors.New("RequestType not found")
	manager, ok := RequestManager[request.Header.RqType]
	if !ok {
		return nil, errors.New("RequestType not found")
	}
	return manager, nil
}
