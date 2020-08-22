package BabelError

import "fmt"

type BabelError struct {
	Code uint32
	Err  error
}

func (e BabelError) Error() string {
	return fmt.Sprintf("[ Babel Error ] : %d - %s", e.Code, e.Err)
}
