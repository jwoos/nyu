# NYU CS-UY 4613 (Artificial Intelligence) Project
Minimax with Alpha-Beta Pruning in Checkers

## Build
You must have `go` installed as well as `dep`.

Built with the following:

```shell
% go version
go version go1.10 linux/amd64

% dep version
dep:
 version     : v0.4.1
 build date  : 2018-01-24
 git hash    : 37d9ea0a
 go version  : go1.9.1
 go compiler : gc
 platform    : linux/amd64
```

Refer to the following for installation:
- https://golang.org/doc/install
- https://github.com/golang/dep

1. Move the directory to your `$GOPATH`

```shell
% mkdir -p $GOPATH/src/
# assuming directory is called project
% mv project $GOPATH/src/
```

2. Pull down the dependency

```shell
% dep ensure
```

3. Build it - this should place an executable in your directory with the same name as the directory

```shell
% go build
```

4. Run it

```shell
# again assuming the directory was called project
% ./project
```

## Design

I decided to split the work up into two pieces - a checkers engine that has all the necessary structures and methods to run a game as well as the actual driver program with the AI.

### go_checkers 

This is located at: https://github.com/jwoos/go_checkers

The main structure of this package is `StateByte` which keeps track of the game state as a 2D matrix of `byte`s which represent pieces. The other key structure is `Rule` which defines the ruleset for the game - I made it this way as I wanted a reusable checkers engine but the assignment deviated from the standard rules of checkers. The other files were implemented to be used for a full game of checkers: `StateByte` and `State` are almost identical except the former uses a 2D matrix of `byte`s for the game board while the latter uses `Piece`s.

`StateByte` has various methods associated with it that help drive a game. For instance it can get all the possible moves for a current side by `PossibleMovesAll`. It can also return only the possible moves for a given piece with `PossibleMoves`. It has analogous functions to return only capture moves in the forms of `PossibleCaptureMoves` and `PossibleCaptureMovesAll`.

`StateByte` is also capable of doing error checks and checking if the game has ended. This basically takes care of all the minute details of actually playing a chess game from moving a piece to validating that a move is correct. It also implements the `Stringer` interface for pretty printing out the game state.

### Driver

This is the driver of the actual program. At its core, it takes the checkers package and makes use of it to run an actual game. It also includes a file for 