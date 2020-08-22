package BabelNetwork

import (
	"BabelGo/Common/BabelModels"
	"errors"
	"fmt"
	"log"
	"net"
)

var (
	ClientAlreadyLogged = errors.New("client already logged")
	ClientNotLogged     = errors.New("client not logged")
)

type Client struct {
	User   *BabelModels.User
	Conn   net.Conn
	EncDec EncodeDecoder
	Logged bool
}

func NewClient(conn net.Conn) *Client {
	return &Client{
		// TODO: Remove call and set to nil
		User:   BabelModels.NewUser(),
		Conn:   conn,
		EncDec: NewEncodeDecoder(conn),
		Logged: false,
	}
}

func (c Client) String() string {
	user := c.User.String()
	conn := fmt.Sprintf("With connexion %s", c.Conn.RemoteAddr().String())
	return user + "\n" + conn
}

func (c Client) IsLogged() bool {
	return c.Logged
}

func (c *Client) Login(datas *UserDatas) error {
	if c.IsLogged() {
		return ClientAlreadyLogged
	}
	// TODO: fetch in Db
	c.User.Login(datas.Login, datas.Password)
	log.Println("Client Logged", c)
	c.Logged = true
	return nil
}

func (c *Client) Logout() error {
	if !c.IsLogged() {
		return ClientNotLogged
	}
	// TODO: set User to nil
	log.Println("Logout user :", c.User)
	c.User.Logout()
	c.Logged = false
	return nil
}

func (c *Client) Close() {
	log.Println("Disconnecting Client :", c)
	if err := c.Logout(); err != nil && err != ClientNotLogged {
		log.Println("Error from Client Logout():", err)
	}
	if err := c.Conn.Close(); err != nil {
		log.Println("Error from Client Close():", err)
	}
}
