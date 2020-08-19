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
	Input chan string
}

func NewClient(addr, port string) (*Core, func()) {
	conn, err := net.Dial("tcp4", addr+":"+port)
	if err != nil {
		log.Fatal(err)
	}
	client := &Core{
		Client: nw.NewClient(conn),
		Run:    true,
		Input:  make(chan string),
	}
	return client, client.Close
}

func (c *Core) SendInput(input string) {
	if !c.Run {
		return
	}
	c.Input <- input
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
		log.Println("User Input:", input)
		rq, err := nw.NewUserRequest(c.Conn, nw.RqUserLogin, "lol", "mdr xd")
		if err != nil {
			log.Println(err)
			return
		}

		for i := 0; i < 10; i++ {
			log.Println("Sending Header :", rq.Header)
			if err := rq.Send(); err != nil {
				log.Println(err)
				return
			}
			if rq.Header.Code == nw.RqUserLogout {
				rq.Header.Code = nw.RqUserLogin
			} else {
				rq.Header.Code = nw.RqUserLogout
			}
		}
	}
}
