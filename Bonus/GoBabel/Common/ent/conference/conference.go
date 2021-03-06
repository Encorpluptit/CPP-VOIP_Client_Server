// Code generated by entc, DO NOT EDIT.

package conference

const (
	// Label holds the string label denoting the conference type in the database.
	Label = "conference"
	// FieldID holds the string denoting the id field in the database.
	FieldID = "id"

	// EdgeUsers holds the string denoting the users edge name in mutations.
	EdgeUsers = "users"
	// EdgeCalls holds the string denoting the calls edge name in mutations.
	EdgeCalls = "calls"

	// Table holds the table name of the conference in the database.
	Table = "conferences"
	// UsersTable is the table the holds the users relation/edge. The primary key declared below.
	UsersTable = "user_conferences"
	// UsersInverseTable is the table name for the User entity.
	// It exists in this package in order to avoid circular dependency with the "user" package.
	UsersInverseTable = "users"
	// CallsTable is the table the holds the calls relation/edge.
	CallsTable = "calls"
	// CallsInverseTable is the table name for the Call entity.
	// It exists in this package in order to avoid circular dependency with the "call" package.
	CallsInverseTable = "calls"
	// CallsColumn is the table column denoting the calls relation/edge.
	CallsColumn = "conference_calls"
)

// Columns holds all SQL columns for conference fields.
var Columns = []string{
	FieldID,
}

var (
	// UsersPrimaryKey and UsersColumn2 are the table columns denoting the
	// primary key for the users relation (M2M).
	UsersPrimaryKey = []string{"user_id", "conference_id"}
)
