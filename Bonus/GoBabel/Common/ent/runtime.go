// Code generated by entc, DO NOT EDIT.

package ent

import (
	"GoBabel/Common/ent/schema"
	"GoBabel/Common/ent/user"
)

// The init function reads all schema descriptors with runtime
// code (default values, validators or hooks) and stitches it
// to their package variables.
func init() {
	userFields := schema.User{}.Fields()
	_ = userFields
	// userDescLogin is the schema descriptor for login field.
	userDescLogin := userFields[0].Descriptor()
	// user.LoginValidator is a validator for the "login" field. It is called by the builders before save.
	user.LoginValidator = func() func(string) error {
		validators := userDescLogin.Validators
		fns := [...]func(string) error{
			validators[0].(func(string) error),
			validators[1].(func(string) error),
			validators[2].(func(string) error),
		}
		return func(login string) error {
			for _, fn := range fns {
				if err := fn(login); err != nil {
					return err
				}
			}
			return nil
		}
	}()
	// userDescPassword is the schema descriptor for password field.
	userDescPassword := userFields[1].Descriptor()
	// user.PasswordValidator is a validator for the "password" field. It is called by the builders before save.
	user.PasswordValidator = func() func(string) error {
		validators := userDescPassword.Validators
		fns := [...]func(string) error{
			validators[0].(func(string) error),
			validators[1].(func(string) error),
			validators[2].(func(string) error),
		}
		return func(password string) error {
			for _, fn := range fns {
				if err := fn(password); err != nil {
					return err
				}
			}
			return nil
		}
	}()
}