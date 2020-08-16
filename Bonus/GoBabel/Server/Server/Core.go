package Server

import (
	"BabelGo/Common/Network"
	"bufio"
	"fmt"
	"log"
	"os"
	"os/signal"
	"strconv"
	"strings"
	"syscall"
)

type Core struct {
	Signals      chan os.Signal
	Run          bool
	ListenerCore *Listener
}

var BabelServer *Core = nil

func NewServer(address, port string) (*Core, func()) {
	BabelServer = &Core{
		Run:          false,
		ListenerCore: NewListener(address, port),
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
		conn, err := c.ListenerCore.NetListener.Accept()
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
	for c.Run {
		netData, err := bufio.NewReader(client.Conn).ReadString('\n')
		if !c.Run {
			break
		}
		if err != nil {
			log.Println("Error in Handle Connection From read", err)
			break
		}

		temp := strings.TrimSpace(netData)
		if temp == "STOP" {
			break
		}
		result := strconv.Itoa(5) + "\n"
		_, err = client.Conn.Write([]byte(result))
		if err != nil {
			log.Println("Error in writing to Connection", err)
			break
		}
	}
	client.Close()
	// TODO: Remove Client from List
}
