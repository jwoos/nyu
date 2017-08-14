'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw7q2.py

Explanation
-----------
I used a for loop inside of a for loop to get the results I wanted. The inside for loop would run until it was finished and only then would the outside loop be allowed to continue.
So I used the outside for loop to set the row and the inside to set the columns. I specified the rows and columns beforehand and looped over the range with the start and end supplied.
It starts at 1 and since the end is exclusive I had to add 1 to include the number itself. The print method with the optional end parameter allowed me to print on the same line with a specififed amount of space between each print.

'''

rows = 5
columns = 10

for exponent in range(1, rows + 1):
    for base in range(1, columns + 1):
        print(base**exponent, end='\t')
    print()
