package Server

import (
	BabelNetwork "BabelGo/Common/Network"
	"errors"
	"log"
)

var WrongUserDatas = errors.New("wrong userDatas")

var userManager = map[uint16]func(*BabelNetwork.Client, *BabelNetwork.UserDatas) error{
	BabelNetwork.UserRqLogin:  LoginUser,
	BabelNetwork.UserRqLogout: LogoutUser,
}

func UserManager(client *BabelNetwork.Client, request *BabelNetwork.Request) error {
	fn, ok := userManager[request.Header.Code]
	if !ok {
		return errors.New("in UserManager(): Code not found")
	}
	userDatas, ok := request.Datas.(*BabelNetwork.UserDatas)
	if !ok {
		return WrongUserDatas
	}
	return fn(client, userDatas)
}

func LoginUser(client *BabelNetwork.Client, datas *BabelNetwork.UserDatas) error {
	if err := client.Login(datas); err != nil {
		return err
	}
	// TODO: manage Login Errors HERE
	return nil
}

func LogoutUser(client *BabelNetwork.Client, datas *BabelNetwork.UserDatas) error {
	log.Println("Logout user")
	if err := client.Logout(); err != nil {
		return err
	}
	return nil
}
