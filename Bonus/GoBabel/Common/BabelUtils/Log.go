package BabelUtils

import (
	"fmt"
	"io"
	"log"
	"os"
	"strings"
)

const (
	EqualLine = "====="
	DashLine  = "-----"
)

type Logger struct {
	File    *os.File
	Vanilla io.Writer
}

func NewLogger() (Logger, error) {
	logOutput := log.Writer()
	file, err := os.Create("LOGLOL.log")
	if err != nil {
		log.Println("New Logger failed from os.Open", err)
		return Logger{}, err
	}
	return Logger{
		File:    file,
		Vanilla: logOutput,
	}, nil
}

func (l Logger) Write(data []byte) (int, error) {
	n1, err1 := l.File.Write(data)
	if err1 != nil {
		return 0, err1
	}
	n2, err2 := l.Vanilla.Write(data)
	if err2 != nil {
		return 0, err2
	}
	return n1 + n2, nil
}

func makeArrow(nb int, line string) string {
	return fmt.Sprintf("<%s>", strings.Repeat(line, nb))
}

func MakeEqualArrow(nb int) string {
	return makeArrow(nb, EqualLine)
}

func MakeDashArrow(nb int) string {
	return makeArrow(nb, DashLine)
}
