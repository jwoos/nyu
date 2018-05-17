/* Common logic for both gui and cli
 */
package main

import (
	"github.com/jwoos/go_checkers/engine"
)

// struct to pass messages to go app
type Message struct {
	Board [][]uint `json:"board"`
	Turn  uint     `json:"turn"`
	Info  string   `json:"info"`
	Skip  bool     `json:"skip"`
	Win   bool     `json:"win"`
	Side  uint     `json:"side"`
}

// message constructor
func NewMessage(board [][]uint, turn uint, info string, skip bool, win bool, side uint) Message {
	return Message{
		Board: board,
		Turn:  turn,
		Info:  info,
		Skip:  skip,
		Win:   win,
		Side:  side,
	}
}

// take a move and apply it
func move(state *checkers.StateByte, from checkers.Coordinate, to checkers.Coordinate) error {
	moves := state.PossibleMovesAll(state.Turn)
	okay := false
	var potential checkers.Move

	// check if it exists in the set of all valid moves
	for m, _ := range moves {
		if m.From == from && m.To == to {
			okay = true
			potential = m
			break
		}
	}

	var err error
	if okay {
		state.Move(potential)
		err = nil
	} else {
		// move isn't valid, try to generate a proper error message
		err = state.Validate(from, to)
		if err == nil {
			err = checkers.NewMovementError(checkers.ERROR_MOVE_INVALID)
		}
	}

	return err
}

// skip the turn if there are no moves remaining
func skipIfNecessary(state *checkers.StateByte) bool {
	if len(state.PossibleMovesAll(state.Turn)) == 0 {
		state.Skip()

		return true
	}

	return false
}
