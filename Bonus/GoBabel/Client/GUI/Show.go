package GUI

import (
	"GoBabel/Client/GUI/App"
	"GoBabel/Client/GUI/Screens"
	"log"
)

const preferenceCurrentTab = "currentTab"

func Show(gui *App.BabelGui) {
	tabs := Screens.SetMenuSidebar(gui.BabelApp, gui.ClientContext)
	tabs.SelectTabIndex(gui.App.Preferences().Int(preferenceCurrentTab))
	gui.Win.SetContent(tabs)
	gui.Win.Show()
	for {
		rq := gui.GuiCom.GetFromNetwork()
		log.Println("GUI got From Network", rq)
		//gui.Win.Show()
		//log.Println("Foor loop")
		//tabs := Menus.SetMenuSidebar(gui.BabelApp, gui.ClientContext)
		//gui.Win.SetContent(tabs)
		//gui.Win.Show()
	}
}
