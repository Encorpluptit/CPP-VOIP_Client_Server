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

//func LauchGui() *GUI.BabelGui {
//	gui := GUI.InitGui(AppID, WindowName)
//
//	appMenu := Menus.CreateAppMenu()
//	gui.Win.SetMainMenu(appMenu)
//	return gui
//}
//
//func main() {
//	gui := LauchGui()
//	tabs := Menus.SetMenuSidebar(gui.BabelApp, gui.ClientContext)
//	gui.Win.SetContent(tabs)
//	gui.Win.ShowAndRun()
//}

func main() {
	client, clientCloser := Client.NewClient(os.Args[1], os.Args[2])
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
		input := strings.Split(text, " ")
		if rq, err := getResponseFromCommand(input); err != nil {
			log.Println(err)
			continue
		} else {
			client.SendInput(rq)
		}
	}
}

func getResponseFromCommand(input []string) (*nw.Request, error) {
	switch input[0] {
	case "login":
		if len(input) != 2 {
			return nil, errors.New("LOL METS MOI UN LOGIN STP")
		}
		return nw.NewUserRequest(nw.UserRqLogin, input[1], "abcd1234")
	case "logout":
		return nw.NewUserRequest(nw.UserRqLogout, "damien", "abcd1234")
	case "test":
		return nw.NewTestRequest(nw.RequestTest, "lol", "mdr")
	case "call":
		return nw.CallTest()
	default:
		return nil, CommandNotFound
	}
}
