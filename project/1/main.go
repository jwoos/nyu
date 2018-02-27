package main

import (
	"flag"
	"fmt"
	"os"
)

func main() {
	var debug bool
	flag.BoolVar(&debug, "debug", false, "Debug mode")

	var tableNum uint
	flag.UintVar(&tableNum, "table", 1, "Table number")

	flag.Parse()
	if len(flag.Args()) == 0 {
		fmt.Println("Must provide an input")
		os.Exit(1)
	}

	input := flag.Args()[0]

	testString := input[0:]
	table := initializeTable(tableNum)
	cache := make([][]int, len(table))
	invalid := false
	lineNumber := 1

	for len(testString) > 0 {
		found := false

		for i, rule := range table {
			indices := rule.regex.FindStringIndex(testString)
			cache[i] = indices

			if indices != nil && indices[0] == 0 {
				if !rule.skip || debug {
					fmt.Printf("%d %s %s\n", rule.number, rule.name, testString[indices[0]:indices[1]])
				}

				if rule.name == "newline" {
					lineNumber++
				}

				if len(testString) >= indices[1] {
					testString = testString[indices[1]:]
				}

				found = true

				break
			}
		}

		if !found {
			invalid = true
			x := len(testString)

			for _, indices := range cache {
				if indices != nil {
					x = min(x, indices[0])
				}
			}

			fmt.Printf("Invalid token on line %d: %s\n", lineNumber, testString[:x])
			testString = testString[x:]
		}
	}

	// if there are any invalids, exit with error status
	if invalid {
		os.Exit(1)
	}
}
