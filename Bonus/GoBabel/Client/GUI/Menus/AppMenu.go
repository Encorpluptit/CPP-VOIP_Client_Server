package Menus

import (
	"fmt"
	"fyne.io/fyne"
)

func CreateAppMenu() *fyne.MainMenu {
	newItem := fyne.NewMenuItem("New", nil)
	settingsItem := fyne.NewMenuItem("Settings", nil)
	settingsItem.ChildMenu = fyne.NewMenu("",
		fyne.NewMenuItem("Load Preferences", func() { fmt.Println("Menu New->Other->Project") }),
		fyne.NewMenuItem("Reset Preferences", func() { fmt.Println("Menu New->Other->Mail") }),
	)
	helpMenu := fyne.NewMenu("Help",
		fyne.NewMenuItem("Get Help", func() { fmt.Println("Help Menu") }),
		fyne.NewMenuItem("About", func() { fmt.Println("Menu New->Other->Mail") }),
	)
	appMenu := fyne.NewMainMenu(
		// a quit item will be appended to our first menu
		fyne.NewMenu("File", newItem, fyne.NewMenuItemSeparator(), settingsItem),
		fyne.NewMenu("Other", newItem, fyne.NewMenuItemSeparator(), settingsItem),
		//fyne.NewMenu("Edit", cutItem, copyItem, pasteItem, fyne.NewMenuItemSeparator(), findItem),
		helpMenu,
	)
	return appMenu
}
