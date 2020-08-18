package Server

import (
	BabelNetwork "BabelGo/Common/Network"
	"errors"
	"log"
)

var userManager = map[uint16]func(*Core, *BabelNetwork.Client, *BabelNetwork.Request) error{
	BabelNetwork.RqLogin:  LoginUser,
	BabelNetwork.RqLogout: LogoutUser,
}

func ManageUser(core *Core, client *BabelNetwork.Client, request *BabelNetwork.Request) error {
	fn, ok := userManager[request.GetCode()]
	if !ok {
		return errors.New("manage User Code not found")
	}
	return fn(core, client, request)
}

func LoginUser(core *Core, client *BabelNetwork.Client, request *BabelNetwork.Request) error {
	log.Println("Login user")
	//if client.Login()
	return nil
}

func LogoutUser(core *Core, client *BabelNetwork.Client, request *BabelNetwork.Request) error {
	log.Println("Logout user")
	//if err :=! client.Logout() {
	//
	//}
	return nil
}
