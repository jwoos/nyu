package main

import (
	"log"
	"math"
)

func round(f float64) int {
	if math.Abs(f) < 0.5 {
		return 0
	}

	return int(f + math.Copysign(0.5, f))
}

func arrayBytetoUint(a [][]byte) [][]uint {
	uintBoard := make([][]uint, 6)
	for i, row := range a {
		uintBoard[i] = make([]uint, 6)
		for j, val := range row {
			uintBoard[i][j] = uint(val)
		}
	}

	return uintBoard
}

func lf(format string, args ...interface{}) {
	if DEBUG {
		log.Printf(format, args...)
	}
}

func l(args ...interface{}) {
	if DEBUG {
		log.Print(args...)
	}
}

func lln(args ...interface{}) {
	if DEBUG {
		log.Println(args...)
	}
}
