package BabelNetwork

import (
	"GoBabel/Common/ent"
	"errors"
	"fmt"
	"log"
	"net"
)

var (
	ClientAlreadyLogged = errors.New("client already logged")
	ClientNotLogged     = errors.New("client not logged")
)

const (
	EmptyUser = "{{ Empty User }}"
)

type Client struct {
	User   *ent.User
	Conn   net.Conn
	EncDec EncodeDecoder
	Logged bool
}

func NewClient(conn net.Conn) *Client {
	return &Client{
		User:   nil,
		Conn:   conn,
		EncDec: NewEncodeDecoder(conn),
		Logged: false,
	}
}

func (c Client) String() string {
	user := EmptyUser
	if c.User != nil {
		user = c.User.String()
	}
	conn := fmt.Sprintf("With connexion %s", c.Conn.RemoteAddr().String())
	return user + "\n" + conn
	//return fmt.Sprintf("%s %s %s", user, BabelUtils.MakeDashArrow(1), conn)
}

func (c Client) IsLogged() bool {
	return c.Logged
}

func (c *Client) Login(user *ent.User) {
	log.Println("Client Logged", c)
	c.Logged = true
	c.User = user
}

func (c *Client) Logout() error {
	if !c.IsLogged() {
		return ClientNotLogged
	}
	log.Println("Logout user :", c.User)
	c.User = nil
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
