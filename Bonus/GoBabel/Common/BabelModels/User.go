package BabelModels

import (
	"fmt"
	"log"
)

type User struct {
	Pseudo, Mail, Password string
	Logged                 bool
}

func NewUser() User {
	return User{
		Pseudo:   "",
		Mail:     "Unknown",
		Password: "",
		Logged:   false,
	}
}

func (u User) IsLogged() bool {
	return u.Logged
}

func (u *User) SetLogin(login string) {
	u.Mail = login
}

func (u *User) SetPassword(password string) {
	u.Password = password
}

func (u *User) Login(login, password string) {
	u.SetLogin(login)
	u.SetPassword(password)
	u.Logged = true
}

func (u *User) Logout() {
	u.Pseudo = ""
	u.Password = ""
	log.Println("Logout User:", u)
}

func (u User) String() string {
	if !u.IsLogged() {
		return fmt.Sprint("Empty User")
	}
	return fmt.Sprintf("User named {{ %s }} with Email {{ %s }} password {{ %s }}", u.Pseudo, u.Mail, u.Password)
}
