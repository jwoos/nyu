package main

import (
	"encoding/json"
	"fmt"
	"time"

	"github.com/jwoos/go_checkers"

	"github.com/asticode/go-astilectron"
	"github.com/asticode/go-astilectron-bootstrap"
)

func gui() {
	// Constants
	const htmlAbout = `Welcome on <b>Astilectron</b> demo!<br>
	This is using the bootstrap and the bundler.`

	// Vars
	var AppName string
	var rule checkers.Rule
	var state *checkers.StateByte

	bootstrap.Run(bootstrap.Options{
		Asset: Asset,
		AstilectronOptions: astilectron.Options{
			AppName:            AppName,
			AppIconDarwinPath:  "resources/icon.icns",
			AppIconDefaultPath: "resources/icon.png",
		},
		Debug: DEBUG,
		Homepage: "index.html",
		MenuOptions: []*astilectron.MenuItemOptions{{
			Label: astilectron.PtrStr("File"),
			SubMenu: []*astilectron.MenuItemOptions{
				{Role: astilectron.MenuItemRoleClose},
			},
		}},
		OnWait: nil,
		MessageHandler: func(w *astilectron.Window, message bootstrap.MessageIn) (interface{}, error) {
			switch message.Name {
			case "initialize":
				rule = checkers.NewRule(6, 6, FIRST, SIDE, 2, false, false, false)
				state = checkers.NewStateByte(rule, true)

				// astilectron doesn't play well with bytes
				return arrayBytetoUint(state.Board), nil

			case "human-move":
				var payload map[string][]int
				json.Unmarshal(message.Payload, &payload)

				from := checkers.NewCoordinate(payload["from"][0], payload["from"][1])
				to := checkers.NewCoordinate(payload["to"][0], payload["to"][1])

				err := move(state, from, to)
				if err != nil {
					return nil, err
				}

				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					"",
				)

				return response, nil

			case "ai-move":
				start := time.Now()
				move, stat := minimaxAB(state, DEPTH)
				elapsed := time.Since(start)

				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					fmt.Sprintf("AI move: %v \n Time elapsed: %v \n%v", move, elapsed, stat),
				)

				return response, nil
				return arrayBytetoUint(state.Board), nil
			}

			return "", nil
		},
		RestoreAssets:  RestoreAssets,
		WindowOptions: &astilectron.WindowOptions{
			BackgroundColor: astilectron.PtrStr("#FFFFFF"),
			Center:          astilectron.PtrBool(true),
			Height:          astilectron.PtrInt(700),
			Width:           astilectron.PtrInt(700),
			WebPreferences: &astilectron.WebPreferences{
				DevTools: astilectron.PtrBool(true),
			},
		},
	})
}
