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

	// Table holds the table name of the user in the database.
	Table = "users"
)

// Columns holds all SQL columns for user fields.
var Columns = []string{
	FieldID,
	FieldLogin,
	FieldPassword,
}

var (
	// LoginValidator is a validator for the "login" field. It is called by the builders before save.
	LoginValidator func(string) error
	// PasswordValidator is a validator for the "password" field. It is called by the builders before save.
	PasswordValidator func(string) error
)