package Server

import (
	"BabelGo/Common/Network"
	"fmt"
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"
)

type Core struct {
	Signals      chan os.Signal
	Run          bool
	ListenerCore *Listener
	Mutex        *sync.Mutex
}

var BabelServer *Core = nil

func NewServer(address, port string) (*Core, func()) {
	BabelServer = &Core{
		Run:          false,
		ListenerCore: NewListener(address, port),
		Mutex:        &sync.Mutex{},
	}
	return BabelServer, BabelServer.Close
}

func (c *Core) Close() {
	if c.Run {
		c.Run = false
		c.ListenerCore.Close()
	}
}

func (c *Core) initSignalChan() {
	c.Signals = make(chan os.Signal, 1)

	// `signal.Notify` registers the given channel to
	// receive notifications of the specified signals.
	signal.Notify(c.Signals, syscall.SIGINT, syscall.SIGTERM)

	// This goroutine executes a blocking receive for
	// signals. When it gets one it'll print it out
	go func() {
		sig := <-c.Signals
		log.Println("Signal received:", sig)
		c.Close()
	}()
}

func (c *Core) Start() error {
	c.initSignalChan()
	c.Run = true
	for c.Run {
		conn, err := c.ListenerCore.StartAccept()
		if !c.Run {
			break
		}
		if err != nil {
			fmt.Println(err)
			return err
		}
		newClient := c.ListenerCore.AcceptClient(conn)
		go c.handleClient(newClient)
	}
	return nil
}

func (c *Core) handleClient(client *BabelNetwork.Client) {
	fmt.Printf("Serving %s\n", client.Conn.RemoteAddr().String())
	defer func() {
		client.Close()
		c.ListenerCore.RemoveClient(client)
	}()
	RequestManagerGetter := func(request *BabelNetwork.Request) (*BabelNetwork.RequestManager, error) {
		c.Mutex.Lock()
		rqManager, err := getRequestManager(request)
		c.Mutex.Unlock()
		return rqManager, err
	}

	nb := 0
	for c.Run {
		if err := client.WaitRequest(RequestManagerGetter); err != nil {
			break
		}
		//rq := BabelNetwork.NewRequest(client.Conn)
		//if err := rq.ReceiveHeader(); err != nil {
		//	log.Println(err)
		//	break
		//}
		//log.Println("Header Received:", rq.Header)
		//rqManager, err := RequestManagerGetter(rq)
		////rqManager, err := getRequestManager(rq)
		//if err != nil {
		//	log.Println(err)
		//	break
		//}
		//rq.Datas = rqManager.EmptyDatas()
		//if err := rq.ReceiveDatas(); err != nil {
		//	log.Println(err)
		//	break
		//}
		//if err := rqManager.ManagerFunc(client, rq); err != nil {
		//	log.Println(err)
		//	break
		//}
		nb += 1
		log.Println("Request received:", nb)
	}
}
