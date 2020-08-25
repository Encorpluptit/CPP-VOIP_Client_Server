package ClientCore

import (
	"BabelGo/Client/Bridge"
	"BabelGo/Client/GUI"
	nw "BabelGo/Common/Network"
	"fmt"
	"log"
	"net"
	"os"
)

type Core struct {
	Client *nw.Client
	Run    bool
	GuiCom *Bridge.GuiCom
	Gui    *GUI.BabelGui
}

func NewClient(addr, port string) (*Core, func()) {
	conn, err := net.Dial("tcp4", addr+":"+port)
	if err != nil {
		log.Fatal(err)
	}
	client := &Core{
		Client: nw.NewClient(conn),
		Run:    true,
		GuiCom: &Bridge.GuiCom{
			ToNetwork: make(chan *nw.Request),
			ToGui:     make(chan *nw.Request),
		},
	}
	nw.RegisterInterfaces()
	client.Start()
	return client, client.Close
}

func (c *Core) SendInput(rq *nw.Request) {
	if !c.Run {
		return
	}
	c.GuiCom.SendToNetwork(rq)
}

func (c *Core) Close() {
	if err := c.Client.Conn.Close(); err != nil {
		log.Println("Error in ClientCore.Close() from net.conn.Close()", err)
	}
	c.GuiCom.Close()
	os.Exit(0)
}

func (c *Core) Start() {
	c.Run = true
	fmt.Printf("Serving %s\n", c.Client.Conn.RemoteAddr().String())
}

func (c *Core) Serve() {
	defer c.Close()

	for c.Run {
		data := c.GuiCom.GetFromGui()
		log.Println(data)
		if err := data.Send(c.Client.EncDec); err != nil {
			log.Println("In gob.Encode(): ", err)
			break
		}
		log.Println("HERE")

		//for i := 0; i < 1000000; i++ {
		//	if err := data.Send(c.EncDec); err != nil {
		//		log.Println("In gob.Encode(): ", err)
		//		break
		//	}
		//	if data.Header.Code == nw.UserRqLogout {
		//		data.Header.Code = nw.UserRqLogin
		//	} else {
		//		data.Header.Code = nw.UserRqLogout
		//	}
		//}
	}
}
