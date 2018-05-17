package main

import (
	"flag"
	"fmt"
	"math/rand"
	"time"

	"github.com/jwoos/go_checkers/engine"
)

const (
	HUMAN byte = checkers.BLACK
	AI    byte = checkers.WHITE
)

var (
	FIRST      byte
	FIRST_UINT uint
	SIDE       byte
	SIDE_UINT  uint
	LEVEL      int
	DEBUG      bool
	GUI        bool
	DEPTH      int
)

func main() {
	// parse commandline flags
	flag.UintVar(&FIRST_UINT, "first", uint(HUMAN), fmt.Sprintf("Who should go first, %d for human and %d for ai", HUMAN, AI))
	flag.BoolVar(&GUI, "gui", false, "Initialize with a GUI")
	flag.BoolVar(&DEBUG, "debug", false, "Debug mode")
	flag.IntVar(&DEPTH, "depth", 16, "Depth of minimax")
	flag.IntVar(&LEVEL, "difficulty", 3, "Difficulty indicated from 1 - 3 with 3 being the hardest")
	flag.Parse()

	FIRST = byte(FIRST_UINT)
	if FIRST == HUMAN {
		SIDE = checkers.BOTTOM
	} else {
		SIDE = checkers.TOP
	}

	lln("debug:", DEBUG, "depth:", DEPTH, "difficulty:", LEVEL)

	rand.Seed(time.Now().Unix())

	if GUI {
		gui()
	} else {
		cli()
	}
}
