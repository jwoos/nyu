'use strict';

let coord = null;

const post = (outgoing) => {
	return new Promise((resolve, reject) => {
		astilectron.sendMessage(outgoing, (incoming) => {
			if (incoming.name === 'error') {
				reject(incoming);
			} else {
				resolve(incoming);
			}
		});
	});
};

const initializeBoard = () => {
	// initialize board
	window.board = [];
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
				if (coord === null) {
					console.log(i, j);
				} else {
					post({"name": "human-move", "payload": {"from": coord, "to": [i, j]}}).then((msg) => {
						updateBoard(msg.payload.board);
						updateOther(msg.turn, msg.info);
						return post({"name": "ai-move"});
					}, alert).then((msg) => {
						updateBoard(msg.payload);
						updateOther(msg.turn, msg.info);
					}, alert);
				}
			});

			rowDom.push(square);
			row.appendChild(square);
		}

		board.push(rowDom);
		document.querySelector('#board').appendChild(row);
	}

	window.board = window.board.reverse();
};

const initializeGame = () => {
	post({'name': 'initialize'}).then((msg) => {
		console.log(msg);
		//updateBoard(msg.payload);
		//updateOther(msg.turn, msg.info);
	});
};

const clear = (board) => {
	for (let i = 0; i < 6; i++) {
		for (let j = 0; j < 6; j++) {
			board[i][j].innerHTML = '';
		}
	}
};

const updateBoard = (byteboard) => {
	window.byteboard = byteboard;

	clear(window.board);

	for (let i = 0; i < 6; i++) {
		for (let j = 0; j < 6; j++) {
			if (byteboard[i][j] === 1) {
				let piece = document.createElement('div');
				piece.className = 'piece white';
				board[i][j].appendChild(piece);

				piece.addEventListener('click', (event) => {
					event.stopPropagation();
					coord = [i, j];
				});
			} else if (byteboard[i][j] == 2) {
				let piece = document.createElement('div');
				piece.className = 'piece black';
				board[i][j].appendChild(piece);

				piece.addEventListener('click', (event) => {
					event.stopPropagation();
					coord = [i, j];
				});
			}
		}
	}
};

const updateOther = (turn, info) => {
	if (turn == 1) {
		document.querySelector('#turn').innerText = "White (A/I) Turn";
	} else {
		document.querySelector('#turn').innerText = "Black (Human) Turn";
	}

	if (info) {
		document.querySelector('#stat').innerText = info;
	}
}

const main = () => {
	initializeBoard();

	initializeGame();
};

document.addEventListener('astilectron-ready', () => {
	console.log('astilectron loaded');

	main();
});
