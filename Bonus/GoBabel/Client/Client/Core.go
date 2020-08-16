package Client

import (
	BabelNetwork "BabelGo/Common/Network"
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"
)

type Core struct {
	*BabelNetwork.Client
	Run   bool
	Input chan string
}

func NewClient(addr, port string) (*Core, func()) {
	conn, err := net.Dial("tcp4", addr+":"+port)
	if err != nil {
		log.Fatal(err)
	}
	client := &Core{
		BabelNetwork.NewClient(conn),
		true,
		make(chan string),
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
}

func (c *Core) Start() {
	c.Run = true
	fmt.Printf("Serving %s\n", c.Conn.RemoteAddr().String())
	for c.Run {
		input := <-c.Input
		log.Println("User Input:", input)
		_, err := c.Conn.Write([]byte(input))
		if err != nil {
			log.Println("Error in writing to Connection", err)
			break
		}
		netData, err := bufio.NewReader(c.Conn).ReadString('\n')
		if !c.Run {
			log.Println("lol")
			break
		}
		if err != nil {
			log.Println("Error in Handle Connection From read", err)
			break
		}
		temp := strings.TrimSpace(netData)
		if temp == "STOP" {
			log.Println("lol")
			break
		}
		log.Println("Message Received", temp)
	}
}
