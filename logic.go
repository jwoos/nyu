package main

import (
	"github.com/jwoos/go_checkers"
)

type Message struct {
	Board [][]uint `json:"board"`
	Turn uint `json:"turn"`
	Info string `json:"info"`
	Skip bool `json:"skip"`
}

func NewMessage(board [][]uint, turn uint, info string, skip bool) Message {
	return Message{
		Board: board,
		Turn: turn,
		Info: info,
		Skip: skip,
	}
}

func move(state *checkers.StateByte, from checkers.Coordinate, to checkers.Coordinate) error {
	moves := state.PossibleMovesAll(state.Turn)
	okay := false
	var potential checkers.Move

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
		err = state.Validate(from, to)
		if err == nil {
			err = checkers.NewMovementError(checkers.ERROR_MOVE_INVALID)
		}
	}

	return err
}

func skipIfNecessary(state *checkers.StateByte) bool {
	if len(state.PossibleMovesAll(state.Turn)) == 0 {
		state.Skip()

		return true
	}

	return false
}
