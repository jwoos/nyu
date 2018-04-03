import scanner

# Give the lexer some input
with open('TEST_EXHAUSTIVE', 'r') as inf:
    scanner.lexer.input(inf.read(-1))
# lexer.input(data)

with open('TEST_EXHAUSTIVE_OUTPUT','w') as f:
    f.write("token\t" +  "token\t" + "token\n")
    f.write("number\t" + "name\t"   + "value\n")
# Tokenize

print("token\t" +  "token\t" + "token")

while True:
    tok = scanner.lexer.token()
    if not tok:
        print("FOUND EOF")
        break      # No more input
    tok.lexpos = scanner.token_dictionary[tok.type]
    with open('TEST_EXHAUSTIVE_OUTPUT','a') as f:
        f.write(str(tok.lexpos) + '\t\t' + str(tok.type) + '\t\t' + '"'+str(tok.value)+'"' + '\n')

    print(str(tok.lexpos) + '\t' + str(tok.type) + '\t' + '"'+str(tok.value)+'"')
