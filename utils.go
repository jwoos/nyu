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
