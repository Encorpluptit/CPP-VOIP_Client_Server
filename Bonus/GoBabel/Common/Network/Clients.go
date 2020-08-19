package BabelNetwork

import (
	"BabelGo/Common/BabelModels"
	"BabelGo/Common/Requests"
	"errors"
	"fmt"
	"log"
	"net"
)

var (
	ClientAlreadyLogged = errors.New("client already logged")
	ClientNotLogged     = errors.New("client already logged")
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
	conn := fmt.Sprintf("With connexion %s", c.Conn.RemoteAddr().String())
	return user + "\n" + conn
}

func (c Client) isLogged() bool {
	return c.User.IsLogged()
}

func (c *Client) Login(datas *Requests.UserDatas) error {
	if c.isLogged() {
		return ClientAlreadyLogged
	}
	c.User.Login(datas.Login, datas.Password)
	log.Println("Client Logged", c)
	return nil
}

func (c *Client) Logout() error {
	if c.isLogged() {
		return ClientNotLogged
	}
	log.Println("Disconnecting Client")
	c.User.Logout()
	return nil
}

func (c Client) Close() {
	if err := c.Logout(); err != nil {
		log.Println("Error on Client Logout():", err)
	}
	if err := c.Conn.Close(); err != nil {
		log.Println("Error on Client Close():", err)
	}
}
