package Screens

import (
	"BabelGo/Client/GUI/Core"
	"BabelGo/Client/GUI/Widgets"
	"fyne.io/fyne"
	"fyne.io/fyne/layout"
	"fyne.io/fyne/widget"
)

func LoginRegister(app *Core.BabelApp, client *Core.ClientContext) fyne.CanvasObject {
	accountForm := Widgets.CreateAccountForm()
	loginForm := Widgets.CreateLoginForm()

	account := widget.NewGroup("Create Account", accountForm)
	login := widget.NewGroup("Login", loginForm)

	return widget.NewVBox(
		layout.NewSpacer(),

		widget.NewHBox(
			layout.NewSpacer(),
			widget.NewVBox(
				widget.NewLabelWithStyle("Create an account", fyne.TextAlignCenter, fyne.TextStyle{Bold: true}),
				account,
			),
			layout.NewSpacer(),
		),
		layout.NewSpacer(),
		widget.NewHBox(
			layout.NewSpacer(),
			widget.NewVBox(
				widget.NewLabelWithStyle("Log in with the form below", fyne.TextAlignCenter, fyne.TextStyle{Bold: true}),
				login,
			),
			layout.NewSpacer(),
		),
		layout.NewSpacer(),
	)
}
