package Server

import (
	nw "GoBabel/Common/Network"
	"GoBabel/Common/ent/schema"
	"GoBabel/Server/Database"
	"errors"
	"log"
)

var WrongUserDatas = errors.New("wrong userDatas")

var userManager = map[uint16]func(*nw.Client, *nw.UserDatas) error{
	nw.UserRqLogin:    LoginUser,
	nw.UserRqLogout:   LogoutUser,
	nw.UserRqRegister: RegisterUser,
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
		return client.SendResponse(nw.NewUserAlreadyLoggedInResponse(datas.Login))
	}
	userFound, err := Database.QueryUser(datas.User)
	if err != nil {
		return client.SendResponse(nw.NewUserWrongLoginResponse(datas.Login))
	}
	if datas.Password != userFound.Password {
		return client.SendResponse(nw.NewUserWrongPasswordResponse())
	}
	client.Login(userFound)
	return client.SendResponse(nw.NewUserLoggedInResponse(userFound))
}

func RegisterUser(client *nw.Client, datas *nw.UserDatas) error {
	if client.IsLogged() {
		return client.SendResponse(nw.NewUserAlreadyLoggedInResponse(datas.Login))
	}

	// TODO: Add query Database for existing user
	newUser, err := Database.CreateUser(datas.User)
	if err == nil {
		client.Login(newUser)
		return client.SendResponse(nw.NewUserRegisteredResponse(newUser))
	}

	if err == schema.UserLoginNotValid {
		return client.SendResponse(nw.NewUserLoginNotValid(err))
	}
	if err == schema.UserPasswordNotValid {
		return client.SendResponse(nw.NewUserPasswordNotValid(err))
	}
	return client.SendResponse(nw.NewUserErrorResponse(nw.UserUnknownError, err.Error()))
}

func LogoutUser(client *nw.Client, datas *nw.UserDatas) error {
	if !client.IsLogged() {
		return client.SendResponse(nw.NewUserNotLoggedInResponse())
	}
	log.Println("Logout user")
	if err := client.Logout(); err != nil {
		return err
	}
	return client.SendResponse(nw.NewUserLoggedOutResponse())
}
