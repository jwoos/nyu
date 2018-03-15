package main

import (
	"fmt"
	"math"

	"github.com/jwoos/go_checkers"
)

const (
	MIN byte = HUMAN
	MAX byte = AI
)

type Node struct {
	Move      checkers.Move
	Heuristic float64
	State     *checkers.StateByte
}

type Stat struct {
	Start int

	MinPruned uint
	MaxPruned uint
	Levels int
	Generated uint
}

func (stat Stat) String() string {
	return fmt.Sprintf("Nodes Generated: %d Max depth: %d Min Pruned: %d Max Pruned %d", stat.Generated, stat.Levels, stat.MinPruned, stat.MaxPruned)
}

func (stat Stat) GoString() string {
	return stat.String()
}

// check for movable and safe count
func evaluation(state *checkers.StateByte, who byte) float64 {
	lln("EVALUATION")
	if who == MAX {
		return float64(len(state.White)) / float64(len(state.Black)) + float64(len(state.PossibleMovesAll(who)))
	} else {
		return -float64(len(state.Black)) / float64(len(state.White)) - float64(len(state.PossibleMovesAll(who)))
	}
}

func minimaxAB(state *checkers.StateByte, depth int) (checkers.Move, Stat) {
	stat := Stat{}

	lln("STARTING MINIMAX")
	move := max(state, math.Inf(-1), math.Inf(1), depth, &stat).Move
	lln(stat)
	return move, stat
}

func max(state *checkers.StateByte, alpha float64, beta float64, depth int, stat *Stat) Node {
	stat.Generated++
	lln("MAX")

	node := Node{}
	node.State = state
	node.Heuristic = math.Inf(-1)

	w, s := state.GameEnd()
	if w {
		if s == MAX {
			node.Heuristic = 100
		} else {
			node.Heuristic = -100
		}

		return node
	}

	if depth == 0 {
		node.Heuristic = evaluation(node.State, MAX)
		lln("Heuristic:", node.Heuristic)
		return node
	}

	moves := state.PossibleMovesAll(state.Turn)
	lln(moves)
	for move, _ := range moves {
		newState := state.Copy()
		newState.Move(move)

		v := math.Max(node.Heuristic, min(newState, alpha, beta, depth-1, stat).Heuristic)
		if v != node.Heuristic {
			node.Move = move
		}
		node.Heuristic = v

		if node.Heuristic >= beta {
			stat.MaxPruned++
			return node
		}

		alpha = math.Max(alpha, node.Heuristic)
	}

	return node
}

func min(state *checkers.StateByte, alpha float64, beta float64, depth int, stat *Stat) Node {
	stat.Generated++
	lln("MIN")

	node := Node{}
	node.State = state
	node.Heuristic = math.Inf(1)

	w, s := state.GameEnd()
	if w {
		if s == MAX {
			node.Heuristic = 100
		} else {
			node.Heuristic = -100
		}

		return node
	}

	if depth == 0 {
		node.Heuristic = evaluation(node.State, MIN)
		lln("Heuristic:", node.Heuristic)
		return node
	}

	moves := state.PossibleMovesAll(state.Turn)
	lln(moves)
	for move, _ := range moves {
		newState := state.Copy()
		newState.Move(move)

		v := math.Min(node.Heuristic, max(newState, alpha, beta, depth-1, stat).Heuristic)
		if v != node.Heuristic {
			node.Move = move
		}
		node.Heuristic = v

		if node.Heuristic <= alpha {
			stat.MinPruned++
			return node
		}

		beta = math.Min(beta, node.Heuristic)
	}

	return node
}
