package main

import (
	"github.com/jwoos/go_checkers"
)

const (
	MIN byte = HUMAN
	MAX byte = AI
)

type Node struct {
	move checkers.Move
	heuristic float64
	state [][]byte
}

// check for movable and white count
func evaluation(state *checkers.State, who byte) float64 {
	if who == AI {
		return float64(len(state.White)) / float64(len(state.Black))
	} else {
		return - float64(len(state.Black)) / float64(len(state.White))
	}
}

/*
 *func minimax() checkers.Move {
 *}
 */

/*
 *func max() checkers.Move {}
 *
 *func min() checkers.Move {}
 */
