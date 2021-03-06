package Screens

import (
	"GoBabel/Client/GUI/App"
	"GoBabel/Client/GUI/Ressources"
	"fyne.io/fyne"
	"fyne.io/fyne/canvas"
	"fyne.io/fyne/layout"
	"fyne.io/fyne/widget"
	"image/color"
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
	return widget.NewIcon(Ressources.GithubIconPng)
}

func getGoImg(client *App.ClientContext) fyne.CanvasObject {
	goImg := canvas.NewImageFromResource(Ressources.GoIconPng)
	if client.IsMobile {
		goImg.SetMinSize(fyne.NewSize(171, 125))
	} else {
		goImg.SetMinSize(fyne.NewSize(228, 167))
	}
	return goImg
}

func Welcome(app *App.BabelApp, client *App.ClientContext) fyne.CanvasObject {
	goImg := getGoImg(client)
	ghLogo := getGithubLogo()

	separator := canvas.NewLine(color.Black)
	separator.StrokeWidth = 5
	spaces := strings.Repeat("     ", 5)

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
	)
}
