package Core

import (
	nw "GoBabel/Common/Network"
	"errors"
	"log"
)

var RequestManager = map[uint16]func(*Core, *nw.Request) error{
	nw.RequestUser: UserManager,
	//nw.RequestCall: CallManager,
	//nw.RequestTest: TestManager,
}

var userManager = map[uint16]func(*Core, *nw.Request, *nw.UserDatas) error{
	nw.UserLoggedIn: LogUser,
}

func UserManager(core *Core, request *nw.Request) error {
	fn, ok := userManager[request.Header.Code]
	if !ok {
		return errors.New("in UserManager(): Code not found")
	}
	userDatas, ok := request.Datas.(*nw.UserDatas)
	if !ok {
		return nw.WrongUserDatas
	}
	return fn(core, request, userDatas)
}

func LogUser(core *Core, rq *nw.Request, datas *nw.UserDatas) error {
	core.Client.User = datas.User
	log.Println(core.Client.User)
	core.GuiCom.SendToGui(rq)
	return nil
}

func getRequestManager(request *nw.Request) (func(*Core, *nw.Request) error, error) {
	manager, ok := RequestManager[request.Header.RqType]
	if !ok {
		return nil, errors.New("RequestType not found")
	}
	return manager, nil
}
