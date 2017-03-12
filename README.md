# CryptoProjects
Crypto Projects for Spring '17

To compile the program run:
```
make main
```

To run the decryption program:
```
./main decrypt
```
After you run that, it will ask for input. It will take any amount of input until enter is pressed.
If no input is passed in, it will autmatically generate plaintext, encrypt it and use that as the text to decrypt. It will print out the plaintext and key as well.

**PLEASE** avoid nonalphabet or space characters as it will inevitably segfault.

When it is finished, it will output the proposed plaintext, the score, and the proposed key.


### Calculating Digram Frequencies
```
$ cd other
$ ./gen.sh
```
