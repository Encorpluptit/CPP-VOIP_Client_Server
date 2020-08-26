package main

import (
	"GoBabel/Client/Core"
	"GoBabel/Client/GUI"
	"GoBabel/Client/GUI/App"
	"GoBabel/Common/BabelUtils"
	nw "GoBabel/Common/Network"
	"errors"
	"log"
	"os"
)

const (
	AppID      = "GoBabel"
	WindowName = "BabelGUI"
)

var CommandNotFound = errors.New("command not found")

func main() {
	core, coreCloser := Core.NewClient(os.Args[1], os.Args[2])
	defer coreCloser()

	gui := App.InitGui(AppID, WindowName, core.Client, core.GuiCom)

	if logger, err, loggerCloser := BabelUtils.NewLogger(BabelUtils.ClientLog); err == nil {
		log.SetOutput(logger)
		defer loggerCloser()
	}

	go GUI.Show(gui)
	core.Serve()
	gui.Run()

	//reader := bufio.NewReader(os.Stdin)
	//for core.Run {
	//	text, err := reader.ReadString('\n')
	//	if err != nil {
	//		log.Println("Error in main() from reader.ReadString()", err)
	//		break
	//	}
	//	text = strings.TrimSuffix(text, "\n")
	//	input := strings.Split(text, " ")
	//	if rq, err := getResponseFromCommand(input); err != nil {
	//		log.Println(err)
	//		continue
	//	} else {
	//		core.SendInput(rq)
	//	}
	//}
}

func getResponseFromCommand(input []string) (*nw.Request, error) {
	switch input[0] {
	case "login":
		if len(input) != 2 {
			return nil, errors.New("LOL METS MOI UN LOGIN STP")
		}
		return nw.NewUserLoginRequest(input[1], "abcd1234")
	case "logout":
		return nw.NewUserDatas(nw.UserRqLogout, "damien", "abcd1234")
	case "test":
		return nw.NewTestRequest(nw.RequestTest, "lol", "mdr")
	case "call":
		return nw.CallTest()
	default:
		return nil, CommandNotFound
	}
}
