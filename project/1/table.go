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


func initializeTable(num uint) []Rule {
	var table []Rule

	switch num {
	case 1:
		table = []Rule{
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
			{number: 101, name: "end-of-file", regexLiteral: "$", skip: true},
		}

	case 2:
		table = []Rule{
			{number: 1, name: "if", regexLiteral: "if", skip: false},
			{number: 2, name: "while", regexLiteral: "while", skip: false},
			{number: 3, name: "else", regexLiteral: "else", skip: false},
			{number: 4, name: "case", regexLiteral: "case", skip: false},
			{number: 5, name: "switch", regexLiteral: "switch", skip: false},
			{number: 10, name: "ID", regexLiteral: "[a-zA-Z_][a-zA-Z_0-9]*", skip: false},
			{number: 11, name: "op", regexLiteral: "\\+|-|\\*|\\/|\\^|~|={1,2}|<=|=>|\\+=|-=|\\*=|\\/=|!=", skip: false},
			{number: 15, name: "LPAR", regexLiteral: "\\(", skip: false},
			{number: 16, name: "RPAR", regexLiteral: "\\)", skip: false},
			{number: 17, name: "LBR", regexLiteral: "\\[", skip: false},
			{number: 18, name: "RBR", regexLiteral: "\\]", skip: false},
			{number: 19, name: "LBRC", regexLiteral: "{", skip: false},
			{number: 20, name: "RBRC", regexLiteral: "}", skip: false},
			{number: 24, name: "fixed", regexLiteral: "[0-9]*(\\.[0-9]|[0-9]\\.)[0-9]*", skip: false},
			{number: 23, name: "int", regexLiteral: "[1-9][0-9]*|0x[0-9A-F]+|0[0-7]*", skip: false},
			{number: 99, name: "WS", regexLiteral: "[ \\t]", skip: true},
			{number: 100, name: "newline", regexLiteral: "\\n", skip: true},
			{number: 101, name: "end-of-file", regexLiteral: "$", skip: true},
		}

	case 3:
		table = []Rule{
			{number: 1, name: "atom", regexLiteral: "[^() \t']+", skip: false},
			{number: 2, name: "quote", regexLiteral: "'", skip: false},
			{number: 3, name: "string", regexLiteral: "\"[^\"\n]*\"", skip: false},
			{number: 15, name: "LPAR", regexLiteral: "\\(", skip: false},
			{number: 16, name: "RPAR", regexLiteral: "\\)", skip: false},
			{number: 99, name: "WS", regexLiteral: "[ \\t]", skip: true},
			{number: 100, name: "newline", regexLiteral: "\\n", skip: true},
			{number: 101, name: "end-of-file", regexLiteral: "$", skip: true},
		}

	case 4:
		table = []Rule{
			{number: 1, name: "int", regexLiteral: "int", skip: false},
			{number: 2, name: "float", regexLiteral: "float", skip: false},
			{number: 3, name: "if", regexLiteral: "if", skip: false},
			{number: 4, name: "else", regexLiteral: "else", skip: false},
			{number: 5, name: "while", regexLiteral: "while", skip: false},
			{number: 6, name: "return", regexLiteral: "return", skip: false},
			{number: 7, name: "read", regexLiteral: "read", skip: false},
			{number: 8, name: "write", regexLiteral: "write", skip: false},
			{number: 10, name: "ID", regexLiteral: "[a-zA-Z_][a-zA-Z_0-9]*", skip: false},
			{number: 11, name: "op", regexLiteral: "\\+|-|\\*|/|=", skip: false},
			{number: 15, name: "LPAR", regexLiteral: "\\(", skip: false},
			{number: 16, name: "RPAR", regexLiteral: "\\)", skip: false},
			{number: 19, name: "LBRACE", regexLiteral: "{", skip: false},
			{number: 20, name: "RBRACE", regexLiteral: "}", skip: false},
			{number: 21, name: "semi", regexLiteral: ";", skip: false},
			{number: 22, name: "comma", regexLiteral: ",", skip: false},
			{number: 24, name: "float", regexLiteral: "[0-9]+\\.[0-9]+", skip: false},
			{number: 23, name: "int", regexLiteral: "[0-9]+", skip: false},
			{number: 99, name: "WS", regexLiteral: "[ \\t]", skip: true},
			{number: 100, name: "newline", regexLiteral: "\\n", skip: true},
			{number: 101, name: "end-of-file", regexLiteral: "$", skip: true},
		}
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
