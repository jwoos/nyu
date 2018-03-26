'use strict';

let global = {};

const WHITE = 1;
const BLACK = 2;

const post = (outgoing) => {
	return new Promise((resolve, reject) => {
		astilectron.sendMessage(outgoing, (incoming) => {
			if (incoming.name === 'error') {
				reject(incoming.payload.Message);
				return;
			}

			resolve(incoming);
		});
	});
};

const sleep = (ms) => {
  return new Promise(resolve => setTimeout(resolve, ms));
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
				event.stopPropagation();
				if (global.turn != BLACK) {
					return;
				}

				if (global.coord === null) {
					console.log(i, j);
					return;
				}

				humanMove(i, j);

				global.coord = null;
			});

			rowDom.push(square);
			row.appendChild(square);
		}

		global.board.push(rowDom);
		document.querySelector('#board').appendChild(row);
	}

	global.board = global.board.reverse();
	global.eventListeners = [];
};

const initializeGame = () => {
	post({'name': 'initialize'}).then(async (msg) => {
		console.log(msg);
		update(msg.payload);

		if (msg.payload.turn === WHITE) {
			await sleep(2500);
			aiMove();
		}
	});
};

const clear = () => {
	for (let val of global.eventListeners) {
		val.element.removeEventListener('click', val.handler);
	}

	global.eventListeners = [];

	for (let i = 0; i < 6; i++) {
		for (let j = 0; j < 6; j++) {
			global.board[i][j].innerHTML = '';
		}
	}
};

const update = (payload) => {
	let byteboard = payload.board;
	let turn = payload.turn;
	let info = payload.info;
	let skip = payload.skip;

	global.byteboard = byteboard;
	global.turn = turn;

	clear();

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

				let handler = (event) => {
					event.stopPropagation();

					if (global.turn != BLACK) {
						return;
					}

					global.coord = [i, j];
				}

				piece.addEventListener('click', handler);
				global.eventListeners.push({
					'element': piece,
					'handler': handler
				});
			}
		}
	}

	if (turn === WHITE) {
		document.querySelector('#turn').innerText = 'White (A/I) Turn';
	} else {
		document.querySelector('#turn').innerText = 'Black (Human) Turn';
	}

	document.querySelector('#info').innerText = info;
};

const aiMove = async () => {
	let msg = await post({'name': 'ai-move'});
	console.log('ai move complete:', msg.payload);
	update(msg.payload);

	msg = await post({'name': 'check'})
	check(msg.payload);
};

const humanMove = async (i, j) => {
	let msg;
	try {
		msg = await post({'name': 'human-move', 'payload': {'from': global.coord, 'to': [i, j]}});
	} catch (e) {
		alert(e);
		return false;
	}
	console.log('human move complete:', msg.payload);
	update(msg.payload);

	msg = await post({'name': 'check'})
	check(msg.payload);

	if (!msg.skip) {
		aiMove();
	}
};

const cleanUp = () => {
	for (let val of global.eventListeners) {
		val.element.removeEventListener('click', val.handler);
	}

	global.eventListeners = [];

	document.querySelector('#info').innerText = 'Game over\nRestart to play another game';
};

const check = (payload) => {
	if (payload.win) {
		if (payload.side === WHITE) {
			alert('You lose');
		} else if (payload.side === BLACK) {
			alert('You win');
		} else {
			alert('It\'s a tie');
		}

		cleanUp();

		return;
	}

	if (payload.skip) {
		update(payload);
		alert('No moves left, skipping');

		if (payload.turn === WHITE) {
			aiMove();
		}
	}
};

document.addEventListener('astilectron-ready', () => {
	console.log('astilectron loaded');

	initializeBoard();

	initializeGame();
});
