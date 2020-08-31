package Database

import (
	"GoBabel/Common/ent"
	"fmt"
	"log"
	"time"
)

func CreateCall() (*ent.Call, error) {
	call, err := ServerDb.Client.Call.
		Create().
		SetStartedAt(time.Now()).
		Save(ServerDb.Ctx)
	if err != nil {
		return nil, fmt.Errorf("failed creating call: %v", err)
	}
	log.Println("Call was created: ", call)
	return call, nil
}

//func CreateCallWithUsers(users ...*ent.User) (*ent.Call, error) {
//conf, err := ServerDb.Client.Call.
//	Create().
//	AddUsers(users...).
//	Save(ServerDb.Ctx)
//if err != nil {
//	return nil, fmt.Errorf("failed creating user: %v", err)
//}
//log.Println("Conf was created: ", conf, "with users", users)
//return conf, nil
//}
