package BabelInterfaces

import "io"

type Response interface {
	io.Writer
	io.Reader
}
