package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"

	"github.com/jwoos/go_checkers"
)

const (
	HUMAN int = checkers.BLACK
	AI    int = checkers.WHITE
)

func main() {
	fmt.Println("Will you go first? (y/n)")
	reader := bufio.NewReader(os.Stdin)
	text, err := reader.ReadString('\n')
	if err != nil {
		log.Fatal(err)
	}

	var firstMove int
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
	state := checkers.NewState(rule, true)

	fmt.Println("\nStarting game\n")

	for true {
		fmt.Printf("%#v \n", state)
		if state.Turn == HUMAN {
			fmt.Println("Enter the move specifying the piece first and then the move: p1,p2 c1,c2")
			text, err = reader.ReadString('\n')
			if err != nil {
				log.Fatal(err)
			}

			spaceSplit := strings.Split(strings.Trim(text, " \n"), " ")
			from := strings.Split(spaceSplit[0], ",")
			to := strings.Split(spaceSplit[1], ",")

			fromRow, err := strconv.Atoi(from[0])
			if err != nil {
				fmt.Println(err)
				continue
			}
			fromColumn, err := strconv.Atoi(from[1])
			if err != nil {
				fmt.Println(err)
				continue
			}

			toRow, err := strconv.Atoi(to[0])
			if err != nil {
				fmt.Println(err)
				continue
			}
			toColumn, err := strconv.Atoi(to[1])
			if err != nil {
				fmt.Println(err)
				continue
			}

			piece := state.Board[fromRow][fromColumn]

			err = state.MovePieceTo(piece, checkers.NewCoordinate(toRow, toColumn))
			if err != nil {
				fmt.Println(err)
				continue
			}
		} else {
			log.Fatal("should not be here")
		}
	}
}
