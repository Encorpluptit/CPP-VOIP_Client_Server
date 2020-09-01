package Database

import (
	"GoBabel/Common/ent"
	"fmt"
	"log"
)

func CreateConference(users ...*ent.User) (*ent.Conference, error) {
	conf, err := ServerDb.Client.Conference.
		Create().
		AddUsers(users...).
		Save(ServerDb.Ctx)
	if err != nil {
		return nil, fmt.Errorf("failed creating conference: %v", err)
	}
	log.Println("Conf was created: ", conf, "with users", users)
	return conf, nil
}

func AddUserToConference(conference *ent.Conference, user *ent.User) (*ent.Conference, error) {
	conf, err := conference.Update().AddUsers(user).Save(ServerDb.Ctx)
	if err != nil {
		return nil, fmt.Errorf("failed adding user %v", err)
	}
	return conf, nil
}
