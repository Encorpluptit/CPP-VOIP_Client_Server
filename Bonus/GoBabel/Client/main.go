package main

import "C"
import (
	"BabelGo/Client/Client"
	"BabelGo/Common/BabelUtils"
	"bufio"
	"log"
	"os"
)

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
		client.SendInput(text)
	}
}
