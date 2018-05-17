/* AI's searching algorithm
 */
package main

import (
	"fmt"
	"math"

	"github.com/jwoos/go_checkers/engine"
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
	Levels    int
	Generated uint
}

func (stat Stat) String() string {
	return fmt.Sprintf("Nodes Generated: %d Max depth: %d Min Pruned: %d Max Pruned %d", stat.Generated, stat.Levels, stat.MinPruned, stat.MaxPruned)
}

func (stat Stat) GoString() string {
	return stat.String()
}

// easiest evaluation
func evaluation1(state *checkers.StateByte, who byte) float64 {
	var ownPieces map[checkers.Coordinate]bool
	var opponentPieces map[checkers.Coordinate]bool

	if who == MAX {
		ownPieces = state.White
		opponentPieces = state.Black
	} else {
		ownPieces = state.Black
		opponentPieces = state.White
	}

	ownPieceCount := float64(len(ownPieces))
	opponentPieceCount := float64(len(opponentPieces))

	eval := ownPieceCount - opponentPieceCount

	if who == MIN {
		eval *= -1
	}

	return eval
}

// medium evaluation
func evaluation2(state *checkers.StateByte, who byte) float64 {
	var own byte
	var opponent byte

	var ownPieces map[checkers.Coordinate]bool
	var opponentPieces map[checkers.Coordinate]bool

	if who == MAX {
		own = MAX
		opponent = MIN

		ownPieces = state.White
		opponentPieces = state.Black
	} else {
		own = MIN
		opponent = MAX

		ownPieces = state.Black
		opponentPieces = state.White
	}

	ownPieceCount := float64(len(ownPieces))
	opponentPieceCount := float64(len(opponentPieces))

	ownPossibleMoves := state.PossibleMovesAll(own)
	opponentPossibleMoves := state.PossibleMovesAll(opponent)

	eval := 10 * (ownPieceCount - opponentPieceCount)
	eval += 5 * (float64(len(ownPossibleMoves)) - float64(len(opponentPossibleMoves)))

	if who == MIN {
		eval *= -1
	}

	return eval
}

// hardest evaluation
func evaluation3(state *checkers.StateByte, who byte) float64 {
	var own byte
	var opponent byte

	var ownPieces map[checkers.Coordinate]bool
	var opponentPieces map[checkers.Coordinate]bool

	if who == MAX {
		own = MAX
		opponent = MIN

		ownPieces = state.White
		opponentPieces = state.Black
	} else {
		own = MIN
		opponent = MAX

		ownPieces = state.Black
		opponentPieces = state.White
	}

	ownPieceCount := float64(len(ownPieces))
	opponentPieceCount := float64(len(opponentPieces))

	ownPossibleMoves := state.PossibleMovesAll(own)
	opponentPossibleMoves := state.PossibleMovesAll(opponent)

	var ownCoordinateCache map[checkers.Coordinate]bool
	ownSafePieces := ownPieceCount
	for m, _ := range opponentPossibleMoves {
		if (m.Jump != checkers.NO_JUMP) && ownCoordinateCache[m.Jump] {
			ownCoordinateCache[m.Jump] = true
			ownSafePieces--
		}
	}
	var opponentCoordinateCache map[checkers.Coordinate]bool
	opponentSafePieces := opponentPieceCount
	for m, _ := range opponentPossibleMoves {
		if (m.Jump != checkers.NO_JUMP) && opponentCoordinateCache[m.Jump] {
			opponentCoordinateCache[m.Jump] = true
			opponentSafePieces--
		}
	}

	eval := 15 * (ownPieceCount - opponentPieceCount)
	eval += 5 * (float64(len(ownPossibleMoves)) - float64(len(opponentPossibleMoves)))
	eval += 5 * (ownSafePieces - opponentSafePieces)

	if who == MIN {
		eval *= -1
	}

	return eval
}

// evaluation driver
func evaluation(state *checkers.StateByte, who byte) float64 {
	lln("EVALUATION")

	switch LEVEL {
	case 1:
		return evaluation1(state, who)

	case 2:
		return evaluation2(state, who)

	case 3:
		fallthrough

	default:
		return evaluation3(state, who)
	}
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
	if stat.Start-depth > stat.Levels {
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
		switch s {
		case MAX:
			node.Heuristic = 100
		case MIN:
			node.Heuristic = -100
		default:
			node.Heuristic = 0
		}

		lln("Game Over Heuristic:", node.Heuristic)
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
		node.Move = move
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
	if stat.Start-depth > stat.Levels {
		stat.Levels = stat.Start - depth
	}
	stat.Generated++
	lln("MIN")

	node := Node{}
	node.State = state
	// v value
	node.Heuristic = math.Inf(1)

	// check if game is over
	w, s := state.GameEnd()
	if w {
		switch s {
		case MAX:
			node.Heuristic = 100
		case MIN:
			node.Heuristic = -100
		default:
			node.Heuristic = 0
		}

		lln("Game Over Heuristic:", node.Heuristic)
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
		node.Move = move
		node.Heuristic = v

		// v <= alpha - should it be pruned?
		if node.Heuristic <= alpha {
			stat.MinPruned++
			return node
		}

		beta = math.Min(beta, node.Heuristic)
	}

	return node
}
