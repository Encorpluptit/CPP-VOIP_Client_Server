package Screens

import (
	"BabelGo/Client/GUI/Core"
	"fyne.io/fyne"
	"fyne.io/fyne/canvas"
	"fyne.io/fyne/cmd/fyne_demo/data"
	"fyne.io/fyne/layout"
	"fyne.io/fyne/theme"
	"fyne.io/fyne/widget"
)

func Welcome(app *Core.BabelApp, client *Core.ClientContext) fyne.CanvasObject {
	logo := canvas.NewImageFromResource(data.FyneScene)
	if fyne.CurrentDevice().IsMobile() {
		logo.SetMinSize(fyne.NewSize(171, 125))
	} else {
		logo.SetMinSize(fyne.NewSize(228, 167))
	}

	return widget.NewVBox(
		layout.NewSpacer(),
		widget.NewLabelWithStyle("Welcome to Babel, the next Discord", fyne.TextAlignCenter, fyne.TextStyle{Bold: true}),
		widget.NewHBox(layout.NewSpacer(), logo, layout.NewSpacer()),

		widget.NewHBox(layout.NewSpacer(),
			widget.NewLabel("fyne.io"),
			widget.NewLabel("-"),
			widget.NewLabel("documentation"),
			widget.NewLabel("-"),
			widget.NewLabel("sponsor"),
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
