package main

import (
	"math"

	"github.com/jwoos/go_checkers"
)

const (
	MIN byte = HUMAN
	MAX byte = AI
)

type Node struct {
	Move checkers.Move
	Heuristic float64
	State *checkers.StateByte
	Level uint
	Count uint
}

// check for movable and safe count
func evaluation(state *checkers.StateByte, who byte) float64 {
	lln("EVALUATION")
	if who == AI {
		return float64(len(state.White)) / float64(len(state.Black))
	} else {
		return - float64(len(state.Black)) / float64(len(state.White))
	}
}

func minimaxAB(state *checkers.StateByte, depth int) checkers.Move {
	lln("STARTING MINIMAX")
	move := max(state, math.Inf(-1), math.Inf(1), depth).Move
	return move
}

func max(state *checkers.StateByte, alpha float64, beta float64, depth int) Node {
	lln("MAX")

	node := Node{}
	node.State = state
	node.Heuristic = math.Inf(-1)

	if depth == 0 {
		node.Heuristic = evaluation(node.State, MAX)
		return node
	}

	for coord, _ := range state.White {
		moves := state.PossibleMoves(coord)
		lln(coord, moves)

		for _, move := range moves {
			newState := state.Copy()
			newState.Move(move)

			v := math.Max(node.Heuristic, min(newState, alpha, beta, depth - 1).Heuristic)
			if v != node.Heuristic {
				node.Move = move
			}
			node.Heuristic = v

			if node.Heuristic >= beta {
				return node
			}

			alpha = math.Max(alpha, node.Heuristic)
		}
	}

	return node
}

func min(state *checkers.StateByte, alpha float64, beta float64, depth int) Node {
	lln("MIN")
	lln(state)

	node := Node{}
	node.State= state
	node.Heuristic = math.Inf(1)

	if depth == 0 {
		node.Heuristic = evaluation(node.State, MIN)
		return node
	}

	for coord, _ := range state.Black {
		moves := state.PossibleMoves(coord)
		lln(coord, moves)

		for _, move := range moves {
			newState := state.Copy()
			newState.Move(move)

			v := math.Min(node.Heuristic, max(newState, alpha, beta, depth - 1).Heuristic)
			if v != node.Heuristic {
				node.Move = move
			}
			node.Heuristic = v

			if node.Heuristic <= alpha {
				return node
			}

			beta = math.Min(beta, node.Heuristic)
		}
	}

	return node
}
