package App

import (
	"GoBabel/Client/Bridge"
	nw "GoBabel/Common/Network"
)

type ClientContext struct {
	Client   *nw.Client
	IsMobile bool
	GuiCom   *Bridge.GuiCom
}
