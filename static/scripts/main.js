window.addEventListener('load', () => {
	document.querySelector('#logbut').addEventListener('click', () => {
		document.querySelector('.login').style.display = 'block';
		document.querySelector('.register').style.display = 'none';
	});

	document.querySelector('#regbut').addEventListener('click', () => {
		document.querySelector('.login').style.display = 'none';
		document.querySelector('.register').style.display = 'block';
	});
	document.querySelector('#loginSub').addEventListener('click',()=>{
		let body = {};
		body['email'] = document.getElementById('#email').value();
		body['pw'] = document.getElementById('#pw').value();
		fetch(`/api/login`, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json'
			},
			body: JSON.stringify(body)
		}).then((d)=>{
			console.log("Logged in!!");
		});
	});
});
