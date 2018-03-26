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
	// Vars
	var AppName string
	var rule checkers.Rule
	var state *checkers.StateByte

	rule = checkers.NewRule(6, 6, FIRST, SIDE, 2, false, false, false)
	state = checkers.NewStateByte(rule, true)

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
			w.OpenDevTools();

			switch message.Name {
			case "initialize":
				// astilectron doesn't play well with bytes
				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					"",
					false,
					false,
					uint(checkers.BLANK),
				)

				return response, nil

			case "human-move":
				var payload map[string][]int
				json.Unmarshal(message.Payload, &payload)

				from := checkers.NewCoordinate(payload["from"][0], payload["from"][1])
				to := checkers.NewCoordinate(payload["to"][0], payload["to"][1])

				err := move(state, from, to)
				if err != nil {
					return err, err
				}

				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					"",
					false,
					false,
					uint(checkers.BLANK),
				)

				return response, nil

			case "ai-move":
				start := time.Now()
				move, stat := minimaxAB(state, DEPTH)
				elapsed := time.Since(start)

				state.Move(move)

				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					fmt.Sprintf("AI move: %v \n Time elapsed: %v \n%v", move, elapsed, stat),
					false,
					false,
					uint(checkers.BLANK),
				)

				return response, nil

			case "check":
				win, side := state.GameEnd()
				skip := false
				if (!win) {
					skip = skipIfNecessary(state)
				}
				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					"",
					skip,
					win,
					uint(side),
				)

				return response, nil
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
