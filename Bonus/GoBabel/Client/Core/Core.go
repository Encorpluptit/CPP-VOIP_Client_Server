package Core

import (
	"GoBabel/Client/Bridge"
	"GoBabel/Client/GUI/App"
	nw "GoBabel/Common/Network"
	"fmt"
	"log"
	"net"
	"os"
)

type Core struct {
	Client *nw.Client
	GuiCom *Bridge.GuiCom
	Gui    *App.BabelGui
	Run    bool
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
	log.Println("Closing ClientCore ...")
	//if c.Run {
	c.Client.Close()
	//if err := c.Client.Conn.Close(); err != nil {
	//	log.Println("Error in ClientCore.Close() from net.conn.Close()", err)
	//}
	c.GuiCom.Close()
	c.Run = false
	//}
	log.Println("Client Core Closed !")
	os.Exit(0)
}

func (c *Core) Start() {
	c.Run = true
	fmt.Printf("Serving %s\n", c.Client.Conn.RemoteAddr().String())
}

func (c *Core) Serve() {
	go c.WaitGuiRequest()
	go c.WaitServerRequest()
}

func (c *Core) WaitGuiRequest() {
	defer c.Close()

	for c.Run {
		data := c.GuiCom.GetFromGui()
		log.Println("Request Received From GUI:", data)
		if err := data.Send(c.Client.EncDec); err != nil {
			log.Println("In gob.Encode(): ", err)
			break
		}
		log.Println("Request Send To SERVER")
	}
}

func (c *Core) WaitServerRequest() {
	defer c.Close()

	for c.Run {
		rq := &nw.Request{}
		if err := rq.Receive(c.Client.EncDec); err != nil {
			log.Println("decode error:", err)
			break
		}
		log.Println("Network got", rq)
		rqManager, err := getRequestManager(rq)
		if err != nil {
			log.Println(err)
			continue
		}
		if err := rqManager(c, rq); err != nil {
			log.Println(err)
			continue
		}

		//if rqManager, err := getRequestManager(rq); err != nil || rqManager(c, rq) != nil {
		//	log.Println(err)
		//	continue
		//}

		//c.GuiCom.SendToGui(rq)
		//rqManager, err := RequestManagerGetter(rq)
		//if err != nil {
		//	log.Println("In Request.Receive() -> RequestManagerGetter:", err)
		//	break
		//}
		//if err := rqManager(client, rq); err != nil {
		//	log.Println("In rqManager():", err)
		//	break
		//}
		//nb += 1
		//log.Println("Request received:", nb)
	}
}
