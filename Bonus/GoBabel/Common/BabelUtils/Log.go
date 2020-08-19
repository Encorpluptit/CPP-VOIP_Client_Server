package BabelUtils

import (
	"errors"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
	"time"
)

const (
	Ldate         = 1 << iota // the date in the local time zone: 2009/01/23
	Ltime                     // the time in the local time zone: 01:23:23
	Lmicroseconds             // microsecond resolution: 01:23:23.123123.  assumes Ltime.
)

const (
	EqualLine    = "====="
	DashLine     = "-----"
	LogDirectory = "GoLogs"
	ClientLog    = "ClientLog"
	ServerLog    = "ServerLog"
)

type Logger struct {
	File    *os.File
	Vanilla io.Writer
}

func getTimeStamp() string {
	t := time.Now()
	year, month, day := t.Date()
	hour, min, sec := t.Clock()
	return fmt.Sprintf("%d-%d-%d_%d-%d-%d", year, int(month), day, hour, min, sec)
}

func createDirectories() error {
	cur, err := os.Getwd()
	if err != nil {
		return err
	}
	logDir := cur + "/" + LogDirectory
	if file, err := os.Stat(logDir); err == nil {
		if file.IsDir() {
			return nil
		}
		return errors.New(logDir + ": is not a dir")
	}
	return os.Mkdir(LogDirectory, 0700)
}

func NewLogger(LogType string) (*Logger, error, func()) {
	if err := createDirectories(); err != nil {
		log.Println("New Logger failed from createDirectories", err)
		return nil, err, nil
	}
	logOutput := log.Writer()
	fileName := fmt.Sprintf("%s/%s-%s", LogDirectory, getTimeStamp(), LogType)
	file, err := os.Create(fileName)
	if err != nil {
		log.Println("New Logger failed from os.Open", err)
		return nil, err, nil
	}
	logger := &Logger{
		File:    file,
		Vanilla: logOutput,
	}
	fmt.Println("Logger Ready !")
	return logger, nil, logger.Close
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

func (l Logger) Close() {
	if err := l.File.Close(); err != nil {
		fmt.Println("Error in Logger.Close() from os.File.Close()", err)
	}
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
