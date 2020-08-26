package Server

import (
	nw "GoBabel/Common/Network"
	"GoBabel/Server/Database"
	"errors"
	"log"
)

var WrongUserDatas = errors.New("wrong userDatas")

var userManager = map[uint16]func(*nw.Client, *nw.UserDatas) error{
	nw.UserRqLogin:  LoginUser,
	nw.UserRqLogout: LogoutUser,
}

func UserManager(client *nw.Client, request *nw.Request) error {
	fn, ok := userManager[request.Header.Code]
	if !ok {
		return errors.New("in UserManager(): Code not found")
	}
	userDatas, ok := request.Datas.(*nw.UserDatas)
	if !ok {
		return WrongUserDatas
	}
	return fn(client, userDatas)
}

func LoginUser(client *nw.Client, datas *nw.UserDatas) error {
	if client.IsLogged() {
		rq := nw.NewUserAlreadyLoggedInResponse(datas.Login)
		if err := rq.Send(client.EncDec); err != nil {
			return err
		}
		return nil
	}
	userFound, err := Database.QueryUser(datas.User)
	if err != nil {
		rq := nw.NewUserWrongLoginResponse(datas.Login)
		if err := rq.Send(client.EncDec); err != nil {
			return err
		}
		return nil
	}
	if datas.Password != userFound.Password {
		rq := nw.NewUserWrongPasswordResponse()
		if err := rq.Send(client.EncDec); err != nil {
			return err
		}
		return nil
	}
	client.Login(userFound)
	// TODO: manage Login Errors HERE
	return nil
}

func LogoutUser(client *nw.Client, datas *nw.UserDatas) error {
	log.Println("Logout user")
	if err := client.Logout(); err != nil {
		return err
	}
	return nil
}
