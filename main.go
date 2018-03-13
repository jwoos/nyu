package main


import (
	"fmt"

	"github.com/jwoos/go_checkers"
)


func main() {
	// instantiate rule
	rule := checkers.NewRule(6, 6, false, false, false)

	// instantitate state
	state := checkers.NewState(rule, checkers.BLACK)

	fmt.Print(state)
}
