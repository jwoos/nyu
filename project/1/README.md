# Compiler Design and Construction Project 1

## Build
The files should be placed in a directory on your `$GOPATH`. Move to that directory and run: `go build`. That should result in a binary with the same name as the directory.

## Run
```
./nyu_csuy-3943-project1 [--debug] [--table=<NUM>] [input]
```

- `--debug`: determines whether to ouput spaces, new lines and EOF
- `--table=<NUM>`: NUM should be 1 through 4 to determine which table to use. It will default to 1
- `input`: This is the input to the program, it should be enclosed in quotations to keep new lines. This is optional and the program will read from stdin if not provided this argument
	- If reading from stdin `ctrl-D` will indicate EOF

## Sample Inputs
### Table 1
```
$ ./nyu_csuy-3943-project1 --table=1
if (x == 10)

2 keyword-if if
15 left-par (
49 ID x
34 equal ==
23 integer-literal 10
16 right-par )
```

```
$ ./nyu_csuy-3943-project1 --table=1
if (x2 == 10)   
else

2 keyword-if if
15 left-par (
49 ID x2
34 equal ==
23 integer-literal 10
16 right-par )
3 keyword-else else
```

```
$ ./nyu_csuy-3943-project1 --table=1
test >= what  
asd = 10

49 ID test
Invalid token on line 1: >=
49 ID what
49 ID asd
Invalid token on line 2: =
23 integer-literal 10
```

### Table 2
```
./nyu_csuy-3943-project1 --table=2        
if (x == 10) {
	y = 10
}

1 if if
15 LPAR (
10 ID x
11 op ==
23 int 10
16 RPAR )
19 LBRC {
10 ID y
11 op =
23 int 10
20 RBRC }
```

```
./nyu_csuy-3943-project1 --table=2
if (a[0]) {
	x = (y != 0xABCDEF);
}

1 if if
15 LPAR (
10 ID a
17 LBR [
23 int 0
18 RBR ]
16 RPAR )
19 LBRC {
10 ID x
11 op =
15 LPAR (
10 ID y
11 op !=
23 int 0xABCDEF
16 RPAR )
Invalid token on line 2: ;
20 RBRC }
```

### Table 3
```
./nyu_csuy-3943-project1 --table=3
(x = 10)

15 LPAR (
1 atom x
1 atom =
1 atom 10
16 RPAR )
1 atom
```

```
./nyu_csuy-3943-project1 --table=3
 (if nil
     (list 1 2 "foo")
     (list 3 4 "bar"))
15 LPAR (
1 atom if
1 atom nil

15 LPAR (
1 atom list
1 atom 1
1 atom 2
1 atom "foo"
16 RPAR )
1 atom 

15 LPAR (
1 atom list
1 atom 3
1 atom 4
1 atom "bar"
16 RPAR )
16 RPAR )
1 atom
```

### Table 4
```
/nyu_csuy-3943-project1 --table=4
int main() {
        float a = 0.01;           
	float b = 0.02;
	float c = a + b;
	return 0;
}

1 int int
10 ID main
15 LPAR (
16 RPAR )
19 LBRACE {
2 float float
10 ID a
11 op =
24 float 0.01
21 semi ;
2 float float
10 ID b
11 op =
24 float 0.02
21 semi ;
2 float float
10 ID c
11 op =
10 ID a
11 op +
10 ID b
21 semi ;
6 return return
23 int 0
21 semi ;
20 RBRACE }
```
