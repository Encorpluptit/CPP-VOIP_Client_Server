package BabelInterfaces

import "io"

type Sender interface {
	io.Writer
	Encode()
}

type Receiver interface {
	io.Reader
	Decode()
}

type Requester interface {
	Sender
	Receiver
}
