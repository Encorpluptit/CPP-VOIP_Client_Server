package Server

import (
	"BabelGo/Common/Network"
	"errors"
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
	nb := 0
	rq := BabelNetwork.NewRequest(client.Conn)
	for c.Run {
		if err := rq.Receive(); err != nil {
			break
		}
		log.Println("Header Received:", rq.Header)
		if err := c.handleRequest(client, rq); err != nil {
			log.Println(err)
		}
		nb += 1
		log.Println("Request received:", nb)
	}
	client.Close()
	c.ListenerCore.RemoveClient(client)
	// TODO: Remove Client from List
}

var RqTypeManager = map[uint16]func(*Core, *BabelNetwork.Client, *BabelNetwork.Request) error{
	BabelNetwork.User: ManageUser,
}

func (c *Core) handleRequest(client *BabelNetwork.Client, request *BabelNetwork.Request) error {
	//c.Mutex.Lock()
	fn, ok := RqTypeManager[request.GetType()]
	//c.Mutex.Unlock()
	if !ok {
		return errors.New("function for type not found")
	}
	if err := fn(c, client, request); err != nil {
		return err
	}
	return nil
}
