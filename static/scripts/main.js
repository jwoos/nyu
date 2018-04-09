window.addEventListener('load', () => {
	document.querySelector('#logbut').addEventListener('click', () => {
		document.querySelector('.login').style.display = 'block';
		document.querySelector('.register').style.display = 'none';
	});

	document.querySelector('#regbut').addEventListener('click', () => {
		document.querySelector('.login').style.display = 'none';
		document.querySelector('.register').style.display = 'block';
	});
});
