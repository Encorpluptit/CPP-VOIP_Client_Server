package Server

import (
	BabelNetwork "BabelGo/Common/Network"
	"fmt"
	"log"
	"net"
)

type Listener struct {
	NetListener net.Listener
	Clients     []*BabelNetwork.Client
}

func NewListener(address, port string) *Listener {
	fullAddr := fmt.Sprintf("%s:%s", address, port)
	l, err := net.Listen("tcp4", fullAddr)
	log.Println("Listening on ", fullAddr)
	if err != nil {
		str := fmt.Sprintf("Could not start Listener with address %s and port %s\n", address, port)
		log.Fatal(str, err)
	}
	return &Listener{
		NetListener: l,
		Clients:     nil,
	}
}

func (l *Listener) AcceptClient(conn net.Conn) *BabelNetwork.Client {
	newClient := BabelNetwork.NewClient(conn)
	l.Clients = append(l.Clients, newClient)
	return newClient
}

func (l *Listener) Close() {
	for _, c := range l.Clients {
		c.Close()
	}
	if err := l.NetListener.Close(); err != nil {
		log.Println("Error in Listener.Close() from net.NetListener Close():", err)
	}
}
