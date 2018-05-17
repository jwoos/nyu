package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"time"

	"github.com/jwoos/go_checkers/engine"
)

func cli() {
	fmt.Println("Starting game\n")
	// instantiate rule
	rule := checkers.NewRule(6, 6, FIRST, SIDE, 2, false, false, false)

	// instantitate state
	state := checkers.NewStateByte(rule, true)
	fmt.Printf("%#v \n\n", state)

	won := checkers.BLANK

	reader := bufio.NewReader(os.Stdin)

	var text string
	var err error

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

			if skipIfNecessary(state) {
				fmt.Println("No more possible moves, skipping")
				fmt.Println()
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

			err = move(state, from, to)
			if err != nil {
				fmt.Println(err)
			}

		} else {
			// AI move
			fmt.Println("AI (WHITE) move")
			if skipIfNecessary(state) {
				fmt.Println("No more possible moves, skipping")
				fmt.Println()
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
