from parser.parser import parser
from scanner.scanner import lexer


def main():
    while True:
        try:
            s = input('input > ')
        except EOFError:
            break
        if not s: continue
        result = parser.parse(s)
        print(result)

if __name__ == '__main__':
    main()
