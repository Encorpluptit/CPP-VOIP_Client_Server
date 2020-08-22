package BabelModels

import (
	"fmt"
)

type User struct {
	Pseudo, Mail, Password string
}

func NewUser() *User {
	return &User{
		Pseudo:   "Unknown",
		Mail:     "",
		Password: "",
	}
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
}

func (u *User) Logout() {
	u.Pseudo = ""
	u.Password = ""
}

func (u User) String() string {
	if u.Mail == "" && u.Password == "" {
		return fmt.Sprint("Empty User")
	}
	return fmt.Sprintf("User named {{ %s }} with Email {{ %s }} password {{ %s }}", u.Pseudo, u.Mail, u.Password)
}
