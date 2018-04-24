'use strict';

window.common.checkAuthentication(true);

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

			window.common.setAccount(data.data.account);
			window.common.setToken(data.data.token);

			window.common.checkAuthentication(true);
		} catch (e) {
			console.error(e);
		}
	});

	document.querySelector('#register-class').addEventListener('change', () => {
		const type = document.querySelector('#register-class').value;
		document.querySelector(`#register-${type}-section`).className = '';

		if (type === 'student') {
			document.querySelector('#register-professor-section').className = 'd-none';
		} else {
			document.querySelector('#register-student-section').className = 'd-none';
		}
	});

	document.querySelector('#register-submit').addEventListener('click', async () => {
		let body = {
			email: document.querySelector('#register-email').value,
			password: document.querySelector('#register-password').value,
			class: document.querySelector('#register-class').value
		};

		if (body.class === 'student') {
			body['university_number'] = document.querySelector('#register-student-unumber').value;
		} else {
			body['first_name'] = document.querySelector('#register-professor-fname').value;
			body['last_name'] = document.querySelector('#register-professor-lname').value;
		}

		try {
			let response = await fetch(`${BASE}/accounts`, {
				method: 'POST',
				headers: {'Content-Type': 'application/json'},
				body: JSON.stringify(body)
			});

			window.location.replace('/');
		} catch (e) {
			console.error(e);
		}
	});
});
