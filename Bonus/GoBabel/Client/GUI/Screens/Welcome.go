package Screens

import (
	"BabelGo/Client/GUI/Core"
	"fyne.io/fyne"
	"fyne.io/fyne/canvas"
	"fyne.io/fyne/layout"
	"fyne.io/fyne/widget"
	"image/color"
	"log"
	"net/url"
	"strings"
)

const (
	RepoGithubLink   = "https://github.com/Encorpluptit/CPP_babel_2020/tree/master/Bonus/GoBabel"
	DamienGithubLink = "https://github.com/Encorpluptit"
	GithubIconPath   = "https://github.com/Encorpluptit/CPP_babel_2020/tree/master/Bonus/GoBabel/Client/Ressources/Github-Icon.png"
	GoImagePath      = "https://github.com/Encorpluptit/CPP_babel_2020/tree/master/Bonus/GoBabel/Client/Ressources/Go-Icon.png"
)

// TODO: DO UML / DOC
const (
	UMLLink = "https://github.com/Encorpluptit/CPP_babel_2020"
	DocLink = "https://github.com/Encorpluptit/CPP_babel_2020"
)

func parseURL(urlStr string) *url.URL {
	link, err := url.Parse(urlStr)
	if err != nil {
		fyne.LogError("Could not parse URL", err)
	}
	return link
}

func getGithubLogo() fyne.CanvasObject {
	ghIcon, err := fyne.LoadResourceFromURLString(GithubIconPath)
	if err != nil {
		log.Println("Cannot load GithubLogo:", err)
		return layout.NewSpacer()
	}
	return widget.NewIcon(ghIcon)
}

func getGoImg(client *Core.ClientContext) fyne.CanvasObject {
	goIcon, err := fyne.LoadResourceFromURLString(GoImagePath)
	if err != nil {
		log.Println("Cannot load Go Image:", err)
		rect := canvas.NewRectangle(color.Black)
		if client.IsMobile {
			rect.SetMinSize(fyne.NewSize(171, 125))
		} else {
			rect.SetMinSize(fyne.NewSize(228, 167))
		}
		return rect
	}
	goImg := canvas.NewImageFromResource(goIcon)
	if client.IsMobile {
		goImg.SetMinSize(fyne.NewSize(171, 125))
	} else {
		goImg.SetMinSize(fyne.NewSize(228, 167))
	}
	return goImg
}

func Welcome(app *Core.BabelApp, client *Core.ClientContext) fyne.CanvasObject {
	goImg := getGoImg(client)
	ghLogo := getGithubLogo()

	separator := canvas.NewLine(color.Black)
	separator.StrokeWidth = 5
	spaces := strings.Repeat("     ", 5)
	//contributors := widget.NewGroup(
	//	spaces + "Contributors:" + spaces,
	//	//"Contributors:",
	//	widget.NewLabelWithStyle("Damien Bernard", fyne.TextAlignCenter, fyne.TextStyle{Monospace: true}),
	//)

	return widget.NewVBox(
		layout.NewSpacer(),
		widget.NewLabelWithStyle("Welcome to Babel, the next Discord (made with Golang)", fyne.TextAlignCenter, fyne.TextStyle{Bold: true}),
		widget.NewHBox(layout.NewSpacer(), goImg, layout.NewSpacer()),

		widget.NewHBox(
			layout.NewSpacer(),
			ghLogo,
			widget.NewHyperlink("Repository", parseURL(RepoGithubLink)),
			widget.NewLabel("-"),
			widget.NewHyperlink("(TODO)Documentation", parseURL(DocLink)),
			widget.NewLabel("-"),
			widget.NewLabel("sponsor"),
			layout.NewSpacer(),
		),
		widget.NewHBox(
			layout.NewSpacer(),
			widget.NewVBox(
				separator,
				//contributors,
				widget.NewLabelWithStyle(spaces+"Contributors:"+spaces, fyne.TextAlignCenter, fyne.TextStyle{Bold: true, Monospace: true}),
				widget.NewHBox(
					layout.NewSpacer(),
					widget.NewLabelWithStyle("Damien Bernard", fyne.TextAlignCenter, fyne.TextStyle{Monospace: true}),
					widget.NewHyperlink("Github", parseURL(DamienGithubLink)),
					layout.NewSpacer(),
				),
			),
			layout.NewSpacer(),
		),
		layout.NewSpacer(),

		//widget.NewGroup("Theme",
		//	fyne.NewContainerWithLayout(layout.NewGridLayout(2),
		//		widget.NewButton("Dark", func() {
		//			app.App.Settings().SetTheme(theme.DarkTheme())
		//		}),
		//		widget.NewButton("Light", func() {
		//			app.App.Settings().SetTheme(theme.LightTheme())
		//		}),
		//	),
		//),
	)
}
