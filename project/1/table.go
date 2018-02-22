package main

import (
	"fmt"
	"log"
	"regexp"
)


type Rule struct {
	number uint
	name string
	regexLiteral string
	regex *regexp.Regexp
	skip bool
}


func initializeTable() []Rule {
	table := []Rule{
		{number: 2, name: "keyword-if", regexLiteral: "if", skip: false},
		{number: 3, name: "keyword-else", regexLiteral: "else", skip: false},
		{number: 4, name: "keyword-while", regexLiteral: "while", skip: false},
		{number: 15, name: "left-par", regexLiteral: "\\(", skip: false},
		{number: 16, name: "right-par", regexLiteral: "\\)", skip: false},
		{number: 23, name: "integer-literal", regexLiteral: "[0-9]+", skip: false},
		{number: 34, name: "equal", regexLiteral: "==", skip: false},
		{number: 49, name: "ID", regexLiteral: "[a-zA-Z][a-zA-Z0-9]*", skip: false},
		{number: 99, name: "WS", regexLiteral: "[ \\t]", skip: true},
		{number: 100, name: "newline", regexLiteral: "\\n", skip: true},
		{number: 101, name: "end-of-file", regexLiteral: "", skip: true},
	}

	for i := 0; i < len(table); i++ {
		rule := &table[i]

		compiled, err := regexp.Compile(rule.regexLiteral)
		if err != nil {
			log.Fatal(err)
		}

		rule.regex = compiled
		if rule.regex == nil {
			fmt.Println("WHAT")
		}
	}

	return table
}
