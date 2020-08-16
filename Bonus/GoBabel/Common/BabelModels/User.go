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

func (u *User) Login(login, password string) bool {
	if u.IsLogged() {
		return false
	}
	u.SetLogin(login)
	u.SetPassword(password)
	u.Logged = true
	return u.Logged
}

func (u *User) Logout() bool {
	if !u.IsLogged() {
		return false
	}
	u.Pseudo = ""
	u.Password = ""
	log.Println("Logout User:\n", u)
	return true
}

func (u User) String() string {
	if !u.IsLogged() {
		return fmt.Sprint("Empty User")
	}
	return fmt.Sprintf("User named {{ %s }} with password {{ %s }}", u.Pseudo, u.Password)
}
