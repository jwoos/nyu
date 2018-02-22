package main

import (
	"flag"
	"fmt"
	"os"
)

func main() {
	var debug bool
	flag.BoolVar(&debug, "debug", false, "Debug mode")

	flag.Parse()
	if len(flag.Args()) == 0 {
		fmt.Println("Must provide an input")
		os.Exit(1)
	}

	input := flag.Args()[0]

	testString := input[0:]
	table := initializeTable()

	// TODO error handling
	// TODO line handling
	for len(testString) > 0 {
		for _, rule := range table {
			indices := rule.regex.FindStringIndex(testString)

			if indices != nil && indices[0] == 0 {
				if !rule.skip || debug {
					fmt.Printf("%d %s %s\n", rule.number, rule.name, testString[indices[0]:indices[1]])
				}

				if len(testString) >= indices[1] {
					testString = testString[indices[1]:]
				}

				break
			}
		}
	}
}
