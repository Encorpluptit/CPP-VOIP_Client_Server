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

func newTextEntry(fn func()) *TextEntry {
	entry := &TextEntry{}
	entry.ExtendBaseWidget(entry)
	entry.Submit = fn
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
	default:
	}
}

func newPasswordEntry(fn func()) *PasswordEntry {
	entry := &PasswordEntry{}
	entry.Password = true
	entry.ExtendBaseWidget(entry)
	entry.Submit = fn
	return entry
}

type LoginForm struct {
	*widget.Form
	Login    *TextEntry
	Password *PasswordEntry
}

func (e *LoginForm) Tapped(pe *fyne.PointEvent) {
	log.Printf("TAPPED at postion: %v (ABS: %v)", pe.Position, pe.AbsolutePosition)
}

func (e *LoginForm) Submit() {
	log.Printf("Log In:\nLogin: %s\nPassword: %s\n", e.Login.Text, e.Password.Text)
}

type AccountForm LoginForm

func (e *AccountForm) Submit() {
	log.Printf("Account create:\nLogin: %s\nPassword: %s\n", e.Login.Text, e.Password.Text)
}

func CreateLoginForm() *LoginForm {
	newLoginForm := &LoginForm{nil, nil, nil}
	newLoginForm.Login = newTextEntry(newLoginForm.Submit)
	newLoginForm.Password = newPasswordEntry(newLoginForm.Submit)
	newLoginForm.Form = &widget.Form{
		Items: []*widget.FormItem{ // we can specify items in the constructor
			{"Login", newLoginForm.Login},
			{"Password", newLoginForm.Password},
		},
		OnSubmit: newLoginForm.Submit,
		OnCancel: func() {
			log.Println("CANCEL")
		},
		SubmitText: "Login",
		CancelText: "Cancel",
	}
	return newLoginForm
}

func CreateAccountForm() *AccountForm {
	newAcccountForm := &AccountForm{nil, nil, nil}
	newAcccountForm.Login = newTextEntry(newAcccountForm.Submit)
	newAcccountForm.Password = newPasswordEntry(newAcccountForm.Submit)
	newAcccountForm.Form = &widget.Form{
		Items: []*widget.FormItem{ // we can specify items in the constructor
			{"Login", newAcccountForm.Login},
			{"Password", newAcccountForm.Password},
		},
		OnSubmit: newAcccountForm.Submit,
		OnCancel: func() {
			log.Println("CANCEL")
		},
		SubmitText: "Create account",
		CancelText: "Cancel",
	}
	return newAcccountForm
}
