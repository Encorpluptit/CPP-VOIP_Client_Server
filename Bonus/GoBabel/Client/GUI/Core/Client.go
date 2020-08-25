package Core

import (
	"BabelGo/Client/Bridge"
	nw "BabelGo/Common/Network"
)

type ClientContext struct {
	Client   *nw.Client
	IsMobile bool
	GuiCom   *Bridge.GuiCom
}
