package Screens

import (
	"GoBabel/Client/GUI/App"
	"GoBabel/Client/GUI/Widgets"
	"fyne.io/fyne"
	"fyne.io/fyne/layout"
	"fyne.io/fyne/theme"
	"fyne.io/fyne/widget"
)

func Settings(app *App.BabelApp, client *App.ClientContext) fyne.CanvasObject {
	loginForm := Widgets.CreateAccountForm(nil)

	return widget.NewVBox(
		layout.NewSpacer(),
		widget.NewLabelWithStyle("Welcome to the Fyne toolkit demo app", fyne.TextAlignCenter, fyne.TextStyle{Bold: true}),

		widget.NewHBox(
			layout.NewSpacer(),
			loginForm,
			layout.NewSpacer(),
		),
		layout.NewSpacer(),

		widget.NewGroup("Theme",
			fyne.NewContainerWithLayout(layout.NewGridLayout(2),
				widget.NewButton("Dark", func() {
					app.App.Settings().SetTheme(theme.DarkTheme())
				}),
				widget.NewButton("Light", func() {
					app.App.Settings().SetTheme(theme.LightTheme())
				}),
			),
		),
	)
}
