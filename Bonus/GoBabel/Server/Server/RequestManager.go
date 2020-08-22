package Server

import (
	nw "BabelGo/Common/Network"
	"errors"
)

var RequestManager = map[uint16]func(*nw.Client, *nw.Request) error{
	nw.RequestUser: UserManager,
	nw.RequestCall: CallManager,
	nw.RequestTest: TestManager,
}

func getRequestManager(request *nw.Request) (func(*nw.Client, *nw.Request) error, error) {
	manager, ok := RequestManager[request.Header.RqType]
	if !ok {
		return nil, errors.New("RequestType not found")
	}
	return manager, nil
}
