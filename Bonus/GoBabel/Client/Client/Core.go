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
	return client, client.Close
}

func (c *Core) SendInput(_ string) {
	if !c.Run {
		return
	}
	rq, err := nw.NewUserRequest(c.Conn, nw.RqUserLogin, "lol", "mdr xd")
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
		input := <-c.Input
		for i := 0; i < 100000; i++ {
			log.Println("Sending Header :", input.Header)
			if err := input.Send(); err != nil {
				log.Println(err)
				return
			}
			if input.Header.Code == nw.RqUserLogout {
				input.Header.Code = nw.RqUserLogin
			} else {
				input.Header.Code = nw.RqUserLogout
			}
		}
	}
}
