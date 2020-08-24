package Core

import "fyne.io/fyne"

type ClientContext struct {
	Client   fyne.App
	IsMobile bool
	Input    chan uintptr
}
