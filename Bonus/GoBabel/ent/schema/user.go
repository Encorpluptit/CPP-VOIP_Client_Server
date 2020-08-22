package schema

import (
	"errors"
	"github.com/facebook/ent"
	"github.com/facebook/ent/schema/field"
	"regexp"
	"unicode"
)

// User holds the schema definition for the User entity.
type User struct {
	ent.Schema
}

// Fields of the User.
func (User) Fields() []ent.Field {
	return []ent.Field{
		field.String("login").Unique().Match(regexp.MustCompile(emailRegex)).MinLen(3).MaxLen(254).Comment("Mail / Login of user"),
		field.String("password").Validate(isValidPassword).MinLen(3).MaxLen(40).Comment("Password for user"),
	}
}

// Edges of the User.
func (User) Edges() []ent.Edge {
	return nil
}

//var emailRegex = regexp.MustCompile("^[a-zA-Z0-9.!#$%&'*+\\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$")
const emailRegex = "^[a-zA-Z0-9.!#$%&'*+\\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$"

// isEmailValid checks if the email provided passes the required structure and length.
//func isEmailValid(e string) error {
//	if !emailRegex.MatchString(e) {
//		return errors.New("email (login) not valid")
//	}
//	return nil
//}

func isValidPassword(pass string) error {
	var (
		upp, low, num, sym bool
		tot                uint8
	)

	for _, char := range pass {
		switch {
		case unicode.IsUpper(char):
			upp = true
			tot++
		case unicode.IsLower(char):
			low = true
			tot++
		case unicode.IsNumber(char):
			num = true
			tot++
		case unicode.IsPunct(char) || unicode.IsSymbol(char):
			sym = true
			tot++
		default:
			return errors.New("one of password character is not recognised")
		}
	}

	if !upp || !low || !num || !sym || tot < 8 {
		return errors.New("password not strong enough")
	}
	return nil
}
