'use strict';

let global = {};

const WHITE = 1;
const BLACK = 2;

const post = (outgoing) => {
	return new Promise((resolve, reject) => {
		astilectron.sendMessage(outgoing, (incoming) => {
			if (incoming.name === "error") {
				reject(incoming.payload.Message);
				return;
			}

			resolve(incoming);
		});
	});
};

const initializeBoard = () => {
	// initialize board
	global.board = [];
	for (let i = 5; i >= 0; i--) {
		let row = document.createElement('div');
		row.className = 'row';
		let rowDom = [];

		for (let j = 0; j < 6; j++) {
			let square = document.createElement('div');
			square.className = 'tile';

			if ((i % 2) === 0) {
				if ((j % 2) === 0) {
					square.className = 'tile black';
				} else {
					square.className = 'tile white';
				}
			} else {
				if ((j % 2) === 0) {
					square.className = 'tile white';
				} else {
					square.className = 'tile black';
				}
			}

			// listener
			square.addEventListener('click', (event) => {
				event.stopPropagation = true;
				if (global.turn != BLACK) {
					return;
				}

				if (global.coord === null) {
					console.log(i, j);
					return;
				}

				post({"name": "human-move", "payload": {"from": global.coord, "to": [i, j]}}).then((msg) => {
					console.log("human move complete:", msg.payload);
					update(msg.payload);
					return post({"name": "ai-move"});
				}, (err) => {
					alert(err);
					return false;
				}).then((msg) => {
					if (msg === false) {
						return;
					}

					console.log("ai move complete:", msg.payload);
					update(msg.payload);
				}, alert);

				global.coord = null;
			});

			rowDom.push(square);
			row.appendChild(square);
		}

		global.board.push(rowDom);
		document.querySelector('#board').appendChild(row);
	}

	global.board = global.board.reverse();
};

const initializeGame = () => {
	post({'name': 'initialize'}).then((msg) => {
		console.log(msg);
		update(msg.payload);
	});
};

const clear = (board) => {
	for (let i = 0; i < 6; i++) {
		for (let j = 0; j < 6; j++) {
			board[i][j].innerHTML = '';
		}
	}
};

const update = (payload) => {
	let byteboard = payload.board;
	let turn = payload.turn;
	let info = payload.info;

	global.byteboard = byteboard;
	global.turn = turn;

	clear(global.board);

	for (let i = 0; i < 6; i++) {
		for (let j = 0; j < 6; j++) {
			if (byteboard[i][j] === WHITE) {
				let piece = document.createElement('div');
				piece.className = 'piece white';
				global.board[i][j].appendChild(piece);
			} else if (byteboard[i][j] == BLACK) {
				let piece = document.createElement('div');
				piece.className = 'piece black';
				global.board[i][j].appendChild(piece);

				piece.addEventListener('click', (event) => {
					event.stopPropagation();

					if (global.turn != BLACK) {
						return;
					}

					global.coord = [i, j];
				});
			}
		}
	}

	if (turn == WHITE) {
		document.querySelector('#turn').innerText = "White (A/I) Turn";
	} else {
		document.querySelector('#turn').innerText = "Black (Human) Turn";
	}

	document.querySelector('#info').innerText = info;
};

const main = () => {
	initializeBoard();

	initializeGame();
};

document.addEventListener('astilectron-ready', () => {
	console.log('astilectron loaded');

	main();
});
