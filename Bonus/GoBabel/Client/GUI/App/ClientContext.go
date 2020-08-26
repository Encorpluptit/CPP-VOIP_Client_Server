package App

import (
	"GoBabel/Client/Manager"
	nw "GoBabel/Common/Network"
)

type ClientContext struct {
	Client   *nw.Client
	IsMobile bool
	GuiCom   *Manager.GuiCom
}
