package Client

import (
	BabelNetwork "BabelGo/Common/Network"
	"fmt"
	"log"
	"net"
	"os"
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
		Client: BabelNetwork.NewClient(conn),
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
		rq := BabelNetwork.NewRequest(c.Conn)
		rq.Header = BabelNetwork.RequestHeader{
			RqType:        BabelNetwork.User,
			DataInfosSize: 10,
			Code:          BabelNetwork.RqLogin,
		}

		for i := 0; i < 1000000; i++ {
			if rq.Header.Code == BabelNetwork.RqLogin {
				rq.Header.Code = BabelNetwork.RqLogout
			} else {
				rq.Header.Code = BabelNetwork.RqLogin
			}
			log.Println("Sending Header :", rq.Header)
			if err := rq.Send(); err != nil {
				log.Println(err)
				return
			}
		}
		//if err := rq.Receive(); err != nil {
		//	break
		//}
		//log.Println("Header Received:", rq.Header)

		//if err := rq.Receive(); err != nil {
		//	break
		//}
		//_, err := c.Conn.Write([]byte(input))
		//if err != nil {
		//	log.Println("Error in writing to Connection", err)
		//}
		//netData, err := bufio.NewReader(c.Conn).ReadString('\n')
		////netData, err := bufio.NewReader(c.Conn).ReadString('\n')
		//if !c.Run {
		//	log.Println("lol")
		//	break
		//}
		//if err != nil {
		//	log.Println("Error in Handle Connection From read", err)
		//	break
		//}
		//temp := strings.TrimSpace(netData)
		//if temp == "STOP" {
		//	log.Println("lol")
		//	break
		//}
		//log.Println("Message Received", temp)
	}
}
