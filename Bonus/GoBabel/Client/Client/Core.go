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
	return client, client.Close
}

func (c *Core) SendInput(_ string) {
	if !c.Run {
		return
	}
	rq, err := nw.NewUserRequest(nw.RqUserLogin, "lol", "mdr xd")
	if err != nil {
		log.Println(err)
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

		for i := 0; i < 1000000; i++ {
			if err := data.Send(c.EncDec); err != nil {
				log.Println("In gob.Encode(): ", err)
				break
			}
			if data.Header.Code == nw.RqUserLogout {
				data.Header.Code = nw.RqUserLogin
			} else {
				data.Header.Code = nw.RqUserLogout
			}
		}
	}
}
