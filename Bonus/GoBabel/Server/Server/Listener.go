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
	log.Println("Listening on ", fullAddr)
	l, err := net.Listen("tcp4", fullAddr)
	if err != nil {
		str := fmt.Sprintf("Could not start Listener with address %s and port %s\n", address, port)
		log.Fatal(str, err)
	}
	return &Listener{
		NetListener: l,
		Clients:     nil,
	}
}

func (l *Listener) StartAccept() (net.Conn, error) {
	return l.NetListener.Accept()
}

func (l *Listener) AcceptClient(conn net.Conn) *BabelNetwork.Client {
	newClient := BabelNetwork.NewClient(conn)
	l.Clients = append(l.Clients, newClient)
	return newClient
}

func (l *Listener) Close() {
	if err := l.NetListener.Close(); err != nil {
		log.Println("Error in Listener.Close() from net.NetListener Close():", err)
	}
}

func (l *Listener) RemoveClient(target *BabelNetwork.Client) {
	for idx, client := range l.Clients {
		if client == target {
			lgth := len(l.Clients)
			l.Clients[idx] = l.Clients[lgth-1]
			l.Clients = l.Clients[:lgth-1]
			log.Println("Removing Client", *client)
			return
		}
	}
}
