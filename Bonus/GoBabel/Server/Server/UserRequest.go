package Server

import (
	BabelNetwork "BabelGo/Common/Network"
	"BabelGo/Common/Requests"
	"errors"
	"log"
)

var WrongUserDatas = errors.New("wrong userDatas")

var userManager = map[uint16]func(*Core, *BabelNetwork.Client, *Requests.UserDatas) error{
	Requests.RqUserLogin:  LoginUser,
	Requests.RqUserLogout: LogoutUser,
}

func ManageUser(core *Core, client *BabelNetwork.Client, request *Requests.Request) error {
	fn, ok := userManager[request.Header.Code]
	if !ok {
		return errors.New("in ManageUser(): Code not found")
	}
	userDatas, ok := request.Datas.(*Requests.UserDatas)
	if !ok {
		return WrongUserDatas
	}
	return fn(core, client, userDatas)
}

func LoginUser(core *Core, client *BabelNetwork.Client, datas *Requests.UserDatas) error {
	log.Println("Login user")
	if err := client.Login(datas); err != nil {
		return err
	}
	return nil
}

func LogoutUser(core *Core, client *BabelNetwork.Client, datas *Requests.UserDatas) error {
	log.Println("Logout user")
	if err := client.Logout(); err != nil {
		return err
	}
	return nil
}
