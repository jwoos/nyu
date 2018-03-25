package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"

	"github.com/jwoos/go_checkers"

	"github.com/asticode/go-astilectron"
	"github.com/asticode/go-astilectron-bootstrap"
	"github.com/asticode/go-astilog"
	"github.com/pkg/errors"
)

const (
	HUMAN byte = checkers.BLACK
	AI    byte = checkers.WHITE
)

var (
	LEVEL int
	DEBUG bool
	GUI  bool
	DEPTH int
)


func gui() {
	var (
		AppName string
		w       *astilectron.Window
	)

	astilog.FlagInit()

	// Run bootstrap
	err := bootstrap.Run(bootstrap.Options{
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
		}},,
		OnWait: func(_ *astilectron.Astilectron, iw *astilectron.Window, _ *astilectron.Menu, _ *astilectron.Tray, _ *astilectron.Menu) error {
			w = iw
			go func() {
				time.Sleep(5 * time.Second)
				if err := bootstrap.SendMessage(w, "check.out.menu", "Don't forget to check out the menu!"); err != nil {
					astilog.Error(errors.Wrap(err, "sending check.out.menu event failed"))
				}
			}()
			return nil
		},
		MessageHandler: nil,
		RestoreAssets:  RestoreAssets,
		WindowOptions: &astilectron.WindowOptions{
			BackgroundColor: astilectron.PtrStr("#333"),
			Center:          astilectron.PtrBool(true),
			Height:          astilectron.PtrInt(700),
			Width:           astilectron.PtrInt(700),
		},
	})

	if err != nil {
		astilog.Fatal(errors.Wrap(err, "running bootstrap failed"))
	}
}

func cli() {
	fmt.Println("Will you go first? (y/n)")
	reader := bufio.NewReader(os.Stdin)
	text, err := reader.ReadString('\n')
	if err != nil {
		log.Fatal(err)
	}

	var firstMove byte
	var side byte

	if strings.Trim(text, "\n ") == "y" {
		firstMove = HUMAN
		side = checkers.BOTTOM
	} else {
		firstMove = AI
		side = checkers.TOP
	}

	// instantiate rule
	rule := checkers.NewRule(6, 6, firstMove, side, 2, false, false, false)

	// instantitate state
	state := checkers.NewStateByte(rule, true)
	fmt.Printf("%#v \n\n", state)

	won := checkers.BLANK

	fmt.Println("\nStarting game\n")
	// keep looping until game is over
	for true {
		w, s := state.GameEnd()
		lln("Game won:", w, s)
		if w {
			won = s
			break
		}

		if state.Turn == HUMAN {
			fmt.Println("Human (BLACK) move")

			moves := state.PossibleMovesAll(state.Turn)
			if len(moves) == 0 {
				fmt.Println("No more possible moves, skipping")
				fmt.Println()
				state.Skip()
				continue
			}

			fmt.Println("Enter the move specifying the piece first and then the move: p1,p2 c1,c2")
			text, err = reader.ReadString('\n')
			if err != nil {
				log.Fatal(err)
			}
			fmt.Println()

			spaceSplit := strings.Split(strings.Trim(text, " \n"), " ")
			if len(spaceSplit) != 2 {
				fmt.Println("Invalid input")
				continue
			}

			fromText := strings.Split(spaceSplit[0], ",")
			toText := strings.Split(spaceSplit[1], ",")

			if len(fromText) != 2 || len(toText) != 2 {
				fmt.Println("Invalid input")
				continue
			}

			fromRow, err := strconv.Atoi(fromText[0])
			if err != nil {
				fmt.Println(err)
				continue
			}
			fromColumn, err := strconv.Atoi(fromText[1])
			if err != nil {
				fmt.Println(err)
				continue
			}

			toRow, err := strconv.Atoi(toText[0])
			if err != nil {
				fmt.Println(err)
				continue
			}
			toColumn, err := strconv.Atoi(toText[1])
			if err != nil {
				fmt.Println(err)
				continue
			}

			from := checkers.NewCoordinate(fromRow, fromColumn)
			to := checkers.NewCoordinate(toRow, toColumn)

			okay := false
			var move checkers.Move

			for m, _ := range moves {
				if m.From == from && m.To == to {
					okay = true
					move = m
					break
				}
			}

			if okay {
				state.Move(move)
			} else {
				err := state.Validate(from, to)
				if err != nil {
					fmt.Println(err)
				} else {
					fmt.Println(checkers.ERROR_MOVE_INVALID)
				}
			}
		} else {
			// AI move
			fmt.Println("AI (WHITE) move")
			if len(state.PossibleMovesAll(state.Turn)) == 0 {
				fmt.Println("No more possible moves, skipping")
				fmt.Println()
				state.Skip()
				continue
			}

			start := time.Now()
			move, stat := minimaxAB(state, DEPTH)
			elapsed := time.Since(start)

			fmt.Println("AI move:", move)
			fmt.Println("Time elapsed:", elapsed)
			fmt.Println(stat)
			fmt.Println()
			state.Move(move)
		}

		fmt.Printf("%#v \n\n", state)
	}

	switch won {
	case AI:
		fmt.Println("You lost!")
	case HUMAN:
		fmt.Println("You won!")
	case checkers.BLANK:
		fmt.Println("It's a tie!")
	}
}


func main() {
	flag.BoolVar(&GUI, "GUI", false, "Initialize with a GUI")
	flag.BoolVar(&DEBUG, "debug", false, "Debug mode")
	flag.IntVar(&DEPTH, "depth", 20, "Depth of minimax")
	flag.IntVar(&LEVEL, "difficulty", 3, "Difficulty indicated from 1 - 3 with 3 being the hardest")
	flag.Parse()

	lln("debug:", DEBUG, "depth:", DEPTH, "difficulty:", LEVEL)

	rand.Seed(time.Now().Unix())

	if GUI {
		cli()
	} else {
		gui()
	}
}
