package Database

import (
	"GoBabel/Common/ent"
	"GoBabel/Common/ent/user"
	"fmt"
	"log"
)

func CreateUser(requestedUser *ent.User) (*ent.User, error) {
	u, err := ServerDb.Client.User.
		Create().
		SetLogin(requestedUser.Login).
		SetPassword(requestedUser.Password).
		Save(ServerDb.Ctx)
	if err != nil {
		return nil, fmt.Errorf("failed creating user: %v", err)
	}
	log.Println("user was created: ", u)
	return u, nil
}

func QueryUser(requestedUser *ent.User) (*ent.User, error) {
	u, err := ServerDb.Client.User.
		Query().
		Where(user.LoginEQ(requestedUser.Login)).
		// `Only` fails if no user found,
		// or more than 1 user returned.
		Only(ServerDb.Ctx)
	if err != nil {
		return nil, fmt.Errorf("failed querying user: %v", err)
	}
	log.Println("user returned: ", u)
	return u, nil
}
