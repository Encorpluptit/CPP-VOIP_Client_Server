package GUI

import (
	"BabelGo/Client/GUI/Core"
	"BabelGo/Client/GUI/Menus"
	"fyne.io/fyne"
	"fyne.io/fyne/app"
)

const (
	InitWith             = 1280
	InitHeight           = 720
	preferenceCurrentTab = "currentTab"
)

type BabelGui struct {
	*Core.BabelApp
	*Core.ClientContext
}

func (gui *BabelGui) Show() {
	tabs := Menus.SetMenuSidebar(gui.BabelApp, gui.ClientContext)
	tabs.SelectTabIndex(gui.App.Preferences().Int(preferenceCurrentTab))
	gui.Win.SetContent(tabs)
}

func (gui *BabelGui) Run() {
	gui.App.Run()
}

// TODO: Parse config with toml (cbm)
func InitGui(appID, windowName string) *BabelGui {
	gui := &BabelGui{&Core.BabelApp{}, &Core.ClientContext{}}
	gui.App = app.NewWithID(appID)
	gui.Win = gui.App.NewWindow(windowName)
	if fyne.CurrentDevice().IsMobile() {
		gui.IsMobile = true
	} else {
		gui.Win.Resize(fyne.NewSize(InitWith, InitHeight))
	}
	gui.Win.CenterOnScreen()
	gui.Win.SetMaster()
	gui.Input = make(chan uintptr)
	return gui
}
