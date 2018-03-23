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
	var evaluation float64

	if who == MAX {
		// ratio of own piece to oppponent pieces
		evaluation = float64(len(state.White)) / float64(len(state.Black))

		// capture moves
		captureMoves := len(state.PossibleCaptureMovesAll(MAX))
		evaluation += 1.5 * float64(captureMoves)

		// how many possible moves
		evaluation += 0.5 * float64(len(state.PossibleMovesAll(MAX)) - captureMoves)

		// how many pieces are in danger
		danger := make(map[checkers.Coordinate]bool)
		for move, _ := range state.PossibleCaptureMovesAll(MIN) {
			danger[move.Jump] = true
		}

		// how many are safe based on how many are in danger
		evaluation += float64(len(state.White) - len(danger))
	} else {
		// ratio of own piece to oppponent pieces
		evaluation = -float64(len(state.Black)) / float64(len(state.White))

		// capture moves
		captureMoves := len(state.PossibleCaptureMovesAll(MIN))
		evaluation -= 1.5 * float64(captureMoves)

		// how many possible moves
		evaluation -= 0.5 * float64(len(state.PossibleMovesAll(MIN)) - captureMoves)

		// how many pieces are in danger
		danger := make(map[checkers.Coordinate]bool)
		for move, _ := range state.PossibleCaptureMovesAll(MAX) {
			danger[move.Jump] = true
		}

		// how many are safe based on how many are in danger
		evaluation -= float64(len(state.Black) - len(danger))
	}

	return evaluation
}

// minimax driver
func minimaxAB(state *checkers.StateByte, depth int) (checkers.Move, Stat) {
	// stat structure to keep track of information about the search
	stat := Stat{}

	lln("STARTING MINIMAX")
	stat.Start = depth
	move := max(state, math.Inf(-1), math.Inf(1), depth, &stat).Move
	lln(stat)
	return move, stat
}

// max player's move
func max(state *checkers.StateByte, alpha float64, beta float64, depth int, stat *Stat) Node {
	// check if current depth is higher than previously set max
	if stat.Start - depth > stat.Levels {
		stat.Levels = stat.Start - depth
	}
	// incremenet for node generated
	stat.Generated++
	lln("MAX")

	node := Node{}
	node.State = state
	// v value
	node.Heuristic = math.Inf(-1)

	// check if game is over
	w, s := state.GameEnd()
	if w {
		if s == MAX {
			node.Heuristic = 100
		} else {
			node.Heuristic = -100
		}

		return node
	}

	// reached the end but game isn't over so we want to use an evaluation function
	if depth == 0 {
		node.Heuristic = evaluation(node.State, MAX)
		lln("Heuristic:", node.Heuristic)
		return node
	}

	// branch from all possible moves
	moves := state.PossibleMovesAll(state.Turn)
	lln(moves)
	for move, _ := range moves {
		newState := state.Copy()
		newState.Move(move)

		// branch deeper
		v := math.Max(node.Heuristic, min(newState, alpha, beta, depth-1, stat).Heuristic)
		// if the current value is different from the heuristic, change the move
		if v != node.Heuristic {
			node.Move = move
		}
		node.Heuristic = v

		// v >= beta should it be pruned?
		if node.Heuristic >= beta {
			stat.MaxPruned++
			return node
		}

		alpha = math.Max(alpha, node.Heuristic)
	}

	return node
}

// min player's move
func min(state *checkers.StateByte, alpha float64, beta float64, depth int, stat *Stat) Node {
	if stat.Start - depth > stat.Levels {
		stat.Levels = stat.Start - depth
	}
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

	// reached the end but game isn't over so we want to use an evaluation function
	if depth == 0 {
		node.Heuristic = evaluation(node.State, MIN)
		lln("Heuristic:", node.Heuristic)
		return node
	}

	// branch from all possible moves
	moves := state.PossibleMovesAll(state.Turn)
	lln(moves)
	for move, _ := range moves {
		newState := state.Copy()
		newState.Move(move)

		// branch deeper
		v := math.Min(node.Heuristic, max(newState, alpha, beta, depth-1, stat).Heuristic)
		// if the current value is different from the heuristic, change the move
		if v != node.Heuristic {
			node.Move = move
		}
		node.Heuristic = v

		// v <= alpha - should it be pruned?
		if node.Heuristic >= beta {
			if node.Heuristic <= alpha {
				stat.MinPruned++
				return node
			}

			beta = math.Min(beta, node.Heuristic)
		}
	}

	return node
}
