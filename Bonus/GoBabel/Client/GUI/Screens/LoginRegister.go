package Screens

import (
	"BabelGo/Client/Bridge"
	"BabelGo/Client/GUI/Core"
	"BabelGo/Client/GUI/Widgets"
	BabelNetwork "BabelGo/Common/Network"
	"fyne.io/fyne"
	"fyne.io/fyne/dialog"
	"fyne.io/fyne/layout"
	"fyne.io/fyne/widget"
)

func getLoginRegisterFuncs(Win fyne.Window, com *Bridge.GuiCom) (func(login, password string), func(login, password string)) {
	loginFunc := func(login, password string) {
		rq, err := BabelNetwork.NewUserLoginRequest(login, password)
		if err != nil {
			dialog.ShowError(err, Win)
			return
		}
		com.SendToNetwork(rq)
	}
	registerFunc := func(login, password string) {
		rq, err := BabelNetwork.NewUserRegisterRequest(login, password)
		if err != nil {
			dialog.ShowError(err, Win)
			return
		}
		com.SendToNetwork(rq)
	}
	return loginFunc, registerFunc
}

func LoginRegister(app *Core.BabelApp, client *Core.ClientContext) fyne.CanvasObject {
	loginFunc, registerFunc := getLoginRegisterFuncs(app.Win, client.GuiCom)
	accountForm := Widgets.CreateAccountForm(registerFunc)
	loginForm := Widgets.CreateLoginForm(loginFunc)

	account := widget.NewGroup("Create Account", accountForm)
	login := widget.NewGroup("Login", loginForm)

	return widget.NewVBox(
		layout.NewSpacer(),

		widget.NewHBox(
			layout.NewSpacer(),
			account,
			layout.NewSpacer(),
		),
		layout.NewSpacer(),
		widget.NewHBox(
			layout.NewSpacer(),
			login,
			layout.NewSpacer(),
		),
		layout.NewSpacer(),
	)
}
