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

func AddUserToCall(call *ent.Call, user *ent.User) (*ent.Call, error) {
	var err error
	call, err = call.Update().AddParticipants(user).Save(ServerDb.Ctx)
	if err != nil {
		return nil, fmt.Errorf("failed add user to call: %v (call: %v)", err, call)
	}
	return call, nil
}

func StopCall(call *ent.Call) (*ent.Call, error) {
	var err error
	call, err = call.Update().SetFinishedAt(time.Now()).Save(ServerDb.Ctx)
	if err != nil {
		return nil, fmt.Errorf("failed stoping call: %v (call: %v)", err, call)
	}
	return call, nil
}
