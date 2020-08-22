package Database

import (
	"BabelGo/ent"
	"context"
	_ "github.com/mattn/go-sqlite3"
	"log"
)

type Database struct {
	Client *ent.Client
}

var ServerDb *Database = nil

func Init() func() {
	db := &Database{}
	var err error
	db.Client, err = ent.Open("sqlite3", "file:ent?mode=memory&cache=shared&_fk=1")
	if err != nil {
		log.Fatalf("failed opening connection to sqlite: %v", err)
	}
	closer := func() {
		if err := db.Client.Close(); err != nil {
			log.Fatalf("failed close connection to sqlite: %v", err)
		}
	}
	// run the auto migration tool.
	if err := db.Client.Schema.Create(context.Background()); err != nil {
		log.Fatalf("failed creating schema resources: %v", err)
	}
	db.Client.Debug()
	ServerDb = db
	return closer
}
