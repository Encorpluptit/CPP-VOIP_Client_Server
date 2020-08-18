package BabelNetwork

import (
	"BabelGo/Common/BabelModels"
	"fmt"
	"log"
	"net"
)

type Client struct {
	User BabelModels.User
	Conn net.Conn
}

func NewClient(conn net.Conn) *Client {
	return &Client{
		User: BabelModels.NewUser(),
		Conn: conn,
	}
}

func (c Client) String() string {
	user := c.User.String()
	conn := fmt.Sprintf("Serving %s", c.Conn.RemoteAddr().String())
	return user + "\n" + conn
}

func (c Client) isLogged() bool {
	return c.User.IsLogged()
}

func (c Client) Login(request Request) {
	//c.User.Login()
}

func (c Client) Logout() {
	log.Println("Disconnecting Client")
	c.User.Logout()
}

func (c Client) Close() {
	c.Logout()
	if err := c.Conn.Close(); err != nil {
		log.Println("Error on Client Close():", err)
	}
}
