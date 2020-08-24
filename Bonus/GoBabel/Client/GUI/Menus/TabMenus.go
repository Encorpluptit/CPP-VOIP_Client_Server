package Menus

import (
	"BabelGo/Client/GUI/Core"
	"BabelGo/Client/GUI/Screens"
	"fyne.io/fyne"
	"fyne.io/fyne/cmd/fyne_demo/screens"
	"fyne.io/fyne/theme"
	"fyne.io/fyne/widget"
)

func SetMenuSidebar(app *Core.BabelApp, client *Core.ClientContext) *widget.TabContainer {
	var tabs *widget.TabContainer
	if client.Client == nil {
		tabs = setLoggedOutSidebar(app, client)
	} else {
		tabs = setLoggedSidebar(app, client)
	}
	return tabs
}

func setLoggedOutSidebar(app *Core.BabelApp, client *Core.ClientContext) *widget.TabContainer {
	tabs := widget.NewTabContainer(
		widget.NewTabItemWithIcon("Welcome", theme.HomeIcon(), Screens.Welcome(app, client)),
		widget.NewTabItemWithIcon("Log in", theme.CheckButtonCheckedIcon(), Screens.LoginRegister(app, client)),
		widget.NewTabItemWithIcon("Settings", theme.ContentAddIcon(), Screens.Settings(app, client)),
	)

	tabs.SetTabLocation(widget.TabLocationTop)
	return tabs
}

func setLoggedSidebar(app *Core.BabelApp, client *Core.ClientContext) *widget.TabContainer {
	tabs := widget.NewTabContainer(
		widget.NewTabItemWithIcon("Graphics", theme.DocumentCreateIcon(), screens.GraphicsScreen()),
		widget.NewTabItemWithIcon("Widgets", theme.CheckButtonCheckedIcon(), screens.WidgetScreen()),
		widget.NewTabItemWithIcon("Containers", theme.ViewRestoreIcon(), screens.ContainerScreen()),
		widget.NewTabItemWithIcon("Windows", theme.ViewFullScreenIcon(), screens.DialogScreen(app.Win)),
		widget.NewTabItemWithIcon("Settings", theme.ContentAddIcon(), Screens.Settings(app, client)),
	)

	if !fyne.CurrentDevice().IsMobile() {
		tabs.Append(widget.NewTabItemWithIcon("Advanced", theme.SettingsIcon(), screens.AdvancedScreen(app.Win)))
	}
	tabs.SetTabLocation(widget.TabLocationLeading)
	return tabs
}
