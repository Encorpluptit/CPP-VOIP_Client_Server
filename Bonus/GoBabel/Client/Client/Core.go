package Client

import (
	nw "BabelGo/Common/Network"
	"fmt"
	"log"
	"net"
	"os"
)

type Core struct {
	*nw.Client
	Run   bool
	Input chan *nw.Request
}

func NewClient(addr, port string) (*Core, func()) {
	conn, err := net.Dial("tcp4", addr+":"+port)
	if err != nil {
		log.Fatal(err)
	}
	client := &Core{
		Client: nw.NewClient(conn),
		Run:    true,
		Input:  make(chan *nw.Request),
	}
	nw.RegisterInterfaces()
	client.Start()
	return client, client.Close
}

func (c *Core) SendInput(rq *nw.Request) {
	if !c.Run {
		return
	}
	c.Input <- rq
}

func (c *Core) Close() {
	if err := c.Conn.Close(); err != nil {
		log.Println("Error in Core.Close() from net.conn.Close()", err)
	}
	close(c.Input)
	os.Exit(0)
}

func (c *Core) Start() {
	c.Run = true
	fmt.Printf("Serving %s\n", c.Conn.RemoteAddr().String())
}

func (c *Core) Serve() {
	defer c.Close()

	for c.Run {
		data := <-c.Input
		log.Println(data)
		if err := data.Send(c.EncDec); err != nil {
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
