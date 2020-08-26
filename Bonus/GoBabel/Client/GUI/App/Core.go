package App

import (
	"GoBabel/Client/Bridge"
	nw "GoBabel/Common/Network"
	"fyne.io/fyne"
	"fyne.io/fyne/app"
)

const (
	InitWith   = 1280
	InitHeight = 720
	//preferenceCurrentTab = "currentTab"
)

type BabelGui struct {
	*BabelApp
	*ClientContext
}

type BabelApp struct {
	App fyne.App
	Win fyne.Window
}

type ClientContext struct {
	Client   *nw.Client
	GuiCom   *Bridge.GuiCom
	IsMobile bool
}

func NewClientContext(client *nw.Client, guiCom *Bridge.GuiCom) *ClientContext {
	ctx := &ClientContext{Client: client, GuiCom: guiCom}
	if fyne.CurrentDevice().IsMobile() {
		ctx.IsMobile = true
	}
	return ctx
}

func (gui *BabelGui) Run() {
	gui.App.Run()
}

// TODO: Parse config with toml (cbm)
func InitGui(appID, windowName string, client *nw.Client, guiCom *Bridge.GuiCom) *BabelGui {
	gui := &BabelGui{
		BabelApp: &BabelApp{
			App: app.NewWithID(appID),
		},
		ClientContext: NewClientContext(client, guiCom),
	}
	gui.Win = gui.App.NewWindow(windowName)
	if !gui.IsMobile {
		gui.Win.Resize(fyne.NewSize(InitWith, InitHeight))
	}
	gui.Win.CenterOnScreen()
	gui.Win.SetMaster()
	appMenu := CreateAppMenu()
	gui.Win.SetMainMenu(appMenu)
	return gui
}
