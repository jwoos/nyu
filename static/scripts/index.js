const BASE = '/api'

window.addEventListener('load', () => {
	document.querySelector('#login-submit').addEventListener('click', async () => {
		let body = {
			email: document.querySelector('#login-email').value,
			password: document.querySelector('#login-password').value
		};

		try {
			let response = await fetch(`${BASE}/accounts/authentications`, {
				method: 'POST',
				headers: {'Content-Type': 'application/json'},
				body: JSON.stringify(body)
			});

			let data = await response.json();
			console.log(data);
		} catch (e) {
			console.error(e);
		}
	});

	document.querySelector('#register-submit').addEventListener('click', async () => {
		let body = {
			email: document.querySelector('#register-email').value(),
			password: document.querySelector('#register-password').value()
		};

		try {
			let response = await fetch(`${BASE}/accounts`, {
				method: 'POST',
				headers: {'Content-Type': 'application/json'},
				body: JSON.stringify(body)
			});
		} catch (e) {
			console.error(e);
		}
	});
});
