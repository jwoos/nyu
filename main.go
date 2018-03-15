package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"time"

	"github.com/jwoos/go_checkers"
)

const (
	HUMAN byte = checkers.BLACK
	AI    byte = checkers.WHITE
)

var DEBUG bool
var DEPTH int

func main() {
	flag.BoolVar(&DEBUG, "debug", false, "Debug mode")
	flag.IntVar(&DEPTH, "depth", 15, "Depth of minimax")
	flag.Parse()

	fmt.Println("Will you go first? (y/n)")
	reader := bufio.NewReader(os.Stdin)
	text, err := reader.ReadString('\n')
	if err != nil {
		log.Fatal(err)
	}

	var firstMove byte
	var side int

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
			fmt.Println("AI (WHITE) move")
			if len(state.PossibleMovesAll(state.Turn)) == 0 {
				fmt.Println("No more possible moves, skipping")
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
