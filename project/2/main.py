from parser.parser import parser
from scanner.scanner import lexer


def main():
    s = open('test.txt').read()
    result = parser.parse(s)
    print(result)

if __name__ == '__main__':
    main()
