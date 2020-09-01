// Code generated by entc, DO NOT EDIT.

package user

const (
	// Label holds the string label denoting the user type in the database.
	Label = "user"
	// FieldID holds the string denoting the id field in the database.
	FieldID = "id"
	// FieldLogin holds the string denoting the login field in the database.
	FieldLogin = "login"
	// FieldPassword holds the string denoting the password field in the database.
	FieldPassword = "password"

	// EdgeConferences holds the string denoting the conferences edge name in mutations.
	EdgeConferences = "conferences"
	// EdgeCalls holds the string denoting the calls edge name in mutations.
	EdgeCalls = "calls"

	// Table holds the table name of the user in the database.
	Table = "users"
	// ConferencesTable is the table the holds the conferences relation/edge. The primary key declared below.
	ConferencesTable = "user_conferences"
	// ConferencesInverseTable is the table name for the Conference entity.
	// It exists in this package in order to avoid circular dependency with the "conference" package.
	ConferencesInverseTable = "conferences"
	// CallsTable is the table the holds the calls relation/edge. The primary key declared below.
	CallsTable = "user_calls"
	// CallsInverseTable is the table name for the Call entity.
	// It exists in this package in order to avoid circular dependency with the "call" package.
	CallsInverseTable = "calls"
)

// Columns holds all SQL columns for user fields.
var Columns = []string{
	FieldID,
	FieldLogin,
	FieldPassword,
}

var (
	// ConferencesPrimaryKey and ConferencesColumn2 are the table columns denoting the
	// primary key for the conferences relation (M2M).
	ConferencesPrimaryKey = []string{"user_id", "conference_id"}
	// CallsPrimaryKey and CallsColumn2 are the table columns denoting the
	// primary key for the calls relation (M2M).
	CallsPrimaryKey = []string{"user_id", "call_id"}
)

var (
	// LoginValidator is a validator for the "login" field. It is called by the builders before save.
	LoginValidator func(string) error
	// PasswordValidator is a validator for the "password" field. It is called by the builders before save.
	PasswordValidator func(string) error
)
