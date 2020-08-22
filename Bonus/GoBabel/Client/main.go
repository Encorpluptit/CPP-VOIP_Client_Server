package main

import "C"
import (
	"BabelGo/Client/Client"
	"BabelGo/Common/BabelUtils"
	nw "BabelGo/Common/Network"
	"bufio"
	"errors"
	"log"
	"os"
	"strings"
)

var CommandNotFound = errors.New("command not found")

func main() {
	arguments := os.Args
	client, clientCloser := Client.NewClient(arguments[1], arguments[2])
	client.Start()
	defer clientCloser()

	if logger, err, loggerCloser := BabelUtils.NewLogger(BabelUtils.ClientLog); err == nil {
		log.SetOutput(logger)
		defer loggerCloser()
	}

	go client.Serve()

	reader := bufio.NewReader(os.Stdin)
	for client.Run {
		text, err := reader.ReadString('\n')
		if err != nil {
			log.Println("Error in main() from reader.ReadString()", err)
			break
		}
		text = strings.TrimSuffix(text, "\n")
		if rq, err := getResponseFromCommand(text); err != nil {
			log.Println(err)
			continue
		} else {
			client.SendInput(rq)
		}
	}
}

func getResponseFromCommand(input string) (*nw.Request, error) {
	switch input {
	case "login":
		return nw.NewUserRequest(nw.UserRqLogin, "damien", "abcd1234")
	case "logout":
		return nw.NewUserRequest(nw.UserRqLogout, "damien", "abcd1234")
	case "test":
		return nw.CallTest()
	default:
		return nil, CommandNotFound
	}
}
