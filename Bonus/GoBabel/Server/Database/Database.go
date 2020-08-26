package Database

import (
	"GoBabel/Common/ent"
	"context"
	_ "github.com/mattn/go-sqlite3"
	"log"
)

type Database struct {
	Client *ent.Client
	Ctx    context.Context
}

const (
	ProdDBFile = "./BabelDB"
	TestDBFile = "./TestDB"
)

var ServerDb *Database = nil

func Init(file string) func() {
	db := &Database{}
	var err error

	// Open Database With filename given in parameter
	db.Client, err = ent.Open("sqlite3", file+"?mode=memory&_fk=1")
	//db.Client, err = ent.Open("sqlite3", "file:ent?mode=memory&cache=shared&_fk=1")
	if err != nil {
		log.Fatalf("failed opening connection to sqlite: %v", err)
	}

	// Set closer to log and close Properly
	closer := func() {
		log.Println("Closing Database ...")
		if err := db.Client.Close(); err != nil {
			log.Fatalf("failed close connection to sqlite: %v", err)
		}
		log.Println("Database Closed !")
	}

	// Get Context Background() (Required by ent)
	db.Ctx = context.Background()

	// run the auto migration tool.
	if err := db.Client.Schema.Create(db.Ctx); err != nil {
		log.Fatalf("failed creating schema resources: %v", err)
	}
	db.Client.Debug()
	ServerDb = db
	return closer
}
