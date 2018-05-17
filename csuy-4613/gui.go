package main

import (
	"encoding/json"
	"fmt"
	"log"
	"time"

	"github.com/jwoos/go_checkers/engine"

	"github.com/asticode/go-astilectron"
	"github.com/asticode/go-astilectron-bootstrap"
)

func gui() {
	// Vars
	var AppName string
	var rule checkers.Rule
	var state *checkers.StateByte

	// instantiate the game
	rule = checkers.NewRule(6, 6, FIRST, SIDE, 2, false, false, false)
	state = checkers.NewStateByte(rule, true)

	// run the gui
	err := bootstrap.Run(bootstrap.Options{
		AstilectronOptions: astilectron.Options{
			AppName:            AppName,
			AppIconDarwinPath:  "resources/icon.icns",
			AppIconDefaultPath: "resources/icon.png",
		},
		Debug:    DEBUG,
		Homepage: "index.html",
		MenuOptions: []*astilectron.MenuItemOptions{{
			Label: astilectron.PtrStr("File"),
			SubMenu: []*astilectron.MenuItemOptions{
				{Role: astilectron.MenuItemRoleClose},
			},
		}},
		OnWait: nil,
		/* handle passing messages between electron and the go app
		 * messages are keyed by the name
		 */
		MessageHandler: func(w *astilectron.Window, message bootstrap.MessageIn) (interface{}, error) {
			switch message.Name {

			// called when electron is done setting up
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

			// human moves
			case "human-move":
				fmt.Println("Human (BLACK) move")

				var payload map[string][]int
				json.Unmarshal(message.Payload, &payload)

				from := checkers.NewCoordinate(payload["from"][0], payload["from"][1])
				to := checkers.NewCoordinate(payload["to"][0], payload["to"][1])

				err := move(state, from, to)
				if err != nil {
					fmt.Println(err)
					return err, err
				}

				fmt.Printf("%#v \n\n", state)

				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					"",
					false,
					false,
					uint(checkers.BLANK),
				)

				return response, nil

			// ai moves
			case "ai-move":
				start := time.Now()
				m, stat := minimaxAB(state, DEPTH)
				elapsed := time.Since(start)

				fmt.Println("AI move:", m)
				fmt.Println("Time elapsed:", elapsed)
				fmt.Println(stat)
				fmt.Println()

				state.Move(m)

				fmt.Printf("%#v \n\n", state)

				response := NewMessage(
					arrayBytetoUint(state.Board),
					uint(state.Turn),
					fmt.Sprintf("AI move: %v \n Time elapsed: %v \n%v", m, elapsed, stat),
					false,
					false,
					uint(checkers.BLANK),
				)

				return response, nil

			// check if game ended or someone should skip their turn
			case "check":
				fmt.Println("checking")
				fmt.Println()
				win, side := state.GameEnd()
				skip := false

				if !win {
					skip = skipIfNecessary(state)
					if skip {
						fmt.Println("No more possible moves, skipping")
						fmt.Println()
					}
				} else {
					switch side {
					case AI:
						fmt.Println("You lost!")
					case HUMAN:
						fmt.Println("You won!")
					case checkers.BLANK:
						fmt.Println("It's a tie!")
					}
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

	if err != nil {
		log.Fatal(err)
	}
}
