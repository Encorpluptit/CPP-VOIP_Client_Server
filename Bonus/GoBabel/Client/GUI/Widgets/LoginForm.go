package Widgets

import (
	"fyne.io/fyne"
	"fyne.io/fyne/widget"
	"log"
)

type TextEntry struct {
	widget.Entry
	Submit func()
}

func newTextEntry(submitFunc func(), placeholder string) *TextEntry {
	entry := &TextEntry{}
	entry.ExtendBaseWidget(entry)
	entry.Submit = submitFunc
	entry.SetPlaceHolder(placeholder)
	return entry
}

func (e *TextEntry) KeyDown(key *fyne.KeyEvent) {
	switch key.Name {
	case fyne.KeyReturn:
		e.Submit()
	default:
	}
}

type PasswordEntry struct {
	widget.Entry
	Submit func()
}

func (e *PasswordEntry) KeyDown(key *fyne.KeyEvent) {
	switch key.Name {
	case fyne.KeyReturn:
		e.Submit()
		e.Reset()
	default:
	}
}

func (e *PasswordEntry) Reset() {
	e.Text = ""
	e.Refresh()
}

func newPasswordEntry(submitFunc func(), placeholder string) *PasswordEntry {
	entry := &PasswordEntry{}
	entry.Password = true
	entry.ExtendBaseWidget(entry)
	entry.Submit = submitFunc
	entry.SetPlaceHolder(placeholder)
	return entry
}

type LoginForm struct {
	*widget.Form
	Login      *TextEntry
	Password   *PasswordEntry
	SubmitFunc func(string, string)
}

func (e *LoginForm) Tapped(pe *fyne.PointEvent) {
	log.Printf("TAPPED at postion: %v (ABS: %v)", pe.Position, pe.AbsolutePosition)
}

func (e *LoginForm) Submit() {
	log.Printf("Log In:\nLogin: %s\nPassword: %s\n", e.Login.Text, e.Password.Text)
	e.SubmitFunc(e.Login.Text, e.Password.Text)
}

type AccountForm struct {
	LoginForm
	Pseudo *TextEntry
}

func (e *AccountForm) Submit() {
	log.Printf("Account create:\nPseudo: %s\nLogin: %s\nPassword: %s\n", e.Pseudo.Text, e.Login.Text, e.Password.Text)
	e.SubmitFunc(e.Login.Text, e.Password.Text)
}

func CreateLoginForm(logFunc func(string, string)) *LoginForm {
	newForm := &LoginForm{nil, nil, nil, logFunc}

	newForm.Login = newTextEntry(newForm.Submit, "Login")
	newForm.Password = newPasswordEntry(newForm.Submit, "Password")

	newForm.Form = &widget.Form{
		Items: []*widget.FormItem{
			{"Login", newForm.Login},
			{"Password", newForm.Password},
		},
		OnSubmit:   newForm.Submit,
		OnCancel:   newForm.Password.Reset,
		SubmitText: "Login",
		CancelText: "Cancel",
	}
	return newForm
}

func CreateAccountForm(regFunc func(string, string)) *AccountForm {
	newForm := &AccountForm{LoginForm{nil, nil, nil, regFunc}, nil}

	newForm.Pseudo = newTextEntry(newForm.Submit, "Pseudo")
	newForm.Login = newTextEntry(newForm.Submit, "Login")
	newForm.Password = newPasswordEntry(newForm.Submit, "Password")

	newForm.Form = &widget.Form{
		Items: []*widget.FormItem{
			{"Pseudo", newForm.Pseudo},
			{"Login", newForm.Login},
			{"Password", newForm.Password},
		},
		OnSubmit:   newForm.Submit,
		OnCancel:   newForm.Password.Reset,
		SubmitText: "Create",
		CancelText: "Cancel",
	}
	return newForm
}
