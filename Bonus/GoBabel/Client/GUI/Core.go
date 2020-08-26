package GUI

import (
	"GoBabel/Client/GUI/App"
	"GoBabel/Client/GUI/Menus"
	"fyne.io/fyne"
	"fyne.io/fyne/app"
	"log"
)

const (
	InitWith             = 1280
	InitHeight           = 720
	preferenceCurrentTab = "currentTab"
)

type BabelGui struct {
	*App.BabelApp
	*App.ClientContext
}

func (gui *BabelGui) Show() {
	tabs := Menus.SetMenuSidebar(gui.BabelApp, gui.ClientContext)
	tabs.SelectTabIndex(gui.App.Preferences().Int(preferenceCurrentTab))
	gui.Win.SetContent(tabs)
	gui.Win.Show()
	for {
		rq := <-gui.GuiCom.ToGui
		log.Println("GUI got From Network", rq)
		//gui.Win.Show()
		//log.Println("Foor loop")
		//tabs := Menus.SetMenuSidebar(gui.BabelApp, gui.ClientContext)
		//gui.Win.SetContent(tabs)
		//gui.Win.Show()
	}
}

func (gui *BabelGui) Run() {
	gui.App.Run()
}

// TODO: Parse config with toml (cbm)
func InitGui(appID, windowName string) *BabelGui {
	gui := &BabelGui{&App.BabelApp{}, &App.ClientContext{}}
	gui.App = app.NewWithID(appID)
	gui.Win = gui.App.NewWindow(windowName)
	if fyne.CurrentDevice().IsMobile() {
		gui.IsMobile = true
	} else {
		gui.Win.Resize(fyne.NewSize(InitWith, InitHeight))
	}
	gui.Win.CenterOnScreen()
	gui.Win.SetMaster()
	appMenu := Menus.CreateAppMenu()
	gui.Win.SetMainMenu(appMenu)
	return gui
}
