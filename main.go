package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"

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

	fmt.Println("\nStarting game\n")

	for true {
		fmt.Printf("%#v \n\n", state)

		if state.Turn == HUMAN {
			fmt.Println("Human (BLACK) move")
			fmt.Println("Enter the move specifying the piece first and then the move: p1,p2 c1,c2")
			text, err = reader.ReadString('\n')
			if err != nil {
				log.Fatal(err)
			}
			fmt.Println()

			spaceSplit := strings.Split(strings.Trim(text, " \n"), " ")
			fromText := strings.Split(spaceSplit[0], ",")
			toText := strings.Split(spaceSplit[1], ",")

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
			moves := state.PossibleMoves(from)

			if _, okay := moves[to]; okay {
				state.Move(moves[to])
			} else {
				fmt.Println(state.Validate(from, to))
			}
		} else {
			fmt.Println("AI (WHITE) move")
			fmt.Println()
			move := minimaxAB(state, DEPTH)
			state.Move(move)
		}
	}
}
